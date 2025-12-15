#pragma once
#ifndef _LOAD_ACTION_H
#define _LOAD_ACTION_H

#include "Action.h"
#include <fstream>

class LoadAction : public Action
{
public:
    LoadAction(ApplicationManager* pApp);

    virtual void ReadActionParameters();
    virtual void Execute();
    virtual void Undo() {}
    virtual void Redo() {}

    virtual bool isUndoable() { return false; }
};

#endif
