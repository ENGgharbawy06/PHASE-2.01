#include "AddNORgate3.h"
#include "..\ApplicationManager.h"

AddNORgate3::AddNORgate3(ApplicationManager* pApp) :Action(pApp)  //test test test 
{

}


AddNORgate3::~AddNORgate3(void)

{


}

void AddNORgate3::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//Print Action Message
	pOut->PrintMsg("3-Inputs NOR Gate: Click to add the gate");

	//Wait for User Input
	pIn->GetPointClicked(Cx, Cy);

	//Clear Status Bar
	pOut->ClearStatusBar();

}

void AddORgate3::Execute()
{
	//Get Center point of the Gate

	ReadActionParameters();

	//Calculate the rectangle CNORners
	int Len = UI.XNOR3_Width;
	int Wdth = UI.XNOR3_Height;

	GraphicsInfo GInfo; //Gfx info to be used to construct the NOR3 gate

	GInfo.x1 = Cx - Len / 2;
	GInfo.x2 = Cx + Len / 2;
	GInfo.y1 = Cy - Wdth / 2;
	GInfo.y2 = Cy + Wdth / 2;
	NOR3* pA = new NOR3(GInfo, NOR3_FANOUT);
	pManager->AddComponent(pA);
}

void AddNORgate3::Undo()
{

}

void AddNORgate3::Redo()
{
}

