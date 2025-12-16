#include "AddLED.h"
#include "..\ApplicationManager.h"

AddLED::AddLED(ApplicationManager* pApp) :Action(pApp)
{
}

AddLED::~AddLED(void)
{
}

void AddLED::ReadActionParameters()
{
	// Get Pointers to Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	// Print Action Message
	pOut->PrintMsg("LED: Click to add an LED");

	// Wait for User Input
	pOut->GetValidDrawingPoint(Cx, Cy, pIn);

	// Clear Status Bar
	pOut->ClearStatusBar();
}

void AddLED::Execute()
{
	// Get Center point of the Component
	ReadActionParameters();

	// Calculate the rectangle Corners
	// We use the dimensions defined in UI_Info (accessed via UI global object)
	int Len = UI.LED_Width;
	int Wdth = UI.LED_Height;

	GraphicsInfo GInfo; // Gfx info to be used to construct the LED

	GInfo.x1 = Cx - Len / 2;
	GInfo.x2 = Cx + Len / 2;
	GInfo.y1 = Cy - Wdth / 2;
	GInfo.y2 = Cy + Wdth / 2;

	if (pManager->CheckCollision(GInfo.x1, GInfo.y1, Len, Wdth, nullptr))
	{
		pManager->GetOutput()->PrintMsg("Error: Space is occupied! Cannot place component here.");
		return; // <--- STOP here if there is a collision
	}

	// Create the LED
	// LED has 0 output fanout, but the constructor might require an integer.
	// We pass 1 or 0 as it doesn't really matter for an Output component.
	LED* pLED = new LED(GInfo, 1);

	// Add the component to the list of components
	pManager->AddComponent(pLED);
}

void AddLED::Undo()
{
}

void AddLED::Redo()
{
}