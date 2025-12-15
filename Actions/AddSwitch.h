#ifndef _ADD_SWITCH_H
#define _ADD_SWITCH_H

#include "Action.h"
#include "..\Components\Switch.h"

class AddSwitch : public Action
{
private:
	//Parameters for rectangular area to be occupied by the Switch
	int Cx, Cy;	//Center point of the component
	int x1, y1, x2, y2;	//Two corners of the rectangluar area
public:
	AddSwitch(ApplicationManager* pApp);
	virtual ~AddSwitch(void);

	//Reads parameters required for action to execute
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();

	Switch(const GraphicsInfo& r_GfxInfo, int r_FanOut);

	virtual void Operate();
	virtual void Draw(Output* pOut);

	virtual int GetOutPinStatus();
	virtual int GetInputPinStatus(int n);
	virtual void setInputPinStatus(int n, STATUS s);

	virtual Component* Clone(const GraphicsInfo& newGfx) const;

	// Function required by CreateTruthTable
	void SetStatus(STATUS s);
	virtual void SetGraphicsInfo(GraphicsInfo NewGfx);

	virtual void Undo();
	virtual void Redo();
};

#endif
