#ifndef SELECT_H
#define SELECT_H

#include "Action.h"

class Select : public Action // Inheretance mn el action
{
private:
    int x, y; // To store the coordinates of the click
public:
    Select(ApplicationManager* pApp);
    virtual void ReadActionParameters();
    virtual void Execute();
    virtual void Undo();
    virtual void Redo();
};

#endif