#include "CopyAction.h"
#include "../ApplicationManager.h"
#include "../GUI/Output.h"
#include "../Components/Component.h"

CopyAction::CopyAction(ApplicationManager* pApp)
    : Action(pApp)
{
}

void CopyAction::ReadActionParameters() {}

void CopyAction::Execute()
{
    Output* pOut = pManager->GetOutput();

    // get ONE selected component
    Component* pComp = pManager->GetOneSelectedComponent();
    if (!pComp)
    {
        pOut->PrintMsg("Copy failed: No component selected");
        return;
    }

    pManager->SetClipboard(pComp);
    pOut->PrintMsg("Component copied");
}
