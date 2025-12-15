#include "AND2.h"

AND2::AND2(const GraphicsInfo &r_GfxInfo, int r_FanOut):Gate(2, r_FanOut)
{
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;

	m_InputPins[0].setPosition(m_GfxInfo.x1, m_GfxInfo.y1 + 15);

	m_InputPins[1].setPosition(m_GfxInfo.x1, m_GfxInfo.y2 - 15);
	
}


void AND2::Operate()
{
	
	STATUS in1 = m_InputPins[0].getStatus();
	STATUS in2 = m_InputPins[1].getStatus();

	if (in1 == HIGH && in2 == HIGH)
		m_OutputPin.setStatus(HIGH);
	else
		m_OutputPin.setStatus(LOW);

}


// Function Draw
// Draws 2-input AND gate
void AND2::Draw(Output* pOut)
{
	//Call output class and pass gate drawing info to it.
	pOut->DrawAND2(m_GfxInfo,selected);
}

//returns status of outputpin
int AND2::GetOutPinStatus()	
{
	return m_OutputPin.getStatus();
}


//returns status of Inputpin #n
int AND2::GetInputPinStatus(int n)	
{
	return m_InputPins[n-1].getStatus();	//n starts from 1 but array index starts from 0.
}

//Set status of an input pin ot HIGH or LOW
void AND2::setInputPinStatus(int n, STATUS s)
{
	m_InputPins[n-1].setStatus(s);
}

//
Component* AND2::Clone(const GraphicsInfo& newGfx) const
{
	return new AND2(newGfx, AND2_FANOUT);

}

void AND2::SetGraphicsInfo(GraphicsInfo NewGfx)
{
	Component::SetGraphicsInfo(NewGfx); // تحديث مكان البوابة الأساسي

	// تحديث مكان الـ Pins عشان تمشي مع البوابة
	m_GfxInfo.x1 = NewGfx.x1;
	m_GfxInfo.y1 = NewGfx.y1;
	m_GfxInfo.x2 = NewGfx.x2;
	m_GfxInfo.y2 = NewGfx.y2;

	// نفس الكود اللي في الـ Constructor
	m_InputPins[0].setPosition(m_GfxInfo.x1, m_GfxInfo.y1 + 15);
	m_InputPins[1].setPosition(m_GfxInfo.x1, m_GfxInfo.y2 - 15);
}

void AND2::Save(ofstream& out)
{
	out << "AND2 "
		<< GetID() << " "
		<< (GetLabel() == "" ? "$" : GetLabel()) << " "
		<< m_GfxInfo.x1 << " " << m_GfxInfo.y1 << "\n";
}

void AND2::Load(ifstream& in)
{
	int id, x, y;
	string lbl;

	in >> id >> lbl >> x >> y;

	SetID(id);
	if (lbl != "$")
		SetLabel(lbl);

	m_GfxInfo.x1 = x;
	m_GfxInfo.y1 = y;

	// حجم ال AND2 حسب UI عندك
	m_GfxInfo.x2 = x + UI.AND2_Width;
	m_GfxInfo.y2 = y + UI.AND2_Height;

	// إعادة ضبط أماكن Pins
	m_InputPins[0].setPosition(m_GfxInfo.x1, m_GfxInfo.y1 + 15);
	m_InputPins[1].setPosition(m_GfxInfo.x1, m_GfxInfo.y2 - 15);
}
