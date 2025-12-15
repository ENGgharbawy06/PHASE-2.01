#include "Switch.h"

Switch::Switch(const GraphicsInfo& r_GfxInfo, int r_FanOut) :Gate(0, r_FanOut)
{
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;

	
}

void Switch::Operate()
{
	// Logic: If the switch is selected (toggled), it acts as ON (HIGH).
	// Otherwise, it is OFF (LOW).
	if (selected)
		m_OutputPin.setStatus(HIGH);
	else
		m_OutputPin.setStatus(LOW);
}

void Switch::Draw(Output* pOut)
{
	// Call output class and pass switch drawing info and selection state
	pOut->DrawSWITCH(m_GfxInfo, selected);
}

int Switch::GetOutPinStatus()
{
	return m_OutputPin.getStatus();
}

int Switch::GetInputPinStatus(int n)
{
	return -1; // Switch has no input pins
}

void Switch::setInputPinStatus(int n, STATUS s)
{
	// Switch has no input pins to set
}

Component* Switch::Clone(const GraphicsInfo& newGfx) const
{
	return new Switch(newGfx, SWITCH_FANOUT);
}

void Switch::SetGraphicsInfo(GraphicsInfo NewGfx)
{
	Component::SetGraphicsInfo(NewGfx);
	m_GfxInfo = NewGfx;

}