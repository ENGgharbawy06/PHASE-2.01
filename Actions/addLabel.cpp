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
	// Destructor

}

void AddLabel::ReadActionParameters()
{
    Output* pOut = pManager->GetOutput();
    Input* pIn = pManager->GetInput();

    // Step 1: Ask user to select a component
    pOut->PrintMsg("Click on a component to add a label");

    int x, y;
    pIn->GetPointClicked(x, y);

    // Find the component at clicked position
    Component* pComp = pManager->GetComponentAt(x, y);

    if (!pComp)
    {
        pOut->PrintMsg("No component selected! Action canceled.");
        return;
    }

    // Step 2: Get label text from user
    pOut->PrintMsg("Enter label text:");
    labelText = pIn->GetString(pOut);

    if (labelText.empty())
    {
        pOut->PrintMsg("No text entered! Action canceled.");
        return;
    }

    // Step 3: Get component graphics info to position label
    GraphicsInfo compGfx = pComp->GetGraphicsInfo();

    // Position label above the component
    labelGfx.x1 = (compGfx.x1 + compGfx.x2) / 2 - 20; // Center horizontally
    labelGfx.y1 = compGfx.y1 - 20; // 20 pixels above component
    labelGfx.x2 = labelGfx.x1 + 40;
    labelGfx.y2 = labelGfx.y1 + 15;
}

void AddLabel::Execute()
{
    ReadActionParameters();

    // Check if we got valid parameters
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