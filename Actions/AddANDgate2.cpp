#include "AddANDgate2.h"
#include "..\ApplicationManager.h"

AddANDgate2::AddANDgate2(ApplicationManager *pApp):Action(pApp)  //test test test 
{

	pComp = NULL;

}

AddANDgate2::~AddANDgate2(void)
{
}

void AddANDgate2::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//Print Action Message
	pOut->PrintMsg("2-Input AND Gate: Click to add the gate");

	//Wait for User Input
	/*pIn->GetPointClicked(Cx, Cy);*/
	pOut->GetValidDrawingPoint(Cx, Cy, pIn);
	

	//Clear Status Bar
	pOut->ClearStatusBar();
	
	
	
	
}

void AddANDgate2::Execute()
{
	//Get Center point of the Gate
	ReadActionParameters();
	
	//Calculate the rectangle Corners
	int Len = UI.AND2_Width;
	int Wdth = UI.AND2_Height;
	
	GraphicsInfo GInfo; //Gfx info to be used to construct the AND2 gate
	
	GInfo.x1 = Cx - Len/2;
	GInfo.x2 = Cx + Len/2;
	GInfo.y1 = Cy - Wdth/2;
	GInfo.y2 = Cy + Wdth/2;

	if (pManager->CheckCollision(GInfo.x1, GInfo.y1, Len, Wdth, nullptr))
	{
		pManager->GetOutput()->PrintMsg("Error: Space is occupied! Cannot place component here.");
		return; // <--- STOP here if there is a collision
	}


	AND2 *pAND2=new AND2(GInfo, AND2_FANOUT); 
	pManager->AddComponent(pAND2);
	pComp = pAND2;

}

void AddANDgate2::Undo()
{
	if (pComp != NULL)
	{
		// Remove it from the screen bas lesa mawoda fel memory
		pManager->BreakConnections(pComp);
		pManager->DeleteComponent(pComp);
		pManager->GetOutput()->PrintMsg("Undo: Removed the AND Gate.");
	}
}

void AddANDgate2::Redo()
{
	if (pComp != NULL)
	{
		// Draw tani (Law redo is clicked)
		pManager->AddComponent(pComp);
		pManager->GetOutput()->PrintMsg("Redo: Restored the AND Gate.");
	}
}
