#pragma once
#include "Gate.h"

class OR2 :public Gate
{
	public:
	OR2(const GraphicsInfo &r_GfxInfo, int r_FanOut);
	virtual void Operate();	
	virtual void Draw(Output* pOut);	
	virtual int GetOutPinStatus();	
	virtual int GetInputPinStatus(int n);	
	virtual void setInputPinStatus(int n, STATUS s);	
	void SetGraphicsInfo(GraphicsInfo NewGfx);
	virtual Component* Clone(const GraphicsInfo& newGfx) const override; 

	virtual void Save(ofstream& out);
	virtual void Load(ifstream& in);
	virtual ~OR2();

};