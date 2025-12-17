#include "LED.h"

LED::LED(const GraphicsInfo& r_GfxInfo, int r_FanOut) : Component(r_GfxInfo)
{
	
	m_InputPin.setComponent(this);
	int pinX = r_GfxInfo.x1 + (r_GfxInfo.x2 - r_GfxInfo.x1) / 2;

	
	int pinY = r_GfxInfo.y2;

	m_InputPin.setPosition(pinX, pinY);
}
void LED::SetGraphicsInfo(GraphicsInfo NewGfx)
{
	Component::SetGraphicsInfo(NewGfx);
	
	int pinX = m_GfxInfo.x1 + (m_GfxInfo.x2 - m_GfxInfo.x1) / 2;
	int pinY = m_GfxInfo.y2; 
	m_InputPin.setPosition(pinX, pinY);
}

InputPin* LED::GetInputPin(int index)
{
	// LED only has 1 pin at index 0
	if (index == 0)
	{
		return &m_InputPin;
	}
	return nullptr;
}


void LED::Operate()
{
	// LED mlhash logical operation effect 3la el output
}

void LED::Draw(Output* pOut)
{
	// lw el input high, draw highlighted image (On)
	// lw la draw normal image (Off)
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
	return -1; // LED m3ndhash input pin
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
void LED::Save(ofstream& out)
{
	out << "LED "
		<< GetID() << " "
		<< (GetLabel() == "" ? "$" : GetLabel()) << " "
		<< m_GfxInfo.x1 << " " << m_GfxInfo.y1 << "\n";
}

void LED::Load(ifstream& in)
{
	int id, x, y;
	string lbl;

	in >> id >> lbl >> x >> y;

	SetID(id);
	if (lbl != "$")
		SetLabel(lbl);

	m_GfxInfo.x1 = x;
	m_GfxInfo.y1 = y;
	m_GfxInfo.x2 = x + UI.LED_Width;
	m_GfxInfo.y2 = y + UI.LED_Height;

	int pinX = m_GfxInfo.x1 + (m_GfxInfo.x2 - m_GfxInfo.x1) / 2;
	int pinY = m_GfxInfo.y2; 
	m_InputPin.setPosition(pinX, pinY);
}