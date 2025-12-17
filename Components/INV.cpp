#include "INV.h"

INV::INV(const GraphicsInfo &r_GfxInfo, int r_FanOut) :Gate(1, r_FanOut)
{
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;

	m_InputPins[0].setPosition(m_GfxInfo.x1, (m_GfxInfo.y1 + m_GfxInfo.y2) / 2);
}

void INV::SetGraphicsInfo(GraphicsInfo NewGfx)
{
	Component::SetGraphicsInfo(NewGfx);

	
	m_InputPins[0].setPosition(m_GfxInfo.x1, (m_GfxInfo.y1 + m_GfxInfo.y2) / 2);
}

void INV::Operate()
{
	STATUS in1 = m_InputPins[0].getStatus();
	if (in1 == HIGH)
		m_OutputPin.setStatus(LOW);
	else
		m_OutputPin.setStatus(HIGH);
}

void INV::Draw(Output* pOut)
{
	
	pOut->DrawINV(m_GfxInfo, selected);
}

int INV::GetOutPinStatus()
{
	return m_OutputPin.getStatus();
}

int INV::GetInputPinStatus(int n)
{
	return m_InputPins[n - 1].getStatus();	
}

void INV::setInputPinStatus(int n, STATUS s)
{
	m_InputPins[n - 1].setStatus(s);

}


Component* INV::Clone(const GraphicsInfo& newGfx) const
{
	return new INV(newGfx, INV_FANOUT);
}


void INV::Save(ofstream& out)
{
	out << "INV "
		<< GetID() << " "
		<< (GetLabel() == "" ? "$" : GetLabel()) << " "
		<< m_GfxInfo.x1 << " " << m_GfxInfo.y1 << "\n";
}



void INV::Load(ifstream& in)
{
	int id, x, y;
	string lbl;

	in >> id >> lbl >> x >> y;

	SetID(id);
	if (lbl != "$")
		SetLabel(lbl);

	m_GfxInfo.x1 = x;
	m_GfxInfo.y1 = y;

	
	m_GfxInfo.x2 = x + UI.INV_Width;
	m_GfxInfo.y2 = y + UI.INV_Height;

	
	m_InputPins[0].setPosition(
		m_GfxInfo.x1,
		(m_GfxInfo.y1 + m_GfxInfo.y2) / 2
	);
}



INV::~INV()
{
}