#ifndef _DELETE_H
#define _DELETE_H

#include "Action.h"

class Component;

class Delete : public Action
{
    Component* CompToDelete;

public:
    Delete(ApplicationManager* pApp);

    virtual void ReadActionParameters();
    virtual void Execute();

    virtual void Undo();
    virtual void Redo();
};

#endif