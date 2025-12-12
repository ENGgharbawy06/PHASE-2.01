#pragma once
#ifndef ACTION_DELETE_H
#define ACTION_DELETE_H
#include "Action.h"
#include "..\UI\UI.h"
#include <vector>
class ActionDelete : public Action
{
private:
    std::vector<Component*> DeletedComponents;
    std::vector<int> DeletedIndices;
public:
    ActionDelete(ApplicationManager* pApp);
    virtual void ReadActionParameters();
    virtual void Execute();
    virtual void Undo();
    virtual void Redo();
};
#endif