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
	if (!pComp)   // if no component is selected
    {
		pOut->PrintMsg("Copy failed: No component selected"); // print error message 
        return;
    }

    pManager->SetClipboard(pComp); 
	pOut->PrintMsg("Component copied");  / / print success message
}
