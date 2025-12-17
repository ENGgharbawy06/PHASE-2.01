#include "XOR2.h"

XOR2::XOR2(const GraphicsInfo& r_GfxInfo, int r_FanOut) :Gate(2, r_FanOut)
{
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;

	m_InputPins[0].setPosition(m_GfxInfo.x1, m_GfxInfo.y1 + 16);
	m_InputPins[1].setPosition(m_GfxInfo.x1, m_GfxInfo.y2 - 17);
}


void XOR2::SetGraphicsInfo(GraphicsInfo NewGfx)
{
	
	Component::SetGraphicsInfo(NewGfx);

	
	m_InputPins[0].setPosition(m_GfxInfo.x1, m_GfxInfo.y1 + 16);	
	m_InputPins[1].setPosition(m_GfxInfo.x1, m_GfxInfo.y2 - 17);
}


void XOR2::Operate()
{
	STATUS in1 = m_InputPins[0].getStatus();
	STATUS in2 = m_InputPins[1].getStatus();
	
	if (in1 != in2) 
		m_OutputPin.setStatus(HIGH);
	else
		m_OutputPin.setStatus(LOW);
}



void XOR2::Draw(Output* pOut)
{
	
	pOut->DrawXOR2(m_GfxInfo, selected);
}


int XOR2::GetOutPinStatus()
{
	return m_OutputPin.getStatus();
}


int XOR2::GetInputPinStatus(int n)
{
	return m_InputPins[n - 1].getStatus();	
}


void XOR2::setInputPinStatus(int n, STATUS s)
{
	m_InputPins[n - 1].setStatus(s);
}


Component* XOR2::Clone(const GraphicsInfo& newGfx) const
{
	return new XOR2(newGfx, XOR2_FANOUT);
}


void XOR2::Save(ofstream& out)
{
	out << "XOR2 "
		<< GetID() << " "
		<< (GetLabel() == "" ? "$" : GetLabel()) << " "
		<< m_GfxInfo.x1 << " " << m_GfxInfo.y1 << "\n";
}

void XOR2::Load(ifstream& in)
{
	int id, x, y;
	string lbl;

	in >> id >> lbl >> x >> y;

	SetID(id);
	if (lbl != "$")
		SetLabel(lbl);

	m_GfxInfo.x1 = x;
	m_GfxInfo.y1 = y;

	m_GfxInfo.x2 = x + UI.XOR2_Width;
	m_GfxInfo.y2 = y + UI.XOR2_Height;

	m_InputPins[0].setPosition(m_GfxInfo.x1, m_GfxInfo.y1 + 16);
	m_InputPins[1].setPosition(m_GfxInfo.x1, m_GfxInfo.y2 - 17);
}

XOR2::~XOR2()
{
}