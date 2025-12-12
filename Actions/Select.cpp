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
    ReadActionParameters(); // Get the click coordinates

    Output* pOut = pManager->GetOutput();

    // 1. Check if there is a component at the clicked coordinates
    Component* pComp = pManager->GetComponentAt(x, y);

    if (pComp != NULL)
    {
        // === Case A: User clicked on a component ===

        if (pComp->IsSelected())
        {
            // If it's already selected, unselect it
            pComp->SetSelected(false);
            pManager->SetSelected(NULL); // Clear the pointer in AppManager
            pOut->PrintMsg("Component unselected.");
        }
        else
        {
            // If it's NOT selected, select it

            // First, unselect the previously selected component (if any)
            // This enforces "Single Selection" behavior
            Component* oldComp = pManager->GetSelected();
            if (oldComp != NULL)
            {
                oldComp->SetSelected(false);
            }

            // Now select the new one
            pComp->SetSelected(true);
            pManager->SetSelected(pComp); // Tell AppManager this is the active one
            pOut->PrintMsg("Component selected.");
        }
    }
    else
    {
        // === Case B: User clicked on empty space ===
        // Unselect everything
        Component* oldComp = pManager->GetSelected();
        if (oldComp != NULL)
        {
            oldComp->SetSelected(false);
        }
        pManager->SetSelected(NULL);
        pOut->PrintMsg("Selection cleared.");
    }
}

void Select::Undo()
{
}

void Select::Redo()
{
}