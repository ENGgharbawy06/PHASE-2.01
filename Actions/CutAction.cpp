#include "CutAction.h"
#include "../ApplicationManager.h"
#include "../GUI/Output.h"
#include "../GUI/Input.h"
#include "../Components/Component.h"
//Testing
CutAction::CutAction(ApplicationManager* pApp)
    : Action(pApp), CompToCut(nullptr)
{
}

void CutAction::ReadActionParameters()
{
    Output* pOut = pManager->GetOutput();
    Input* pIn = pManager->GetInput();

    // Prompt user to select a component
    pOut->PrintMsg("Select a component to CUT...");

    // Get mouse click coordinates
    int x, y;
    pIn->GetPointClicked(x, y);

    // Find component at clicked position
    CompToCut = pManager->GetComponentAt(x, y);

    pOut->ClearStatusBar();
}

void CutAction::Execute()
{
    ReadActionParameters();

    Output* pOut = pManager->GetOutput();

    // Check if a component was found
    if (!CompToCut)
    {
        pOut->PrintMsg("No component selected!");
        return;
    }

    // Clone the component and store in clipboard (COPY part)
    Component* copied = CompToCut->Clone(CompToCut->GetGraphicsInfo());
    pManager->SetClipboard(copied);

    // Disconnect all wires from this component (DELETE part)
    pManager->BreakConnections(CompToCut);

    // Remove component from circuit (DELETE part)
    pManager->DeleteComponent(CompToCut);

    // Refresh display
    pManager->UpdateInterface();

    // Confirm successful cut
    pOut->PrintMsg("Component cut!");
}

void CutAction::Undo()
{
    // TODO: Restore cut component and connections
}

void CutAction::Redo()
{
    // TODO: Re-cut the component
}
