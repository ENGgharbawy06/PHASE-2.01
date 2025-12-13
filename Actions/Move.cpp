#include "Move.h"
#include "..\ApplicationManager.h"
#include "..\Components\Connection.h"

Move::Move(ApplicationManager* pApp) :Action(pApp)
{
}

void Move::ReadActionParameters()
{
	// Empty because we handle inputs directly in Execute based on the case
}

void Move::Execute()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	// 1. Check how many items are selected
	int count = pManager->GetSelectedCount();

	if (count == 0)
	{
		pOut->PrintMsg("Error: No components selected. Please select component(s) first.");
		return;
	}

	int dx = 0, dy = 0;

	// 2. Handle Case 1: Single Component (Not a Connection)
	// We want to move its CENTER to the clicked location.
	if (count == 1)
	{
		Component* pComp = pManager->GetOneSelectedComponent();

		// If it's a gate (Not a connection), use 1-click move
		if (dynamic_cast<Connection*>(pComp) == NULL)
		{
			pOut->PrintMsg("Move Component: Click on the new destination.");

			int destX, destY;
			pIn->GetPointClicked(destX, destY); // User clicks destination

			// Calculate the center of the component
			GraphicsInfo GInfo = pComp->GetGraphicsInfo();
			int centerX = (GInfo.x1 + GInfo.x2) / 2;
			int centerY = (GInfo.y1 + GInfo.y2) / 2;

			// Calculate shift needed to move Center -> Dest
			dx = destX - centerX;
			dy = destY - centerY;
		}
		else
		{
			// It is a connection, treat it like multiple components (use Reference point)
			// forcing flow to the 'else' block logic below is cleaner, but we duplicate for clarity:
			pOut->PrintMsg("Move Connection: Click Reference Point, then Destination.");
			int x1, y1, x2, y2;
			pIn->GetPointClicked(x1, y1);
			pIn->GetPointClicked(x2, y2);
			dx = x2 - x1;
			dy = y2 - y1;
		}
	}
	// 3. Handle Case 2: Multiple Components (or Single Connection)
	else
	{
		pOut->PrintMsg("Move Selected: Click on a Reference Point (Start).");
		int x1, y1;
		pIn->GetPointClicked(x1, y1);

		pOut->PrintMsg("Click on the Destination Point (End).");
		int x2, y2;
		pIn->GetPointClicked(x2, y2);

		dx = x2 - x1;
		dy = y2 - y1;
	}

	// 4. Apply the Move
	pManager->MoveSelected(dx, dy);
	pOut->PrintMsg("Move completed.");
}

void Move::Undo()
{
}

void Move::Redo()
{
}