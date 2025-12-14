#pragma once
#include "Action.h" 

class RedoAction : public Action
{
public:
	RedoAction(ApplicationManager* pApp) : Action(pApp) {}

	virtual void ReadActionParameters() {}
	virtual void Execute();
	virtual void Undo() {}
	virtual void Redo() {}

	virtual bool isUndoable() const { return false; }

};