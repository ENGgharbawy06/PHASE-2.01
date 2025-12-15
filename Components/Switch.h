#pragma once
#include "Gate.h"

class Switch : public Gate
{
public:
	Switch(const GraphicsInfo& r_GfxInfo, int r_FanOut);

	virtual void Operate();	// Calculates the output according to the selection status
	virtual void Draw(Output* pOut); // Draws the switch

	virtual int GetOutPinStatus();	// returns status of outputpin
	virtual int GetInputPinStatus(int n);	// returns -1 as switch has no inputs
	virtual void setInputPinStatus(int n, STATUS s); // does nothing

	virtual Component* Clone(const GraphicsInfo& newGfx) const;
	virtual void SetGraphicsInfo(GraphicsInfo NewGfx);
};