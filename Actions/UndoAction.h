#pragma once
#include "Action.h" 

class UndoAction : public Action
{
public:
	UndoAction(ApplicationManager* pApp) : Action(pApp) {}

	virtual void ReadActionParameters() {}
	virtual void Execute();
	virtual void Undo() {}
	virtual void Redo() {}

	virtual bool isUndoable() const { return false; }

};