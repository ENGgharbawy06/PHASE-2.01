#include "Gate.h"

Gate::Gate(int r_Inputs, int r_FanOut):m_OutputPin(r_FanOut)
{
	
	m_InputPins = new InputPin[r_Inputs];
	m_Inputs = r_Inputs;	
	
	for(int i=0; i<m_Inputs; i++)
		m_InputPins[i].setComponent(this);

	m_OutputPin.setComponent(this);
}

OutputPin* Gate::GetOutputPin()
{
	return &m_OutputPin;
}

InputPin* Gate::GetInputPin(int index)
{
	
	if (index >= 0 && index < m_Inputs)
	{
		return &m_InputPins[index];
	}
	return nullptr;
}

