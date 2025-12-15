#include "SwitchToDesign.h"
#include "..\ApplicationManager.h"
#include "..\GUI\Output.h" // Needed to access Output class functions

SwitchToDesign::SwitchToDesign(ApplicationManager* pApp) : Action(pApp)
{
}

SwitchToDesign::~SwitchToDesign()
{
}

void SwitchToDesign::ReadActionParameters()
{
	// No parameters needed
}

void SwitchToDesign::Execute()
{
	Output* pOut = pManager->GetOutput();

	// 1. Switch the toolbar (This internally sets UI.AppMode = DESIGN)
	pOut->CreateDesignToolBar();

	// 2. Clear the status bar
	pOut->ClearStatusBar();

	//3. create bottom tool bar
	pOut->CreateBottomToolBar();

	// 4. Redraw the interface to remove any simulation artifacts (optional but recommended)
	pManager->UpdateInterface();

	// 5. Notify the user
	pOut->PrintMsg("Switched to Design Mode.");
}

void SwitchToDesign::Undo()
{
}

void SwitchToDesign::Redo()
{
}



