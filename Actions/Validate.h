#pragma once
#include "Action.h"

class Validate : public Action
{
public:
	Validate(ApplicationManager* pApp);
	virtual ~Validate();

	virtual void ReadActionParameters();
	virtual void Execute();
	virtual void Undo();
	virtual void Redo();
};