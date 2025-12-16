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

    // 1️⃣ Store SAME component in clipboard
    pManager->SetClipboard(CompToCut);

    // 2️⃣ Remove component from circuit (NO delete)
    pManager->RemoveComponent(CompToCut);

    // 3️⃣ Refresh UI
    pManager->UpdateInterface();

    pOut->PrintMsg("Component cut!");
}

void CutAction::Undo()
{
    if (!CompToCut) return;

    // 🔁 Undo CUT = put component bacK
    pManager->AddComponent(CompToCut);
    pManager->UpdateInterface();
}

void CutAction::Redo()
{
    if (!CompToCut) return;

    // 🔁 Redo CUT = remove it again
    pManager->RemoveComponent(CompToCut);
    pManager->UpdateInterface();
}
