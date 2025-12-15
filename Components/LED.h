#include "LED.h"

LED::LED(const GraphicsInfo& r_GfxInfo, int r_FanOut) : Component(r_GfxInfo)
{
	// Must associate this Pin with the component so the Connection class can link to it
	m_InputPin.setComponent(this);
}

void LED::Operate()
{
}

void LED::Draw(Output* pOut)
{
	// Logic: If input pin is HIGH, draw the Highlighted image (Lit up)
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

// Since the LED is an output component, it has no output pin.
int LED::GetOutPinStatus()
{
	return -1;
}

int LED::GetInputPinStatus(int n)
{
	return m_InputPin.getStatus();
}

// Set status of the input pin (used by the Connection class)
void LED::setInputPinStatus(int n, STATUS s)
{
	m_InputPin.setStatus(s);
}

Component* LED::Clone(const GraphicsInfo& gfx) const
{
	return new LED(gfx, 1); // Pass dummy fanout
}

// IMPLEMENTATION of the function declared in .h
InputPin* LED::GetInputPin()
{
	return &m_InputPin;
}