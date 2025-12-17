#include "OR2.h"

OR2::OR2(const GraphicsInfo &r_GfxInfo, int r_FanOut):Gate(2, r_FanOut)
{
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;

	m_InputPins[0].setPosition(m_GfxInfo.x1, m_GfxInfo.y1 + 18);
	m_InputPins[1].setPosition(m_GfxInfo.x1, m_GfxInfo.y2 - 17);
}

void OR2::SetGraphicsInfo(GraphicsInfo NewGfx)
{
	
	Component::SetGraphicsInfo(NewGfx);



	m_InputPins[0].setPosition(m_GfxInfo.x1, m_GfxInfo.y1 + 18);

	
	m_InputPins[1].setPosition(m_GfxInfo.x1, m_GfxInfo.y2 - 17);
}

void OR2::Operate()
{
	STATUS in1 = m_InputPins[0].getStatus();
	STATUS in2 = m_InputPins[1].getStatus();

	if (in1 == HIGH || in2 == HIGH)
		m_OutputPin.setStatus(HIGH);
	else
		m_OutputPin.setStatus(LOW);
}

void OR2::Draw(Output* pOut)
{
	
	pOut->DrawOR2(m_GfxInfo, selected);
}

int OR2::GetOutPinStatus()	
{
	return m_OutputPin.getStatus();
}

int OR2::GetInputPinStatus(int n)	
{
	return m_InputPins[n-1].getStatus();	
}

void OR2::setInputPinStatus(int n, STATUS s)
{
	m_InputPins[n-1].setStatus(s);
}

Component* OR2::Clone(const GraphicsInfo& newGfx) const
{
	return new OR2(newGfx, OR2_FANOUT);
}

void OR2::Save(ofstream& out)
{
	out << "OR2 "
		<< GetID() << " "
		<< (GetLabel() == "" ? "$" : GetLabel()) << " "
		<< m_GfxInfo.x1 << " " << m_GfxInfo.y1 << "\n";
}

void OR2::Load(ifstream& in)
{
	int id, x, y;
	string lbl;

	in >> id >> lbl >> x >> y;

	SetID(id);
	if (lbl != "$")
		SetLabel(lbl);

	m_GfxInfo.x1 = x;
	m_GfxInfo.y1 = y;

	m_GfxInfo.x2 = x + UI.OR2_Width;
	m_GfxInfo.y2 = y + UI.OR2_Height;

	m_InputPins[0].setPosition(m_GfxInfo.x1, m_GfxInfo.y1 + 18);
	m_InputPins[1].setPosition(m_GfxInfo.x1, m_GfxInfo.y2 - 17);
}

OR2::~OR2()
{
}