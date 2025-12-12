#ifndef _BUFF_H
#define _BUFF_H
#include "Gate.h"
class BUFF : public Gate 
{
	public:
	BUFF(const GraphicsInfo &r_GfxInfo, int r_FanOut);
	virtual void Operate();	//Calculates the output according to the inputs
	virtual void Draw(Output* pOut);	//for each component to Draw itself
	virtual int GetOutPinStatus();	//returns status of outputpin if LED, return -1
	virtual int GetInputPinStatus(int n);	//returns status of Inputpin # n if SWITCH, return -1
	virtual void setInputPinStatus(int n, STATUS s);	//set status of Inputpin # n, to be used by connection class.
	virtual Component* Clone(const GraphicsInfo& newGfx) const override; // Clone function to create a copy of the component
	virtual ~BUFF();


};
#endif