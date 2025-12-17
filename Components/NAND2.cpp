#include "NAND2.h"
NAND2::NAND2(const GraphicsInfo &r_GfxInfo, int r_FanOut):Gate(2, r_FanOut)
{
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;

	m_InputPins[0].setPosition(m_GfxInfo.x1, m_GfxInfo.y1 + 17);
	m_InputPins[1].setPosition(m_GfxInfo.x1, m_GfxInfo.y2 - 15);
}

void NAND2::SetGraphicsInfo(GraphicsInfo NewGfx)
{
	Component::SetGraphicsInfo(NewGfx);

	
	m_InputPins[0].setPosition(m_GfxInfo.x1, m_GfxInfo.y1 + 17);

	
	m_InputPins[1].setPosition(m_GfxInfo.x1, m_GfxInfo.y2 - 15);
}

void NAND2::Operate()
{
	STATUS in1 = m_InputPins[0].getStatus();
	STATUS in2 = m_InputPins[1].getStatus();
	
	if (in1 == LOW || in2 == LOW)
		m_OutputPin.setStatus(HIGH);
	else
		m_OutputPin.setStatus(LOW);
}

void NAND2::Draw(Output* pOut)
{
	
	pOut->DrawNAND2(m_GfxInfo, selected);
}

int NAND2::GetOutPinStatus()	
{
	return m_OutputPin.getStatus();
}

int NAND2::GetInputPinStatus(int n)	
{
	return m_InputPins[n-1].getStatus();	
}

void NAND2::setInputPinStatus(int n, STATUS s)
{
	m_InputPins[n-1].setStatus(s);
}



Component* NAND2::Clone(const GraphicsInfo& newGfx) const
{
	return new NAND2(newGfx, NAND2_FANOUT);
}


void NAND2::Save(ofstream& out)
{
	out << "NAND2 "
		<< GetID() << " "
		<< (GetLabel() == "" ? "$" : GetLabel()) << " "
		<< m_GfxInfo.x1 << " " << m_GfxInfo.y1 << "\n";
}

void NAND2::Load(ifstream& in)
{
	int id, x, y;
	string lbl;

	in >> id >> lbl >> x >> y;

	SetID(id);

	if (lbl != "$")
		SetLabel(lbl);

	m_GfxInfo.x1 = x;
	m_GfxInfo.y1 = y;

	
	m_GfxInfo.x2 = x + UI.NAND2_Width;
	m_GfxInfo.y2 = y + UI.NAND2_Height;

	
	m_InputPins[0].setPosition(m_GfxInfo.x1, m_GfxInfo.y1 + 17);
	m_InputPins[1].setPosition(m_GfxInfo.x1, m_GfxInfo.y2 - 15);
}




NAND2::~NAND2()
{
}
