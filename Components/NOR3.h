#ifndef _NOR3_H
#define _NOR3_H

#include "Gate.h"

class NOR3 : public Gate
{
public:
    NOR3(const GraphicsInfo& r_GfxInfo, int r_FanOut);

    virtual void Operate();
    virtual void Draw(Output* pOut);

    virtual int GetOutPinStatus();
    virtual int GetInputPinStatus(int n);
    virtual void setInputPinStatus(int n, STATUS s);

    virtual Component* Clone(const GraphicsInfo& newGfx) const override;
    void SetGraphicsInfo(GraphicsInfo NewGfx);

    virtual void Save(ofstream& out);
    virtual void Load(ifstream& in);
    virtual ~NOR3();

};

#endif
