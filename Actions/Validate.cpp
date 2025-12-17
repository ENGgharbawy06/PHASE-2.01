#include "Validate.h"
#include "..\ApplicationManager.h"
#include "..\Components\Gate.h"
#include "..\Components\LED.h"

Validate::Validate(ApplicationManager* pApp) : Action(pApp)
{
}

Validate::~Validate()
{
}

void Validate::ReadActionParameters()
{
	// No parameters needed for validation
}

void Validate::Execute()
{
	// Get the Output interface (Used for printing messages)
	Output* pOut = pManager->GetOutput();

	// =================================================================================
	// CASE 1: CHECK IF CIRCUIT IS EMPTY
	// =================================================================================
	// If there are no components, the circuit is technically invalid/empty.
	if (pManager->GetCompCount() == 0)
	{
		pOut->PrintMsg("Validation Failed: The circuit is empty. Please add gates first.");
		return; // <--- STOP EXECUTION HERE (Do not print "Successful")
	}

	// =================================================================================
	// CASE 2: NORMAL VALIDATION (Check Connections)
	// =================================================================================
	pOut->PrintMsg("Validating Circuit...");

	int count = pManager->GetCompCount();
	bool isValid = true;

	// Clear previous selections so we only highlight current errors
	pManager->UnselectAll();

	for (int i = 0; i < count; ++i)
	{
		Component* pComp = pManager->GetComponent(i);
		bool compConnected = true;

		// --- Check Gates (AND, OR, NOT, etc.) ---
		Gate* pGate = dynamic_cast<Gate*>(pComp);
		if (pGate)
		{
			// Check every input pin of the gate
			for (int j = 0; j < pGate->GetInputPinCount(); ++j)
			{
				if (!pGate->GetInputPin(j)->getIsConnected())
				{
					compConnected = false;
					break;
				}
			}
		}

		// --- Check LEDs ---
		LED* pLED = dynamic_cast<LED*>(pComp);
		if (pLED)
		{
			// Check if the LED input pin is connected
			if (!pLED->GetInputPin()->getIsConnected())
			{
				compConnected = false;
			}
		}

		// --- Handle Unconnected Components ---
		// If unconnected, mark as invalid and highlight the component (Select it)
		if (!compConnected)
		{
			pComp->SetSelected(true);
			isValid = false;
		}
	}

	// =================================================================================
	// FINAL RESULT MESSAGE
	// =================================================================================
	if (isValid)
	{
		pOut->PrintMsg("Validation Successful: All input pins are connected.");
	}
	else
	{
		pOut->PrintMsg("Validation Failed: Components with unconnected inputs are selected.");
	}
}

void Validate::Undo()
{
	// Validation cannot be undone
}

void Validate::Redo()
{
	// Validation cannot be redone
}