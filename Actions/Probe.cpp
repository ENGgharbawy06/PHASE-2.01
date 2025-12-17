#include "Probe.h"
#include "..\ApplicationManager.h"
#include "..\Components\Connection.h" 
#include "..\Components\Component.h"

Probe::Probe(ApplicationManager* pApp) : Action(pApp)
{
}

Probe::~Probe()
{
}

void Probe::ReadActionParameters()
{
	// We only need to wait for a click in Execute()
}

void Probe::Execute()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMsg("Probe Mode: Click on a Connection or Component to check its status...");

	int x, y;
	pIn->GetPointClicked(x, y); // Wait for user click

	// Check if the user clicked on a component
	Component* pComp = pManager->GetComponentAt(x, y);

	if (pComp != nullptr)
	{
		// Polymorphism in action: GetOutPinStatus() works for Gates and Connections
		int status = pComp->GetOutPinStatus();

		string label = pComp->GetLabel();
		if (label == "") label = "Component";

		if (status == HIGH)
			pOut->PrintMsg(label + " Status: HIGH (1)");
		else
			pOut->PrintMsg(label + " Status: LOW (0)");
	}
	else
	{
		pOut->PrintMsg("No component found at this position.");
	}
}

void Probe::Undo()
{
}

void Probe::Redo()
{
}