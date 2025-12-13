#ifndef _COMPONENT_H
#define _COMPONENT_H

#include "..\Defs.h"
#include "..\GUI\Output.h"

//Base class for classes Gate, Switch, and LED.
class Component
{
private:
	string m_Label;
protected:
	GraphicsInfo m_GfxInfo;	//The parameters required to draw a component
	bool selected;
public:
	Component(const GraphicsInfo& r_GfxInfo);
	virtual void Operate() = 0;	//Calculates the output according to the inputs
	virtual void Draw(Output* pOut) = 0;	//for each component to Draw itself


	virtual int GetOutPinStatus() = 0;	//returns status of outputpin if LED, return -1
	virtual int GetInputPinStatus(int n) = 0;	//returns status of Inputpin # n if SWITCH, return -1

	virtual void setInputPinStatus(int n, STATUS s) = 0;	//set status of Inputpin # n, to be used by connection class.
	virtual Component* Clone(const GraphicsInfo& newGfx) const = 0; // Clone function to create a copy of the component
	
	virtual void SetSelected(bool select) { selected = select; }
	virtual bool IsSelected() const { return selected; }

	virtual bool IsInside(int x, int y) {

		if (x >= m_GfxInfo.x1 && x <= m_GfxInfo.x2 && y >= m_GfxInfo.y1 && y <= m_GfxInfo.y2) // Law akbar mn el minimum w a2al mn el maximum hai return true
			return true;
		else
			return false;

	}

	// Get the graphics info of the component
	GraphicsInfo GetGraphicsInfo() const { return m_GfxInfo; }

	Component();

	//3a4an el move action, lazem a3raf eh el coordinates el gdida
	virtual void SetGraphicsInfo(GraphicsInfo NewGfx) {
		m_GfxInfo = NewGfx;
	} 


	//Destructor must be virtual
	virtual ~Component();
};

#endif