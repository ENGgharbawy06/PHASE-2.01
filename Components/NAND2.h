#ifndef _NAND2_H
#define _NAND2_H


#pragma
#include "Gaate.h"

class NAND2 : public Gate
{
	NAND2(const GraphicsInfo& r_GfxInfo, int r_FanOut);
	virtual void Operate();	//Calculates the output of the AND gate
	virtual void Draw(Output* pOut);	//Draws 2-input gate

	virtual int GetOutPinStatus();	//returns status of outputpin if LED, return -1
	virtual int GetInputPinStatus(int n);	//returns status of Inputpin # n if SWITCH, return -1

	virtual void setInputPinStatus(int n, STATUS s);	//set status of Inputpin # n, to be used by connection class.
	virtual Component* Clone(const GraphicsInfo& newGfx) const override; // Clone function to create a copy of the component




}

#endif
