#ifndef _LED_H
#define _LED_H

#include "Component.h"
#include "InputPin.h"

class LED : public Component {
private:
    InputPin m_InputPin;

public:
    LED(const GraphicsInfo& r_GfxInfo, int r_FanOut);

    virtual void Operate();
    virtual void Draw(Output* pOut);

    virtual int GetOutPinStatus();
    virtual int GetInputPinStatus(int n);
    virtual void setInputPinStatus(int n, STATUS s);
    virtual bool IsLED() const override { return true; }
    virtual Component* Clone(const GraphicsInfo& newGfx) const;
    virtual void Save(ofstream& out) override;
    virtual void Load(ifstream& in) override;
    void SetGraphicsInfo(GraphicsInfo NewGfx);

    // Helper function to get the input pin pointer
    InputPin* GetInputPin();
};

#endif