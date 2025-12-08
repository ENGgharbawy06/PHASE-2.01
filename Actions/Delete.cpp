#include "Delete.h"
#include "../ApplicationManager.h"
#include "../GUI/Output.h"
#include "../GUI/Input.h"
#include "../Components/Component.h"

Delete::Delete(ApplicationManager* pApp)
    : Action(pApp), CompToDelete(nullptr)  // Initialize with null component
{
}

void Delete::ReadActionParameters()
{
    Input* pIn = pManager->GetInput();
    Output* pOut = pManager->GetOutput();

    pOut->PrintMsg("Delete: Click on the component you want to delete");

    int x, y;
    pIn->GetPointClicked(x, y);  // Get user click position

    // Find component at clicked coordinates
    CompToDelete = pManager->GetComponentAt(x, y);

    pOut->ClearStatusBar();
}

void Delete::Execute()
{
    ReadActionParameters();

    Output* pOut = pManager->GetOutput();
    if (!CompToDelete)  // No component found at clicked position
    {
        pOut->PrintMsg("Delete: No component selected");
        return;
    }

    // Disconnect all wires from this component
    pManager->BreakConnections(CompToDelete);

    // Remove component from circuit
    pManager->DeleteComponent(CompToDelete);

    // Refresh display
    pManager->UpdateInterface();

    pOut->ClearStatusBar();
}

void Delete::Undo()
{
    // TODO: Restore deleted component and connections
}

void Delete::Redo()
{
    // TODO: Re-delete the component
}