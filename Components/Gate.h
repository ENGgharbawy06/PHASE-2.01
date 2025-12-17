#ifndef _GATE_H
#define _GATE_H

#include "InputPin.h"
#include "OutputPin.h"
#include "Component.h"

class Gate:public Component
{
protected:
	InputPin* m_InputPins;	
	OutputPin m_OutputPin;	
	int m_Inputs;		
public:
	Gate(int r_Inputs, int r_FanOut);
	//InputPin* GetInputPin(int n) { return &m_InputPins[n]; }
	bool IsGate() const { return true; } 
	//OutputPin* GetOutputPin() { return &m_OutputPin; }
	int GetInputPinCount() const { return m_Inputs; }

	virtual OutputPin* GetOutputPin();
	virtual InputPin* GetInputPin(int index);

	

};

#endif
