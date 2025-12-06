#pragma
#include "Gate.h"
class INV : public Gate
{
	public:
	INV(const GraphicsInfo &r_GfxInfo);
	virtual void Operate();	//Calculates the output according to the inputs
	virtual void Draw(Output* pOut);	//for each component to Draw itself
	virtual int GetOutPinStatus();	//returns status of outputpin
	virtual int GetInputPinStatus(int n);	//returns status of Inputpin # n
	virtual void setInputPinStatus(int n, STATUS s);	//set status of Inputpin # n, to be used by connection class.
	virtual ~INV();
};
