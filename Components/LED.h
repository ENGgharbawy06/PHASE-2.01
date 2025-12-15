#ifndef _LED_H
#define _LED_H

#include "Component.h"
#include "InputPin.h"

class LED : public Component {
private:

    InputPin m_InputPin; // Keep variables private

public:

    LED(const GraphicsInfo& r_GfxInfo, int r_FanOut);
    virtual void Draw(Output* pOut);
    virtual void Operate();

    // SOLUTION: Move the function here!
    virtual InputPin* GetInputPin();
};

#endif

