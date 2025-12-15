#include "LED.h"

LED::LED(const GraphicsInfo& r_GfxInfo, int r_FanOut) : Component(r_GfxInfo)
{
	// Associate the input pin with this component
	m_InputPin.setComponent(this);
}

void LED::Operate()
{
	// LED has no logical operation affecting outputs, it's visual.
}

void LED::Draw(Output* pOut)
{
	// If input pin is HIGH, draw the Highlighted image (Lit up)
	// Otherwise, draw the normal image (Dark)
	if (m_InputPin.getStatus() == HIGH)
	{
		pOut->DrawLED(m_GfxInfo, true); // true = draw highlighted
	}
	else
	{
		pOut->DrawLED(m_GfxInfo, false); // false = draw normal
	}
}

int LED::GetOutPinStatus()
{
	return -1; // LED has no output pin
}

int LED::GetInputPinStatus(int n)
{
	return m_InputPin.getStatus();
}

void LED::setInputPinStatus(int n, STATUS s)
{
	m_InputPin.setStatus(s);
}

Component* LED::Clone(const GraphicsInfo& gfx) const
{
	return new LED(gfx, 1);
}

InputPin* LED::GetInputPin()
{
	return &m_InputPin;
}