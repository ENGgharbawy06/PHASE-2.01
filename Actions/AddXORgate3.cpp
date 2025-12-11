#include "AddXORgate3.h"
#include "..\ApplicationManager.h"

AddXORgate3::AddXORgate3(ApplicationManager* pApp) :Action(pApp)  //test test test 
{

}


AddXORgate3::~AddXORgate3(void)

{


}

void AddXORgate3::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//Print Action Message
	pOut->PrintMsg("3-Inputs XOR Gate: Click to add the gate");

	//Wait for User Input
	pIn->GetPointClicked(Cx, Cy);

	//Clear Status Bar
	pOut->ClearStatusBar();

}

void AddORgate3::Execute()
{
	//Get Center point of the Gate

	ReadActionParameters();

	//Calculate the rectangle CXORners
	int Len = UI.XOR3_Width;
	int Wdth = UI.XOR3_Height;

	GraphicsInfo GInfo; //Gfx info to be used to construct the XOR3 gate

	GInfo.x1 = Cx - Len / 2;
	GInfo.x2 = Cx + Len / 2;
	GInfo.y1 = Cy - Wdth / 2;
	GInfo.y2 = Cy + Wdth / 2;
	XOR2* pA = new XOR2(GInfo, XOR2_FANOUT);
	pManager->AddComponent(pA);
}

void AddXORgate3::Undo()
{

}

void AddXORgate3::Redo()
{
}
