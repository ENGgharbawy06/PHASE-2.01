#include "AddNORgate3.h"
#include "..\ApplicationManager.h"

AddNORgate3::AddNORgate3(ApplicationManager* pApp) :Action(pApp)  //test test test 
{
	pComp = nullptr;
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
	/*pIn->GetPointClicked(Cx, Cy);*/
	pOut->GetValidDrawingPoint(Cx, Cy, pIn);

	//Clear Status Bar
	pOut->ClearStatusBar();

}

void AddNORgate3::Execute()
{
	//Get Center point of the Gate

	ReadActionParameters();

	//Calculate the rectangle CNORners
	int Len = UI.NOR3_Width;
	int Wdth = UI.NOR3_Height;

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
	if (pComp != nullptr)
	{
		pManager->DeleteComponent(pComp);
		pManager->GetOutput()->PrintMsg("Undo: Removed the component.");
	}
}

void AddNORgate3::Redo()
{
	if (pComp != nullptr)
	{
		pManager->AddComponent(pComp);
		pManager->GetOutput()->PrintMsg("Redo: Restored the component.");
	}
}