#include "AddNORgate2.h"
#include "..\ApplicationManager.h"

AddNORgate2::AddNORgate2(ApplicationManager* pApp) :Action(pApp)  //test test test 
{
	pComp = nullptr;
}


AddNORgate2::~AddNORgate2(void)

{
}

void AddNORgate2::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//Print Action Message
	pOut->PrintMsg("2-Inputs NOR Gate: Click to add the gate");

	//Wait for User Input
	/*pIn->GetPointClicked(Cx, Cy);*/

	pOut->GetValidDrawingPoint(Cx, Cy, pIn);

	//Clear Status Bar
	pOut->ClearStatusBar();

}

void AddNORgate2::Execute()
{
	//Get Center point of the Gate

	ReadActionParameters();

	//Calculate the rectangle CNORners
	int Len = UI.NOR2_Width;
	int Wdth = UI.NOR2_Height;

	GraphicsInfo GInfo; //Gfx info to be used to construct the NOR2 gate

	GInfo.x1 = Cx - Len / 2;
	GInfo.x2 = Cx + Len / 2;
	GInfo.y1 = Cy - Wdth / 2;
	GInfo.y2 = Cy + Wdth / 2;

	if (pManager->CheckCollision(GInfo.x1, GInfo.y1, Len, Wdth, nullptr))
	{
		pManager->GetOutput()->PrintMsg("Error: Space is occupied! Cannot place component here.");
		return; // <--- STOP here if there is a collision
	}

	NOR2* pA = new NOR2(GInfo, NOR2_FANOUT);
	pManager->AddComponent(pA);
	pComp = pA;
}

void AddNORgate2::Undo()
{
	if (pComp != nullptr)
	{
		pManager->DeleteComponent(pComp);
		pManager->GetOutput()->PrintMsg("Undo: Removed the component.");
	}
}

void AddNORgate2::Redo()
{
	if (pComp != nullptr)
	{
		pManager->AddComponent(pComp);
		pManager->GetOutput()->PrintMsg("Redo: Restored the component.");
	}
}

