#include "XNOR2.h"


XNOR2::XNOR2(const GraphicsInfo& r_GfxInfo, int r_FanOut) :Gate(2, r_FanOut)
{
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;

	m_InputPins[0].setPosition(m_GfxInfo.x1, m_GfxInfo.y1 + 16);
	m_InputPins[1].setPosition(m_GfxInfo.x1, m_GfxInfo.y2 - 17);

}

void XNOR2::SetGraphicsInfo(GraphicsInfo NewGfx)
{
	
	Component::SetGraphicsInfo(NewGfx);

	
	m_InputPins[0].setPosition(m_GfxInfo.x1, m_GfxInfo.y1 + 16);

	
	m_InputPins[1].setPosition(m_GfxInfo.x1, m_GfxInfo.y2 - 17);
}

void XNOR2::Operate()
{
	STATUS in1 = m_InputPins[0].getStatus();
	STATUS in2 = m_InputPins[1].getStatus();

	if ((in1 == HIGH && in2 == HIGH) || (in1 == LOW && in2 == LOW))
		m_OutputPin.setStatus(HIGH);
	else
		m_OutputPin.setStatus(LOW);
}

void XNOR2::Draw(Output* pOut)
{
	
	pOut->DrawXNOR2(m_GfxInfo, selected);
}

int XNOR2::GetOutPinStatus()
{
	return m_OutputPin.getStatus();
}

int XNOR2::GetInputPinStatus(int n)
{
	return m_InputPins[n - 1].getStatus();	
}

void XNOR2::setInputPinStatus(int n, STATUS s)
{
	m_InputPins[n - 1].setStatus(s);
}


Component* XNOR2::Clone(const GraphicsInfo& newGfx) const
{
	return new XNOR2(newGfx, XNOR2_FANOUT);
}

void XNOR2::Save(ofstream& out)
{
	out << "XNOR2 "
		<< GetID() << " "
		<< (GetLabel() == "" ? "$" : GetLabel()) << " "
		<< m_GfxInfo.x1 << " " << m_GfxInfo.y1 << "\n";
}

void XNOR2::Load(ifstream& in)
{
	int id, x, y;
	string lbl;

	in >> id >> lbl >> x >> y;

	SetID(id);
	if (lbl != "$")
		SetLabel(lbl);

	m_GfxInfo.x1 = x;
	m_GfxInfo.y1 = y;

	m_GfxInfo.x2 = x + UI.XNOR2_Width;
	m_GfxInfo.y2 = y + UI.XNOR2_Height;

	m_InputPins[0].setPosition(m_GfxInfo.x1, m_GfxInfo.y1 + 15);
	m_InputPins[1].setPosition(m_GfxInfo.x1, m_GfxInfo.y2 - 15);
}

XNOR2::~XNOR2()
{
}