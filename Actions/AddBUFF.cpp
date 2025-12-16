#include "AddBUFF.h"
#include "..\ApplicationManager.h"
AddBuffer::AddBuffer(ApplicationManager* pApp) : Action(pApp)
{
	pComp = NULL;
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

	if (pManager->CheckCollision(GInfo.x1, GInfo.y1, Len, Wdth, nullptr))
	{
		pManager->GetOutput()->PrintMsg("Error: Space is occupied! Cannot place component here.");
		return; // <--- STOP here if there is a collision
	}

	BUFF* pA = new BUFF(GInfo, BUFF_FANOUT);
	pManager->AddComponent(pA);
	pComp = pA;
}
void AddBuffer::Undo()
{
	if (pComp != nullptr)
	{
		pManager->BreakConnections(pComp);
		pManager->DeleteComponent(pComp);
		pManager->GetOutput()->PrintMsg("Undo: Removed the component.");
	}
}

void AddBuffer::Redo()
{
	if (pComp != nullptr)
	{
		pManager->AddComponent(pComp);
		pManager->GetOutput()->PrintMsg("Redo: Restored the component.");
	}
}