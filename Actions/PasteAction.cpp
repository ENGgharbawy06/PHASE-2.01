#include "PasteAction.h"
#include "../ApplicationManager.h"
#include "../GUI/Input.h"
#include "../GUI/Output.h"
#include "../Components/Component.h"

PasteAction::PasteAction(ApplicationManager* pApp)
    : Action(pApp), m_PastedComp(nullptr)
{
}

void PasteAction::ReadActionParameters() {}

void PasteAction::Execute()
{
    Output* pOut = pManager->GetOutput();
    Input* pIn = pManager->GetInput();

    Component* pClip = pManager->GetClipboard();
    if (!pClip)
    {
        pOut->PrintMsg("Paste failed: Clipboard is empty");
        return;
    }

    pOut->PrintMsg("Click to paste component");

    int x, y;
    pIn->GetPointClicked(x, y);

    GraphicsInfo gfx = pClip->GetGraphicsInfo();

    int width = gfx.x2 - gfx.x1;
    int height = gfx.y2 - gfx.y1;

    gfx.x1 = x - width / 2;
    gfx.y1 = y - height / 2;
    gfx.x2 = gfx.x1 + width;
    gfx.y2 = gfx.y1 + height;

    // CLONE happens here
    m_PastedComp = pClip->Clone(gfx);
    pManager->AddComponent(m_PastedComp);

    pOut->PrintMsg("Component pasted");
}

void PasteAction::Undo()
{
    if (m_PastedComp)
        pManager->RemoveComponent(m_PastedComp);
}

void PasteAction::Redo()
{
    if (m_PastedComp)
        pManager->AddComponent(m_PastedComp);
}
