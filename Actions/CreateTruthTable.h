#pragma once
#include "Action.h"
#include "..\Components\Component.h"

class CreateTruthTable : public Action
{
private:
	// Dynamic arrays (pointers to pointers)
	Component** m_SwitchList;
	Component** m_LEDList;

	int m_NumSwitches;
	int m_NumLEDs;

public:
	CreateTruthTable(ApplicationManager* pApp);
	virtual ~CreateTruthTable();

	virtual void ReadActionParameters();
	virtual void Execute();
	virtual void Undo();
	virtual void Redo();
};