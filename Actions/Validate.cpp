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
	// No parameters needed
}

void Validate::Execute()
{
	Output* pOut = pManager->GetOutput();
	int count = pManager->GetCompCount();
	bool isValid = true;

	// Clear previous selections to show only errors
	pManager->UnselectAll();

	for (int i = 0; i < count; ++i)
	{
		Component* pComp = pManager->GetComponent(i);
		bool compConnected = true;

		// 1. Check Gates (AND, OR, etc.)
		Gate* pGate = dynamic_cast<Gate*>(pComp);
		if (pGate)
		{
			for (int j = 0; j < pGate->GetInputPinCount(); ++j)
			{
				if (!pGate->GetInputPin(j)->getIsConnected())
				{
					compConnected = false;
					break;
				}
			}
		}

		// 2. Check LEDs
		LED* pLED = dynamic_cast<LED*>(pComp);
		if (pLED)
		{
			// Requires GetInputPin() to be public in LED.h
			if (!pLED->GetInputPin()->getIsConnected())
			{
				compConnected = false;
			}
		}

		// If unconnected, mark as invalid and highlight the component
		if (!compConnected)
		{
			pComp->SetSelected(true);
			isValid = false;
		}
	}

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
}

void Validate::Redo()
{
}