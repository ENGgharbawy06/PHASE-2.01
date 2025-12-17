#pragma once
#include "component.h"
#include "InputPin.h"
#include "OutputPin.h"

class Connection :	public Component
{
	OutputPin* SrcPin;	
	InputPin* DstPin;

public:
	Connection(const GraphicsInfo& r_GfxInfo, OutputPin* pSrcPin, InputPin* pDstPin); //constructor

	virtual void Operate();	// bta5d el signal mn el source w t7otoa fe el destination
	virtual void Draw(Output* pOut); 	// بترسم ياسطا مش محتاجة شرح 

	
	void setSourcePin(OutputPin *pSrcPin); //setter 
	void setDestPin(InputPin* pDstPin); //setter
	OutputPin* getSourcePin(); // pointer to source pin
	InputPin* getDestPin(); //  poiner to destination pin
	virtual bool IsConnection() const; //بتسال لو دي كونكشن ولا لا 


	virtual int GetOutPinStatus();	//getter
	virtual int GetInputPinStatus(int n);	 //getter

	virtual void setInputPinStatus(int n, STATUS s);	//manual setter 
	virtual Component* Clone(const GraphicsInfo& newGfx) const override; //copy

	virtual void Save(ofstream& out) override; 
	virtual void Load(ifstream& in) override;

	virtual bool IsInside(int x, int y) override;
	~Connection(); //destructor
	void Disconnect(); // بستخدمها لما اجي افصل ال connection.
	//void Reconnect(); 

};
