#include "XOR3.h"

XOR3::XOR3(const GraphicsInfo& r_GfxInfo, int r_FanOut) :Gate(2, r_FanOut)
{
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;
}


void XOR3::Operate()
{
	STATUS in1 = m_InputPins[0].getStatus();
	STATUS in2 = m_InputPins[1].getStatus();
	STATUS in3 = m_InputPins[2].getStatus();
	if ((in1 == HIGH && in2 == LOW && in3 == LOW) ||
		(in1 == LOW && in2 == HIGH && in3 == LOW) ||
		(in1 == LOW && in2 == LOW && in3 == HIGH) ||
		(in1 == HIGH && in2 == HIGH && in3 == HIGH))
	{
		m_OutputPin.setStatus(HIGH);
	}
	else
	{
		m_OutputPin.setStatus(LOW);
	}

	//Law el parity odd fa el output 1 otherwise 0
}


// Function Draw
// Draws 3-input XOR gate
void XOR3::Draw(Output* pOut)
{
	//Call output class and pass gate drawing info to it.
	pOut->DrawXOR3(m_GfxInfo, selected);
}

//returns status of outputpin
int XOR3::GetOutPinStatus()
{
	return m_OutputPin.getStatus();
}


//returns status of Inputpin #n
int XOR3::GetInputPinStatus(int n)
{
	return m_InputPins[n - 1].getStatus();	//n starts from 1 but array index starts from 0.
}

//Set status of an input pin ot HIGH or LOW
void XOR3::setInputPinStatus(int n, STATUS s)
{
	m_InputPins[n - 1].setStatus(s);
}

Component* XOR3::Clone(const GraphicsInfo& newGfx) const
{
	return new XOR3(newGfx, XOR3_FANOUT);
}
