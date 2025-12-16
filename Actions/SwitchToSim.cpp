#include "SwitchToSim.h"
#include "..\ApplicationManager.h"
#include "..\GUI\Output.h"

SwitchToSim::SwitchToSim(ApplicationManager* pApp) : Action(pApp)
{
}

SwitchToSim::~SwitchToSim()
{
}

void SwitchToSim::ReadActionParameters()
{
	// No parameters needed for switching modes
}

void SwitchToSim::Execute()
{
	Output* pOut = pManager->GetOutput();

	pOut->CreateSimulationToolBar();

	pOut->ClearStatusBar();

	// 3. Create/Refresh the bottom toolbar (if consistent across modes)
	pOut->CreateBottomToolBar();

	pManager->UpdateInterface();

	pOut->PrintMsg("Switched to Simulation Mode.");
}

void SwitchToSim::Undo()
{
}

void SwitchToSim::Redo()
{
}