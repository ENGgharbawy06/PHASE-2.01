#include "AND3.h"

AND3::AND3(const GraphicsInfo &r_GfxInfo, int r_FanOut):Gate(3, r_FanOut)
{
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;

	// Pin 1 (Top)
	m_InputPins[0].setPosition(m_GfxInfo.x1, m_GfxInfo.y1 + 10);
	// Pin 2 (Middle)
	m_InputPins[1].setPosition(m_GfxInfo.x1, (m_GfxInfo.y1 + m_GfxInfo.y2) / 2);
	// Pin 3 (Bottom)
	m_InputPins[2].setPosition(m_GfxInfo.x1, m_GfxInfo.y2 - 10);
}
	

	void AND3::SetGraphicsInfo(GraphicsInfo NewGfx)
	{
		Component::SetGraphicsInfo(NewGfx);

		// Pin 1 (Top)
		m_InputPins[0].setPosition(m_GfxInfo.x1, m_GfxInfo.y1 + 10);

		// Pin 2 (Middle)
		m_InputPins[1].setPosition(m_GfxInfo.x1, (m_GfxInfo.y1 + m_GfxInfo.y2) / 2);

		// Pin 3 (Bottom)
		m_InputPins[2].setPosition(m_GfxInfo.x1, m_GfxInfo.y2 - 10);
	}

void AND3::Operate()
{

	STATUS in1 = m_InputPins[0].getStatus();
	STATUS in2 = m_InputPins[1].getStatus();
	STATUS in3 = m_InputPins[2].getStatus();

	if (in1 == HIGH && in2 == HIGH && in3 == HIGH)
		m_OutputPin.setStatus(HIGH);
	else
		m_OutputPin.setStatus(LOW);

	
}
// Function Draw	
// Draws 3-input AND gate
void AND3::Draw(Output* pOut)
{
	//Call output class and pass gate drawing info to it.
	pOut->DrawAND3(m_GfxInfo, selected);
}
//returns status of outputpin
int AND3::GetOutPinStatus()	
{
	return m_OutputPin.getStatus();
}
//returns status of Inputpin #n
int AND3::GetInputPinStatus(int n)	
{
	return m_InputPins[n-1].getStatus();	//n starts from 1 but array index starts from 0.
}
//Set status of an input pin ot HIGH or LOW
void AND3::setInputPinStatus(int n, STATUS s)
{
	m_InputPins[n-1].setStatus(s);
}

Component* AND3::Clone(const GraphicsInfo& newGfx) const
{
	return new AND3(newGfx, AND2_FANOUT);

}

void AND3::Save(ofstream& out)
{
	out << "AND3 "
		<< GetID() << " "
		<< (GetLabel() == "" ? "$" : GetLabel()) << " "
		<< m_GfxInfo.x1 << " " << m_GfxInfo.y1 << "\n";
}



void AND3::Load(ifstream& in)
{
	int id, x, y;
	string lbl;

	in >> id >> lbl >> x >> y;

	SetID(id);
	if (lbl != "$")
		SetLabel(lbl);

	m_GfxInfo.x1 = x;
	m_GfxInfo.y1 = y;

	m_GfxInfo.x2 = x + UI.AND3_Width;
	m_GfxInfo.y2 = y + UI.AND3_Height;

	m_InputPins[0].setPosition(m_GfxInfo.x1, m_GfxInfo.y1 + 10);
	m_InputPins[1].setPosition(m_GfxInfo.x1, (m_GfxInfo.y1 + m_GfxInfo.y2) / 2);
	m_InputPins[2].setPosition(m_GfxInfo.x1, m_GfxInfo.y2 - 10);
}




AND3::~AND3()
{
}