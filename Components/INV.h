#pragma once
#include "Gate.h"
class INV : public Gate
{
	public:
	INV(const GraphicsInfo &r_GfxInfo, int r_FanOut);
	virtual void Operate();	
	virtual void Draw(Output* pOut);	
	virtual int GetOutPinStatus();	
	virtual int GetInputPinStatus(int n);	
	virtual void setInputPinStatus(int n, STATUS s);	
	virtual Component* Clone(const GraphicsInfo& newGfx) const override; 
	virtual ~INV();
	void SetGraphicsInfo(GraphicsInfo NewGfx);
	
	
	virtual void Save(ofstream& out);
	virtual void Load(ifstream& in); 
};
