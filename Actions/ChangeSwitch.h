#ifndef _Change_SWITCH_H
#define _Change_SWITCH_H

#include "Action.h"
#include "..\Components\Switch.h"

class ChangeSwitch : public Action
{
public:
	ChangeSwitch(ApplicationManager* pApp);
	virtual ~ChangeSwitch(void);

	
	virtual void ReadActionParameters();


	
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();
};

#endif