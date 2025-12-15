#pragma once
#ifndef _NOR2_H
#define _NOR2_H

#include "Gate.h"

class NOR2 : public Gate
{
public:
    NOR2(const GraphicsInfo& r_GfxInfo, int r_FanOut);

    virtual void Operate();
    virtual void Draw(Output* pOut);

    virtual int GetOutPinStatus();
    virtual int GetInputPinStatus(int n);
    virtual void setInputPinStatus(int n, STATUS s);

    virtual Component* Clone(const GraphicsInfo& newGfx) const override;

    virtual void SetGraphicsInfo(GraphicsInfo NewGfx);

    virtual void Save(ofstream& out);
    virtual void Load(ifstream& in);
    virtual ~NOR2();
};

#endif