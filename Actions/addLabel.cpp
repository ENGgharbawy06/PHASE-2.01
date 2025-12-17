#include "AddLabel.h"
#include "..\ApplicationManager.h"
#include "..\GUI\Input.h"
#include "..\GUI\Output.h"
#include "..\Components\Label.h"

AddLabel::AddLabel(ApplicationManager* pApp) : Action(pApp)
{
    pLabel = nullptr;
}

AddLabel::~AddLabel()
{
	

}

void AddLabel::ReadActionParameters()
{
    Output* pOut = pManager->GetOutput();
    Input* pIn = pManager->GetInput();

    
    pOut->PrintMsg("Click on a component to add a label");

    int x, y;
    pIn->GetPointClicked(x, y);

    
    Component* pComp = pManager->GetComponentAt(x, y);

    if (!pComp)
    {
        pOut->PrintMsg("No component selected! Action canceled.");
        return;
    }

    if (pComp->GetLabel() != "")
    {
        pOut->PrintMsg("Error: Component already has a label! You can edit it instead.");
       
        labelText = "";
        return;
    }

    
    pOut->PrintMsg("Enter label text:");
    labelText = pIn->GetString(pOut);

    if (labelText.empty())
    {
        pOut->PrintMsg("No text entered! Action canceled.");
        return;
    }

    pComp->SetLabel(labelText);

    
    GraphicsInfo compGfx = pComp->GetGraphicsInfo();

    
    labelGfx.x1 = (compGfx.x1 + compGfx.x2) / 2 - 20; 
    labelGfx.y1 = compGfx.y1 - 8; 
    labelGfx.x2 = labelGfx.x1 + 40;
    labelGfx.y2 = labelGfx.y1 + 12;
}

void AddLabel::Execute()
{
    ReadActionParameters();

   
    if (labelText.empty())
        return;

    // Create the label
    pLabel = new Label(labelGfx, labelText);

    if (pLabel)
    {
        pManager->AddComponent(pLabel);
        pManager->GetOutput()->PrintMsg("Label added successfully!");
    }
}

void AddLabel::Undo()
{
    if (pLabel != nullptr)
    {
        pManager->DeleteComponent(pLabel);
        pManager->GetOutput()->PrintMsg("Undo: Label removed.");
    }
}

void AddLabel::Redo()
{
    if (pLabel != nullptr)
    {
        pManager->AddComponent(pLabel);
        pManager->GetOutput()->PrintMsg("Redo: Label restored.");
    }
}