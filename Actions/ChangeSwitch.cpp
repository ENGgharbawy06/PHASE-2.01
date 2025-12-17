#include "ChangeSwitch.h"
#include "..\ApplicationManager.h"

ChangeSwitch::ChangeSwitch(ApplicationManager* pApp) :Action(pApp)
{
}

ChangeSwitch::~ChangeSwitch(void)
{
}

void ChangeSwitch::ReadActionParameters()
{
	// This action does not require any parameters (clicks) from the user
	// It applies immediately when the button is pressed.
}

void ChangeSwitch::Execute()
{
	Output* pOut = pManager->GetOutput();

	bool turnAllOn = false;
	int compCount = pManager->GetCompCount();

	// 1. Check if ANY switch is currently OFF
	for (int i = 0; i < compCount; i++)
	{
		Component* pComp = pManager->GetComponent(i);
		Switch* pSwitch = dynamic_cast<Switch*>(pComp);

		if (pSwitch != NULL)
		{
			if (!pSwitch->IsSelected())
			{
				turnAllOn = true;
				break;
			}
		}
	}

	// 2. Apply the new state
	int switchCount = 0;
	for (int i = 0; i < compCount; i++)
	{
		Component* pComp = pManager->GetComponent(i);
		Switch* pSwitch = dynamic_cast<Switch*>(pComp);

		if (pSwitch != NULL)
		{
			pSwitch->SetSelected(turnAllOn);
			switchCount++;
		}
	}

	if (switchCount > 0)
	{
		if (turnAllOn)
			pOut->PrintMsg("Action: All Switches turned ON (High).");
		else
			pOut->PrintMsg("Action: All Switches turned OFF (Low).");
	}
	else
	{
		pOut->PrintMsg("No switches found in the circuit.");
	}
}

void ChangeSwitch::Undo()
{
}

void ChangeSwitch::Redo()
{
}