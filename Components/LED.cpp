#include "LED.h"

LED::LED(const GraphicsInfo& r_GfxInfo) : Component(r_GfxInfo)
{
	// Must associate this Pin with the component so the Connection class can link to it
	m_InputPin.setComponent(this);
}

void LED::Operate()
{
	//empty function: LED operation is done in Draw
}

void LED::Draw(Output* pOut)
{
	// Check the Pin status: if High, draw lit up; if Low, draw unlit.

	if (m_InputPin.getStatus() == HIGH)
	{
		// true means lit up (Active)
		pOut->DrawLED(m_GfxInfo, true);
	}
	else
	{
		// false means unlit
		pOut->DrawLED(m_GfxInfo, false);
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

	return new LED(gfx);
}