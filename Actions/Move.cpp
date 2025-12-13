#include "Move.h"
#include "..\ApplicationManager.h"

Move::Move(ApplicationManager* pApp) :Action(pApp)
{
}

void Move::ReadActionParameters()
{
    Output* pOut = pManager->GetOutput();
    Input* pIn = pManager->GetInput();

    // 1. Get Reference Point
    pOut->PrintMsg("Move Action: Click on a reference point (start of movement).");
    pIn->GetPointClicked(x1, y1);

    // 2. Get Destination Point
    pOut->PrintMsg("Click on the destination point.");
    pIn->GetPointClicked(x2, y2);

    pOut->ClearStatusBar();
}

void Move::Execute()
{
    Output* pOut = pManager->GetOutput();

    // 1. Check if any components are selected
    if (pManager->GetSelectedCount() == 0)
    {
        pOut->PrintMsg("Error: No components selected. Please select component(s) first.");
        return; // Exit action if nothing is selected
    }


ReadActionParameters();

int diffx = x2 - x1;
int diffy = y2 - y1;

pManager->MoveSelected(diffx, diffy);

pOut->PrintMsg("Move completed.");

}

void Move::Undo()
{
}

void Move::Redo()
{
}