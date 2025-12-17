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
}

void Validate::Execute()
{
	
	Output* pOut = pManager->GetOutput();


	// lw mafesh ay comp ytl3 invalid aw empty 
	if (pManager->GetCompCount() == 0)
	{
		pOut->PrintMsg("Validation Failed: The circuit is empty. Please add gates first.");
		return; //msh 3ayzeno y3ml print successful 
	}

	
	pOut->PrintMsg("Validating Circuit...");

	int count = pManager->GetCompCount();
	bool isValid = true;

	
	pManager->UnselectAll();

	for (int i = 0; i < count; ++i)
	{
		Component* pComp = pManager->GetComponent(i);
		bool compConnected = true;

		
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

		
		LED* pLED = dynamic_cast<LED*>(pComp);
		if (pLED)
		{
			
			if (!pLED->GetInputPin()->getIsConnected())
			{
				compConnected = false;
			}
		}

		
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