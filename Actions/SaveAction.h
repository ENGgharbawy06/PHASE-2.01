#pragma once
#ifndef _SAVE_ACTION_H
#define _SAVE_ACTION_H

#include "Action.h"
#include <fstream>

class SaveAction : public Action
{
public:
    SaveAction(ApplicationManager* pApp);

    virtual void ReadActionParameters();
    virtual void Execute();
    virtual void Undo() {}
    virtual void Redo() {}

    virtual bool isUndoable() { return false; }
};

#endif
