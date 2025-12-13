#include "Select.h"
#include "..\ApplicationManager.h"

Select::Select(ApplicationManager* pApp) :Action(pApp)
{
}

void Select::ReadActionParameters()
{
    // Get the Input interface
    Input* pIn = pManager->GetInput();

    // RETRIEVE THE STORED CLICK (The one that triggered the action)
    pIn->GetLastClick(x, y);
}

void Select::Execute()
{
    ReadActionParameters(); // Beygib el coordiantes of point clicked

    Output* pOut = pManager->GetOutput();

    // 1. Check if user clicked a component
    Component* pComp = pManager->GetComponentAt(x, y); //Only returns the pointer law howa mawgod 
                                                       //fel component list (Note: el comp list di array of all components)

	if (pComp != NULL) //Hateb2a true law enta fe3lan 3amalt select 3ala component marsom
    {
        // TOGGLE logic:
        if (pComp->IsSelected())
        {
            pComp->SetSelected(false); // Deselect if already selected
            pOut->PrintMsg("Component unselected.");
        }
        else
        {
            pComp->SetSelected(true); // Select if not selected
            pOut->PrintMsg("Component selected.");
        }
    }
    else
    {
        // Clicked empty space -> Clear ALL selections
        // You need to add a function in ApplicationManager to do this efficiently
        pManager->UnselectAll();
        pOut->PrintMsg("Selection cleared.");
    }
}

void Select::Undo()
{
}

void Select::Redo()
{
}