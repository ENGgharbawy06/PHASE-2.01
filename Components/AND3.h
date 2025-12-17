#pragma once
#ifndef _AND3_H
#define _AND3_H


#include "Gate.h"
class AND3 :public Gate

{
	public:
	AND3(const GraphicsInfo &r_GfxInfo, int r_FanOut);
	virtual void Operate();	
	virtual void Draw(Output* pOut);	
	virtual int GetOutPinStatus();	
	virtual int GetInputPinStatus(int n);	
	virtual void setInputPinStatus(int n, STATUS s);	
	virtual Component* Clone(const GraphicsInfo& newGfx) const override; 
	virtual ~AND3();
	void SetGraphicsInfo(GraphicsInfo NewGfx);


	// ====== REQUIRED FOR SAVE/LOAD (NO LOGIC CHANGE) ======
	virtual void Save(ofstream& out) override;
	virtual void Load(ifstream& in) override;
	// =======================================================
};
#endif