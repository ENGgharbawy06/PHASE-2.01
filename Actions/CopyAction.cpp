﻿#include "CopyAction.h"
#include "../ApplicationManager.h"
#include "../GUI/Output.h"
#include "../GUI/Input.h"
#include "../Components/Component.h"

CopyAction::CopyAction(ApplicationManager* pApp) : Action(pApp) {}

// No parameters needed to read for copy action
void CopyAction::ReadActionParameters() {}

void CopyAction::Execute()
{
    // Get pointers to output and input interfaces
    Output* pOut = pManager->GetOutput();
    Input* pIn = pManager->GetInput();

    // Prompt user to select a component
    pOut->PrintMsg("Select a component to COPY...");

    // Get mouse click coordinates
    int x, y;
    pIn->GetPointClicked(x, y);

    // Find component at clicked position
    Component* comp = pManager->GetComponentAt(x, y);

    // Check if a component was found
    if (!comp)
    {
        pOut->PrintMsg("No component selected!");
        return; // Exit if no component selected
    }

    // Clone the selected component
    Component* copied = comp->Clone(comp->GetGraphicsInfo());
    // Store the cloned component in clipboard
    pManager->SetClipboard(copied);

    // Confirm successful copy
    pOut->PrintMsg("Component copied!");
}