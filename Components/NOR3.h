#pragma once
#ifndef _NOR3_H
#define _NOR3_H

	

#include "Gate.h"

	class NOR3 :public Gate
	{
	public:
		NOR3(const GraphicsInfo& r_GfxInfo, int r_FanOut);
		virtual void Operate();	//Calculates the output of the NOR gate
		virtual void Draw(Output* pOut);	//Draws 3-input gate

		virtual int GetOutPinStatus();	//returns status of outputpin if LED, return -1
		virtual int GetInputPinStatus(int n);	//returns status of Inputpin # n if SWITCH, return -1

		virtual void setInputPinStatus(int n, STATUS s);	//set status of Inputpin # n, to be used by connection class.

		virtual Component* Clone(const GraphicsInfo& newGfx) const override; // Clone function to create a copy of the component
		virtual int GetInputPinCount(); //returns the count of input pins for the NOR gate

	};

#endif


