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
	//Law el switch kan ON/OFF, el output hayeb2a HIGH (1) / LOW(0)
	//El output pin di heya one of the input pins lel gates
	if (selected)
		m_OutputPin.setStatus(HIGH);
	else
		m_OutputPin.setStatus(LOW);
}

void Switch::Draw(Output* pOut)
{
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