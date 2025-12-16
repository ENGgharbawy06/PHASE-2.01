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

	pManager->UpdateInterface();

	pOut->PrintMsg("Switched to Simulation Mode.");
}

void SwitchToSim::Undo()
{
}

void SwitchToSim::Redo()
{
}