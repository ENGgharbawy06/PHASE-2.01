#ifndef _LED_H
#define _LED_H

#include "Component.h"
#include "InputPin.h"

class LED : public Component
{
public:
    LED(const GraphicsInfo& r_GfxInfo);
    virtual void Operate();                    // Calculate LED state (ON/OFF)
    virtual void Draw(Output* pOut);           // Draw LED
    virtual int GetOutPinStatus();             // LED has no output -> return -1
    virtual int GetInputPinStatus(int n);      // Only one input
    virtual void setInputPinStatus(int n, STATUS s);
	virtual Component* Clone(const GraphicsInfo& newGfx) const override; // Clone function to create a copy of the component 
private:
    InputPin m_InputPin;   // LED has ONLY 1 input
};

#endif
