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
    Input* pIn = pManager->GetInput();

    // determine if ctrl is pressed (if Input supports it)
    bool ctrl = false;
    // If Input class provides IsCtrlPressed(), use it. Otherwise ctrl remains false.
    // Make sure to add IsCtrlPressed() to Input if you want Ctrl behavior.
#ifdef HAS_ISCTRL
    ctrl = pIn->IsCtrlPressed();
#else
// try calling it anyway (will compile only if method exists)
// ctrl = pIn->IsCtrlPressed();
#endif

    Component* pComp = pManager->GetComponentAt(x, y);
    if (pComp != NULL)
    {
        if (ctrl)
        {
            // Toggle selection of clicked component (multi-select behavior)
            if (pComp->IsSelected())
            {
                pManager->RemoveFromSelection(pComp);
                pOut->PrintMsg("Component unselected.");
            }
            else
            {
                pManager->AddToSelection(pComp);
                pOut->PrintMsg("Component added to selection.");
            }
        }
        else
        {
            // Single-selection behavior: clear previous then select this
            pManager->ClearSelection();
            pManager->AddToSelection(pComp);
            pOut->PrintMsg("Component selected.");
        }
    }
    else
    {
        // Clicked empty space
        if (!ctrl) // if ctrl pressed and empty, we keep selected items (common UX) — here we clear if no ctrl
            pManager->ClearSelection();
        pOut->PrintMsg("Selection cleared.");
    }
}
void Select::Undo()
{
}
void Select::Redo()
{
}