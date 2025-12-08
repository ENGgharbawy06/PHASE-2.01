#include "BUFF.h"

BUFF::BUFF(const GraphicsInfo &r_GfxInfo) :Gate(1, r_GfxInfo)
{
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;	

}
void BUFF::Operate()	//Calculates the output according to the inputs
{




	int inputStatus = GetInputPinStatus(1);
	if (inputStatus == LOW) {
		m_OutputPin.setStatus(LOW);
	} else {
		m_OutputPin.setStatus(HIGH);
	}
}
// Function Draw	
// Draws Buffer gate
void BUFF::Draw(Output* pOut)	
{
	//Call output class and pass gate drawing info to it.
	pOut->DrawBUFF(m_GfxInfo);
}
//returns status of outputpin
int BUFF::GetOutPinStatus()	
{
	return m_OutputPin.getStatus();
}
//returns status of Inputpin #n
int BUFF::GetInputPinStatus(int n)	
{
	return m_InputPins[n - 1].getStatus();	//n starts from 1 but array index starts from 0.
}
//Set status of an input pin ot HIGH or LOW
void BUFF::setInputPinStatus(int n, STATUS s)	
{
	m_InputPins[n - 1].setStatus(s);
}
BUFF::~BUFF()
{
}