#include "BUFF.h"

BUFF::BUFF(const GraphicsInfo &r_GfxInfo, int r_FanOut) :Gate(1, r_FanOut)
{
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;	

	m_InputPins[0].setPosition(m_GfxInfo.x1, (m_GfxInfo.y1 + m_GfxInfo.y2) / 2);

}

void BUFF::SetGraphicsInfo(GraphicsInfo NewGfx)
{
	Component::SetGraphicsInfo(NewGfx);

	
	m_InputPins[0].setPosition(m_GfxInfo.x1, (m_GfxInfo.y1 + m_GfxInfo.y2) / 2);
}

void BUFF::Operate()	
{
	int inputStatus = GetInputPinStatus(1);
	if (inputStatus == LOW) {
		m_OutputPin.setStatus(LOW);
	} else {
		m_OutputPin.setStatus(HIGH);
	}
}

void BUFF::Draw(Output* pOut)
{
	
	pOut->DrawBUFF(m_GfxInfo, selected);
}
int BUFF::GetOutPinStatus()	
{
	return m_OutputPin.getStatus();
}

int BUFF::GetInputPinStatus(int n)	
{
	return m_InputPins[n - 1].getStatus();	
}

void BUFF::setInputPinStatus(int n, STATUS s)	
{
	m_InputPins[n - 1].setStatus(s);
}


Component* BUFF::Clone(const GraphicsInfo& newGfx) const
{
	return new BUFF(newGfx,BUFF_FANOUT);
}


void BUFF::Save(ofstream& out)
{
	out << "BUFF "
		<< GetID() << " "
		<< (GetLabel() == "" ? "$" : GetLabel()) << " "
		<< m_GfxInfo.x1 << " " << m_GfxInfo.y1 << "\n";
}


void BUFF::Load(ifstream& in)
{
	int id, x, y;
	string lbl;

	in >> id >> lbl >> x >> y;

	SetID(id);
	if (lbl != "$")
		SetLabel(lbl);

	m_GfxInfo.x1 = x;
	m_GfxInfo.y1 = y;

	m_GfxInfo.x2 = x + UI.BUFF_Width;
	m_GfxInfo.y2 = y + UI.BUFF_Height;

	m_InputPins[0].setPosition(m_GfxInfo.x1, (m_GfxInfo.y1 + m_GfxInfo.y2) / 2);
}


BUFF::~BUFF()
{
}