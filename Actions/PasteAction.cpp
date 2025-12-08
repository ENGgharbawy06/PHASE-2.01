#include "PasteAction.h"
#include "../ApplicationManager.h"
#include "../Components/Component.h"

// Constructor
PasteAction::PasteAction(ApplicationManager* pApp)
    : Action(pApp)
{
}
// Execute the paste action
void PasteAction::Execute()
{
    Output* pOut = pManager->GetOutput();
    Input* pIn = pManager->GetInput();

    // Get component from clipboard
    Component* clip = pManager->GetClipboard();

    // Check if clipboard is empty
    if (!clip)
    {
        pOut->PrintMsg("Clipboard empty!");
        return;
    }

    // Get paste location from user click
    int x, y;
    pIn->GetPointClicked(x, y);

    // Set new position for pasted component (centered 100x100 box)
    GraphicsInfo newGfx;
    newGfx.x1 = x - 50;
    newGfx.y1 = y - 50;
    newGfx.x2 = x + 50;
    newGfx.y2 = y + 50;

    // Clone component to new location
    Component* pasted = clip->Clone(newGfx);

    // Validate clone succeeded
    if (!pasted)
    {
        pOut->PrintMsg("Cannot paste this component");
        return;
    }

    // Add to component list
    pManager->AddComponent(pasted);
    pOut->PrintMsg("Pasted!");
}

// No parameters to read
void PasteAction::ReadActionParameters() {}