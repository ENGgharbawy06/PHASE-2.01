#include "Probe.h"
#include "..\ApplicationManager.h"
#include "..\Components\Connection.h" 
#include "..\Components\Component.h"
#include "..\GUI\Output.h"

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

	// Print the initial message ONCE so we don't overwrite results later
	pOut->PrintMsg("Probe Mode: Click on a Connection or Component to check status (Click Toolbar/Statusbar to exit)");

	// Loop to allow probing multiple components without re-selecting the tool
	while (true)
	{
		int x = 0, y = 0;
		pIn->GetPointClicked(x, y); // Wait for user click
		// The previous message stays on the status bar while waiting here

		// Check if the user clicked outside the drawing area
		if (y < UI.ToolBarHeight || y > UI.height - UI.StatusBarHeight)
		{
			pOut->PrintMsg("Exiting Probe Mode.");
			break; // Exit if clicked outside drawing area (e.g. Toolbar)
		}

		Component* pComp = pManager->GetComponentAt(x, y);

		if (pComp != nullptr)
		{
			int status = pComp->GetOutPinStatus();
			string label = pComp->GetLabel();
			if (label == "") label = "Component";

			// Build the message string
			string msg = label + " Status: ";
			if (status == HIGH)
				msg += "HIGH (1)";
			else
				msg += "LOW (0)";

			// Append instruction so user knows the tool is still active
			msg += "   [Click again to probe another]";

			pOut->PrintMsg(msg);
		}
		else
		{
			// Do NOT break here. Just ask to try again.
			pOut->PrintMsg("No component found. Click again to probe.");
		}
	}
}

void Probe::Undo()
{
}

void Probe::Redo()
{
}

// Returning false prevents the ApplicationManager from recording this action
bool Probe::isUndoable() const
{
	return false;
}