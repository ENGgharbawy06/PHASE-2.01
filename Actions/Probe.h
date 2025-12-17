#ifndef _PROBE_H
#define _PROBE_H

#include "Action.h"

class Probe : public Action
{
public:
	Probe(ApplicationManager* pApp);
	virtual ~Probe();

	virtual void ReadActionParameters();
	virtual void Execute();
	virtual void Undo();
	virtual void Redo();
};

#endif