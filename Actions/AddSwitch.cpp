#include "AddSwitch.h"
#include "..\ApplicationManager.h"
#include "..\Components\Switch.h"

AddSwitch::AddSwitch(ApplicationManager* pApp) :Action(pApp)
{
}

AddSwitch::~AddSwitch(void)
{
}

void AddSwitch::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//Print Action Message
	pOut->PrintMsg("Switch: Click to add a Switch");

	//Wait for User Input
	pOut->GetValidDrawingPoint(Cx, Cy, pIn);

	//Clear Status Bar
	pOut->ClearStatusBar();

}

void AddSwitch::Execute()
{
	//Get Center point of the Gate
	ReadActionParameters();

	//Calculate the rectangle Corners
	int Len = UI.AND2_Width;		// width of the switch (uses default gate width)
	int Wdth = UI.AND2_Height;		// height of the switch (uses default gate height)

	GraphicsInfo GInfo; //Gfx info to be used to construct the Switch

	GInfo.x1 = Cx - Len / 2;
	GInfo.x2 = Cx + Len / 2;
	GInfo.y1 = Cy - Wdth / 2;
	GInfo.y2 = Cy + Wdth / 2;

	if (pManager->CheckCollision(GInfo.x1, GInfo.y1, Len, Wdth, nullptr))
	{
		pManager->GetOutput()->PrintMsg("Error: Space is occupied! Cannot place component here.");
		return; // <--- STOP here if there is a collision
	}

	//Create the Switch
	Switch* pSwitch = new Switch(GInfo, SWITCH_FANOUT);

	//Add the component to the list of components
	pManager->AddComponent(pSwitch);
}

void AddSwitch::Undo()
{
}

void AddSwitch::Redo()
{
}