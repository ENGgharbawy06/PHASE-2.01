#include "ActionTOGGLE_SWITCHES.h"
#include "..\ApplicationManager.h"

ActionToggleSwitches::ActionToggleSwitches(ApplicationManager* pApp) : Action(pApp)
{
}

ActionToggleSwitches::~ActionToggleSwitches()
{
}

void ActionToggleSwitches::ReadActionParameters()
{
	// No parameters needed (button click)
}

void ActionToggleSwitches::Execute()
{
	Output* pOut = pManager->GetOutput();

	// 1. Determine the Target State
	// Logic: If *any* switch is OFF, we turn ALL ON. 
	//        Only if *all* are already ON do we turn them OFF.
	bool targetState = true; // Default to turning ON (HIGH)
	bool allAreOn = true;

	int count = pManager->GetCompCount();
	for (int i = 0; i < count; ++i)
	{
		Switch* pSwitch = dynamic_cast<Switch*>(pManager->GetComponent(i));
		if (pSwitch)
		{
			// Check if this switch is OFF (Low)
			if (pSwitch->GetOutPinStatus() == LOW)
			{
				allAreOn = false;
				break; // Found one that is OFF, so our goal is to turn everything ON
			}
		}
	}

	if (allAreOn)
	{
		targetState = false; // Turn OFF (LOW)
		pOut->PrintMsg("Master Switch: Turning ALL Switches OFF.");
	}
	else
	{
		targetState = true; // Turn ON (HIGH)
		pOut->PrintMsg("Master Switch: Turning ALL Switches ON.");
	}

	// 2. Apply the Target State to All Switches
	for (int i = 0; i < count; ++i)
	{
		Switch* pSwitch = dynamic_cast<Switch*>(pManager->GetComponent(i));
		if (pSwitch)
		{
			// In your Switch code, 'selected' controls the ON/OFF state in Operate()
			pSwitch->SetSelected(targetState);
		}
	}

	// 3. Simulate and Update
	pManager->ExecuteCircuit(); // Recalculate the whole circuit
	pManager->UpdateInterface(); // Redraw to show changes (LEDs lighting up etc.)
}

void ActionToggleSwitches::Undo()
{
}

void ActionToggleSwitches::Redo()
{
}