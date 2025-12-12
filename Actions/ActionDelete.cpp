#include "ActionDelete.h"
#include "..\ApplicationManager.h"
#include "..\UI\UI.h"
#include <iostream>
using namespace std;

ActionDelete::ActionDelete(ApplicationManager* pApp) : Action(pApp)
{
}

void ActionDelete::ReadActionParameters()
{
    // no parameters - deletion depends on current selection
}

void ActionDelete::Execute()
{
    Output* pOut = pManager->GetOutput();

    // get all selected components
    std::vector<Component*> selectedList = pManager->GetAllSelected();

    if (selectedList.empty())
    {
        pOut->PrintMsg("There is no selected component(s), please select one or more component to delete");
        return;
    }

    // store components and their indices for undo
    DeletedComponents.clear();
    DeletedIndices.clear();

    for (Component* c : selectedList)
    {
        // before deleting component, break its connections
        pManager->BreakConnections(c);

        int idx = pManager->GetComponentIndex(c);
        if (idx != -1)
        {
            DeletedComponents.push_back(c);
            DeletedIndices.push_back(idx);
        }
    }

    // delete components (important: delete by current index lookup since array shifts)
    // We will iterate over DeletedIndices sorted descending to delete safely by index,
    // but here we have component pointers so we'll call DeleteComponent which finds and removes.
    for (Component* c : selectedList)
    {
        pManager->DeleteComponent(c);
    }

    // clear selection
    pManager->ClearSelection();

    pOut->PrintMsg("Component(s) deleted");
}

void ActionDelete::Undo()
{
    Output* pOut = pManager->GetOutput();

    // Re-insert deleted components at their original indices
    // Insert in ascending order of indices so positions match
    for (size_t i = 0; i < DeletedComponents.size(); ++i)
    {
        int idx = DeletedIndices[i];
        Component* c = DeletedComponents[i];
        pManager->InsertComponentAt(idx, c);
        // ensure it's not selected after undo
        c->SetSelected(false);
    }

    pOut->PrintMsg("Undo Delete completed.");
}

void ActionDelete::Redo()
{
    Output* pOut = pManager->GetOutput();

    for (Component* c : DeletedComponents)
    {
        pManager->DeleteComponent(c);
    }

    pOut->PrintMsg("Redo Delete completed.");
}