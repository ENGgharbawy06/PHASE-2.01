#include "AddBUFF.h"
#include "..\ApplicationManager.h"
AddBuffer::AddBuffer(ApplicationManager* pApp) : Action(pApp)
{
}
AddBuffer::~AddBuffer()
{
}
void AddBuffer::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	//Print Action Message
	pOut->PrintMsg("Buffer Gate: Click to add the gate");
	//Wait for User Input
	/*pIn->GetPointClicked(Cx, Cy);*/
	pOut->GetValidDrawingPoint(Cx, Cy, pIn);
	//Clear Status Bar
	pOut->ClearStatusBar();
}
void AddBuffer::Execute()
{
	//Get Center point of the Gate
	ReadActionParameters();
	//Calculate the rectangle Corners
	int Len = UI.BUFF_Width;
	int Wdth = UI.BUFF_Height;
	GraphicsInfo GInfo; //Gfx info to be used to construct the BUFF gate
	GInfo.x1 = Cx - Len / 2;
	GInfo.x2 = Cx + Len / 2;
	GInfo.y1 = Cy - Wdth / 2;
	GInfo.y2 = Cy + Wdth / 2;
	BUFF* pA = new BUFF(GInfo, BUFF_FANOUT);
	pManager->AddComponent(pA);
}
void AddBuffer::Undo()
{
}
void AddBuffer::Redo()
{
}
