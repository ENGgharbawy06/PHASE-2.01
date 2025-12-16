#include "CutAction.h"
#include "../ApplicationManager.h"
#include "../GUI/Output.h"
#include "../GUI/Input.h"
#include "../Components/Component.h"

CutAction::CutAction(ApplicationManager* pApp)
    : Action(pApp), CompToCut(nullptr)
{
}

void CutAction::ReadActionParameters()
{
    Output* pOut = pManager->GetOutput();
    Input* pIn = pManager->GetInput();

    pOut->PrintMsg("Select a component to CUT...");

    int x, y;
    pIn->GetPointClicked(x, y);

    CompToCut = pManager->GetComponentAt(x, y);

    pOut->ClearStatusBar();
}

void CutAction::Execute()
{
    ReadActionParameters();

    Output* pOut = pManager->GetOutput();

    if (!CompToCut)
    {
        pOut->PrintMsg("No component selected!");
        return;
    }

    // Store SAME component in clipboard
    pManager->SetClipboard(CompToCut);

    //  Remove component from circuit (NO delete)
    pManager->RemoveComponent(CompToCut);

    //  Refresh UI
    pManager->UpdateInterface();

    pOut->PrintMsg("Component cut!");
}

void CutAction::Undo()
{
    if (!CompToCut) return;
    pManager->AddComponent(CompToCut);
    pManager->UpdateInterface();
}

void CutAction::Redo()
{
    if (!CompToCut) return;
    pManager->RemoveComponent(CompToCut);
    pManager->UpdateInterface();
}
