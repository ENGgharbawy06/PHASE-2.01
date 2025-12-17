#ifndef _TOGGLE_SWITCHES_H
#define _TOGGLE_SWITCHES_H

#include "Action.h"
#include "../Components/Switch.h"

class TOGGLE_SWITCHES : public Action
{
private:
	int x, y;          // Coordinates where the user clicked
	Switch* pSwitch;   // Pointer to the switch being toggled
	bool oldState;     // To store the state before toggling (for Undo)

public:
	TOGGLE_SWITCHES(ApplicationManager* pApp);
	virtual ~TOGGLE_SWITCHES();

	virtual void ReadActionParameters();
	virtual void Execute();
	virtual void Undo();
	virtual void Redo();
};

#endif
TOGGLE_SWITCHES