#include "XOR2.h"

XOR2::XOR2(const GraphicsInfo& r_GfxInfo, int r_FanOut) :Gate(2, r_FanOut)
{
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;

	m_InputPins[0].setPosition(m_GfxInfo.x1, m_GfxInfo.y1 + 15);
	m_InputPins[1].setPosition(m_GfxInfo.x1, m_GfxInfo.y2 - 15);
}


void XOR2::SetGraphicsInfo(GraphicsInfo NewGfx)
{
	// 1. تحديث إحداثيات البوابة نفسها باستخدام دالة الأب
	Component::SetGraphicsInfo(NewGfx);

	// 2. تحديث إحداثيات الـ Pins بناءً على المكان الجديد
	// Pin 1 (Top)
	m_InputPins[0].setPosition(m_GfxInfo.x1, m_GfxInfo.y1 + 15);

	// Pin 2 (Bottom)
	m_InputPins[1].setPosition(m_GfxInfo.x1, m_GfxInfo.y2 - 15);
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


// Function Draw
// Draws 2-input XOR gate
void XOR2::Draw(Output* pOut)
{
	//Call output class and pass gate drawing info to it.
	pOut->DrawXOR2(m_GfxInfo, selected);
}

//returns status of outputpin
int XOR2::GetOutPinStatus()
{
	return m_OutputPin.getStatus();
}


//returns status of Inputpin #n
int XOR2::GetInputPinStatus(int n)
{
	return m_InputPins[n - 1].getStatus();	//n starts from 1 but array index starts from 0.
}

//Set status of an input pin ot HIGH or LOW
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

	m_InputPins[0].setPosition(m_GfxInfo.x1, m_GfxInfo.y1 + 15);
	m_InputPins[1].setPosition(m_GfxInfo.x1, m_GfxInfo.y2 - 15);
}

XOR2::~XOR2()
{
}