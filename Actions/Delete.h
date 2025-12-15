#ifndef _DELETE_H
#define _DELETE_H

#include "Action.h"
#include "../Components/Component.h"

class Delete : public Action
{
private:
    Component* DeletedArray[200];   // fixed-size array
    int DeletedCount;               // how many components deleted

public:
    Delete(ApplicationManager* pApp);

    virtual void ReadActionParameters();
    virtual void Execute();
    virtual void Undo();
    virtual void Redo();

    virtual bool isUndoable() const { return true; }
};

#endif
