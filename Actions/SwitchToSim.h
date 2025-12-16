#ifndef SWITCH_TO_SIM_H
#define SWITCH_TO_SIM_H

#include "Action.h"

class SwitchToSim : public Action
{
public:
	SwitchToSim(ApplicationManager* pApp);
	virtual ~SwitchToSim();

	virtual void ReadActionParameters();
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();
};

#endif