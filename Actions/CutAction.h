#ifndef _CUT_ACTION_H
#define _CUT_ACTION_H

#include "Action.h"

class Component;

class CutAction : public Action
{
private:
    Component* CompToCut;  // Component to be cut

public:
    CutAction(ApplicationManager* pApp);

    virtual void ReadActionParameters();
    virtual void Execute();

    virtual void Undo() {}
    virtual void Redo() {}
    virtual bool isUndoable() const { return true; }
};

#endif
