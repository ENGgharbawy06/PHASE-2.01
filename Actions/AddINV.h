#ifndef _ADD_INV_H
#define _ADD_INV_H

#include "action.h"
#include "..\Components\INV.h"

class AddINV : public Action
{
private:
    int Cx, Cy;
    int x1, y1, x2, y2;

public:
    AddINV(ApplicationManager* pApp);
    virtual ~AddINV();

    virtual void ReadActionParameters();
    virtual void Execute();
    virtual void Undo();
    virtual void Redo();
};

#endif
