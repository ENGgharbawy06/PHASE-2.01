#include "TOGGLE_SWITCHES.h"
#include "../ApplicationManager.h"

TOGGLE_SWITCHES::TOGGLE_SWITCHES(ApplicationManager* pApp) : Action(pApp)
{
	pSwitch = nullptr;
	x = 0;
	y = 0;
	oldState = false; // Initialize to safe default
}

TOGGLE_SWITCHES::~TOGGLE_SWITCHES()
{
}

void TOGGLE_SWITCHES::ReadActionParameters()
{
	// Get the Input interface
	Input* pIn = pManager->GetInput();

	// Wait for the user to click on a component (the switch)
	pIn->GetPointClicked(x, y);
}

void TOGGLE_SWITCHES::Execute()
{
	// 1. Get user click coordinates
	ReadActionParameters();

	// 2. Find the component at these coordinates
	Component* pComp = pManager->GetComponentAt(x, y);

	// 3. Check if the component is a Switch using dynamic_cast
	// (Note: This requires #include "Switch.h" in the header or here)
	pSwitch = dynamic_cast<Switch*>(pComp);

	if (pSwitch)
	{
		// Save old state for Undo/Redo logic
		oldState = pSwitch->IsSelected();

		// Toggle the state (Set it to the opposite of what it was)
		pSwitch->SetSelected(!oldState);

		// 4. Recalculate the circuit to show the new result
		pManager->ExecuteCircuit();
	}
}

void TOGGLE_SWITCHES::Undo()
{
	if (pSwitch)
	{
		// Restore the old state
		pSwitch->SetSelected(oldState);

		// Recalculate circuit to reflect the undo
		pManager->ExecuteCircuit();
	}
}

void TOGGLE_SWITCHES::Redo()
{
	if (pSwitch)
	{

		pSwitch->SetSelected(!oldState);


		pManager->ExecuteCircuit();
	}
}

void TOGGLE_SWITCHES::Redo()
{
	if (pSwitch)
	{
		// Re-apply the toggle (opposite of oldState)
		pSwitch->SetSelected(!oldState);

		// Recalculate circuit to reflect the redo
		pManager->ExecuteCircuit();
	}
}