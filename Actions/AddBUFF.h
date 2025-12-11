#ifndef _ADD_Buffer_H
#define _ADD_Buffer_H

#include "action.h"
#include "..\Components\BUFF.h"

class AddBuffer : public Action
{
private:
    int Cx, Cy;
    int x1, y1, x2, y2;

public:
    AddBuffer(ApplicationManager* pApp);
    virtual ~AddBuffer();

    virtual void ReadActionParameters();
    virtual void Execute();
    virtual void Undo();
    virtual void Redo();
};

#endif
