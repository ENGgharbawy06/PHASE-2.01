#ifndef _NAND2_H
#define _NAND2_H


#include "Gate.h"

class NAND2 : public Gate
{
public:
	NAND2(const GraphicsInfo& r_GfxInfo, int r_FanOut);
	virtual void Operate();	
	virtual void Draw(Output* pOut);	

	virtual int GetOutPinStatus();	
	virtual int GetInputPinStatus(int n);	

	virtual void setInputPinStatus(int n, STATUS s);	
	virtual Component* Clone(const GraphicsInfo& newGfx) const override; 
	void SetGraphicsInfo(GraphicsInfo NewGfx);
	virtual ~NAND2();

	virtual void Save(ofstream& out);
	virtual void Load(ifstream& in);


};

#endif
