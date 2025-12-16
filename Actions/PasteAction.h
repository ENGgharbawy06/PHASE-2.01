#pragma once
#include "Action.h"

class Component;

class PasteAction : public Action
{
private:
    Component* m_PastedComp;   // component created by paste

public:
    PasteAction(ApplicationManager* pApp);

    virtual void ReadActionParameters();
    virtual void Execute();
    virtual void Undo();
    virtual void Redo();

    virtual bool isUndoable() const { return true; }
};
