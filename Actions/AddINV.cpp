#include "AddINV.h"
#include "..\ApplicationManager.h"
AddINV::AddINV(ApplicationManager* pApp) : Action(pApp)
{
	pComp = nullptr;
}
AddINV::~AddINV()
{
}
void AddINV::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	//Print Action Message
	pOut->PrintMsg("1-Input Inverter Gate: Click to add the gate");
	//Wait for User Input
	/*pIn->GetPointClicked(Cx, Cy);*/
	pOut->GetValidDrawingPoint(Cx, Cy, pIn);
	//Clear Status Bar
	pOut->ClearStatusBar();
}
void AddINV::Execute()
{
	//Get Center point of the Gate
	ReadActionParameters();
	//Calculate the rectangle Corners
	int Len = UI.INV_Width;
	int Wdth = UI.INV_Height;
	GraphicsInfo GInfo; //Gfx info to be used to construct the INV gate
	GInfo.x1 = Cx - Len / 2;
	GInfo.x2 = Cx + Len / 2;
	GInfo.y1 = Cy - Wdth / 2;
	GInfo.y2 = Cy + Wdth / 2;

	if (pManager->CheckCollision(GInfo.x1, GInfo.y1, Len, Wdth, nullptr))
	{
		pManager->GetOutput()->PrintMsg("Error: Space is occupied! Cannot place component here.");
		return; // <--- STOP here if there is a collision
	}

	INV* pA = new INV(GInfo, INV_FANOUT);
	pManager->AddComponent(pA);
	pComp = pA;
}
void AddINV::Undo()
{
	if (pComp != nullptr)
	{
		pManager->BreakConnections(pComp);
		pManager->DeleteComponent(pComp);
		pManager->GetOutput()->PrintMsg("Undo: Removed the component.");
	}
}

void AddINV::Redo()
{
	if (pComp != nullptr)
	{
		pManager->AddComponent(pComp);
		pManager->GetOutput()->PrintMsg("Redo: Restored the component.");
	}
}