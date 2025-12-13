#include "Move.h"
#include "..\ApplicationManager.h"

Move::Move(ApplicationManager* pApp) :Action(pApp)
{
}

void Move::ReadActionParameters()
{
    Output* pOut = pManager->GetOutput();
    Input* pIn = pManager->GetInput();

    pOut->PrintMsg("Move Action: Click on the component you want to move.");
    pIn->GetPointClicked(x1, y1); // Store start point

    pOut->PrintMsg("Click on the location destination point. ");
	pIn->GetPointClicked(x2, y2); //Getting new location

    pOut->ClearStatusBar();
}

void Move::Execute()
{
    ReadActionParameters(); // Get the points from the user

    //
    int diffx = x2 - x1;
    int diffy = y2 - y1;

    // Call the Manager to move the selected components
    // You must ensure MoveSelected is implemented in ApplicationManager (see Step 4)
    pManager->MoveSelected(diffx, diffy);

    pManager->GetOutput()->PrintMsg("Move completed.");
}

void Move::Undo()
{
}

void Move::Redo()
{
}