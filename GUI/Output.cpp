#include "Output.h"

Output::Output()
{
	UI.AppMode = DESIGN;		
	//Initilaize interface colors
	UI.DrawColor = BLACK;
	UI.SelectColor = BLUE;
	UI.ConnColor = RED;
	UI.MsgColor = DARKGREEN;
	UI.BkGrndColor = WHITE;
	//Create the drawing window
	pWind = CreateWind(UI.width, UI.height, UI.wx, UI.wy);	
	ChangeTitle("Programming Techniques Project");

	CreateDesignToolBar();	//Create desgin toolbar
	CreateStatusBar();		//Create Statusbar
	CreateBottomToolBar();  // Create bottom toolbar
}
Input* Output::CreateInput() const
{
	//Create an Input Object & assign it to the Same Window
	Input* pIn = new Input(pWind);
	return pIn;
}
//Interface Functions

window* Output::CreateWind(int wd, int h, int x, int y) const
{
	return new window(wd, h, x, y);
}

void Output::ChangeTitle(string Title) const
{
	pWind->ChangeTitle(Title);
}

void Output::CreateStatusBar() const
{
	pWind->SetPen(BLACK,3);
	pWind->DrawLine(0, UI.height-UI.StatusBarHeight, UI.width, UI.height-UI.StatusBarHeight);
}

void Output::PrintMsg(string msg) const
{
	ClearStatusBar();
	int MsgX = 25;
	int MsgY = UI.StatusBarHeight - 10;
	
    pWind->SetFont(20, BOLD | ITALICIZED, BY_NAME, "Arial"); 
	pWind->SetPen(UI.MsgColor); 
	pWind->DrawString(MsgX, UI.height - MsgY, msg);
}

void Output::ClearStatusBar()const
{
	int MsgX = 25;
	int MsgY = UI.StatusBarHeight - 10;

	pWind->SetPen(UI.BkGrndColor);
	pWind->SetBrush(UI.BkGrndColor);
	pWind->DrawRectangle(MsgX, UI.height - MsgY, UI.width, UI.height);
}

//Clears the drawing (desgin) area
void Output::ClearDrawingArea() const
{
	pWind->SetPen(BLACK, 1);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(0, UI.ToolBarHeight, UI.width, UI.height -UI.ToolBarHeight- UI.StatusBarHeight); //start drawing after the left toolbar and top toolbar
	
}
//Draws the menu (toolbar) in the Design mode
void Output::CreateDesignToolBar() const
{
	UI.AppMode = DESIGN;	//Design Mode
	

	//Images in the menu bar 
	string MenuItemImages[ITM_DSN_CNT];
	MenuItemImages[ITM_AND2] = "..\\Images\\Menu\\Menu_AND2.jpg";
	MenuItemImages[ITM_OR2]  = "..\\Images\\Menu\\Menu_OR2.jpg";
	MenuItemImages[ITM_EXIT] = "..\\Images\\Menu\\Menu_Exit.jpg";
	MenuItemImages[ITM_NAND2] = "..\\Images\\Menu\\Menu_NAND2.jpg";
	MenuItemImages[ITM_NOR2] = "..\\Images\\Menu\\Menu_NOR2.jpg";
	MenuItemImages[ITM_XOR2] = "..\\Images\\Menu\\Menu_XOR2.jpg";
	MenuItemImages[ITM_XNOR2] = "..\\Images\\Menu\\Menu_XNOR2.jpg";
	MenuItemImages[ITM_AND3] = "..\\Images\\Menu\\Menu_AND3.jpg";
	MenuItemImages[ITM_NOR3] = "..\\Images\\Menu\\Menu_NOR3.jpg";
	MenuItemImages[ITM_XOR3] = "..\\Images\\Menu\\Menu_XOR3.jpg"; 
	MenuItemImages[ITM_INV] = "..\\Images\\Menu\\Menu_INV.jpg";
	MenuItemImages[ITM_BUFF] = "..\\Images\\Menu\\Menu_BUFF.jpg";
	MenuItemImages[ITM_SWITCH] = "..\\Images\\Menu\\Menu_SWITCH.jpg"; 
	MenuItemImages[ITM_CONNECTION] = "..\\Images\\Menu\\Menu_connection.jpg";
	MenuItemImages[ITM_LED] = "..\\Images\\Menu\\Menu_LED.jpg"; //recheck 3a4an fi errors
	MenuItemImages[ITM_SIM_MODE] = "..\\Images\\Menu\\Menu_changeMode.jpg";

	//MenuItemImages[ITM_DSN_MODE] = "..\\Images\\Menu\\Menu_Design.jpg";*/


	//Draw menu item one image at a time
	for (int i = 0; i < ITM_DSN_CNT; i++) 
		pWind->DrawImage(MenuItemImages[i],i*UI.ToolItemWidth,0,UI.ToolItemWidth, UI.ToolBarHeight);

	//This is a line under the toolbar
	pWind->SetPen(BLACK,3);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);	
}

void Output::CreateBottomToolBar() const
{
	// Images in the bottom menu
	string BottomItemImages[ITM_BTM_CNT];
	BottomItemImages[ITM_UNDO_B] = "..\\Images\\Menu\\Undo.jpg";
	BottomItemImages[ITM_REDO_B] ="..\\Images\\Menu\\Redo.jpg";
	BottomItemImages[ITM_SAVE_B] = "..\\Images\\Menu\\Save.jpg";
	BottomItemImages[ITM_EDIT_B] = "..\\Images\\Menu\\Edit.jpg";
	BottomItemImages[ITM_delete_B] ="..\\Images\\Menu\\delete.jpg";
	BottomItemImages[ITM_paste_B] = "..\\Images\\Menu\\Paste.jpg";
	BottomItemImages[ITM_copy_B] = "..\\Images\\Menu\\Copy.jpg";
	BottomItemImages[ITM_cut_B] = "..\\Images\\Menu\\cut.jpg";
	
	int y = UI.height - UI.StatusBarHeight - UI.ToolBarHeight;

	for (int i = 0; i < ITM_BTM_CNT; i++)
		pWind->DrawImage(BottomItemImages[i], i * UI.ToolItemWidth, y,
			UI.ToolItemWidth, UI.ToolBarHeight);


	pWind->SetPen(BLACK, 3);
	pWind->DrawLine(0, y, UI.width, y);
}

//Draws the menu (toolbar) in the simulation mode
void Output::CreateSimulationToolBar() const
{
	UI.AppMode = SIMULATION;	//Simulation Mode

	pWind->SetBrush(WHITE);
	pWind->SetPen(WHITE);
	pWind->DrawRectangle(0, 0, UI.width, UI.ToolBarHeight);
	pWind->DrawRectangle(0, UI.height - UI.StatusBarHeight - UI.ToolBarHeight-10, UI.width, UI.height - UI.StatusBarHeight);

	// Prepare list of images for simulation toolbar
	string MenuItemImages[ITM_SIM_CNT];
	MenuItemImages[ITM_VALIDATE] = "..\\Images\\Menu\\Menu_Validate.jpg";
	MenuItemImages[ITM_SIMULATE] = "..\\Images\\Menu\\Menu_Simulate.jpg";
	MenuItemImages[ITM_TRUTH_TABLE] = "..\\Images\\Menu\\Menu_TruthTable.jpg";
	MenuItemImages[ITM_DSN_MODE] = "..\\Images\\Menu\\Menu_changeMode.jpg";
	MenuItemImages[ITM_CHANGE_SWITCH] = "..\\Images\\Menu\\Menu_ChangeSwitch.jpg";
	MenuItemImages[ITM_EXIT2] = "..\\Images\\Menu\\Menu_Exit.jpg";

	// Draw menu items
	for (int i = 0; i < ITM_SIM_CNT; i++)
		pWind->DrawImage(MenuItemImages[i], i * UI.ToolItemWidth, 0,
			UI.ToolItemWidth, UI.ToolBarHeight);

	// Draw a line under the toolbar
	pWind->SetPen(BLACK, 3);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);

}

// Components of the circuit
void Output::DrawAND2(GraphicsInfo r_GfxInfo, bool sel) const
{
	string GateImage;
	if (sel)	// use highlighted image when sel
		GateImage = "..\\Images\\Gates\\Gate_AND2_Hi.jpg";
	else
		GateImage = "..\\Images\\Gates\\Gate_AND2.jpg";

	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.AND2_Width, UI.AND2_Height);

}

void Output::DrawOR2(GraphicsInfo r_GfxInfo, bool sel) const
{
	string GateImage;
	if (sel)
		GateImage = "..\\Images\\Gates\\Gate_OR2.jpg";
	else
		GateImage = "..\\Images\\Gates\\Gate_OR2.jpg";

	// Draw OR2 gate
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.OR2_Width, UI.OR2_Height);
}

void Output::DrawXOR2(GraphicsInfo r_GfxInfo, bool sel) const
{
	string GateImage;
	if (sel)
		GateImage = "..\\Images\\Gates\\Gate_XOR2_Hi.jpg";
	else
		GateImage = "..\\Images\\Gates\\Gate_XOR2.jpg";

	// Draw XOR2 gate
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.XOR2_Width, UI.XOR2_Height);
}

void Output::DrawXNOR2(GraphicsInfo r_GfxInfo, bool sel) const
{
	string GateImage;
	if (sel)
		GateImage = "..\\Images\\Gates\\Gate_XNOR2_Hi.jpg";
	else
		GateImage = "..\\Images\\Gates\\Gate_XNOR2.jpg";

	// Draw XNOR2 gate
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.XNOR2_Width, UI.XNOR2_Height);
}

void Output::DrawLED(GraphicsInfo r_GfxInfo, bool sel) const
{
	string GateImage;
	if(sel)
		GateImage = "..\\Images\\Gates\\Gate_LED_Hi.jpg";
	else
		GateImage = "..\\Images\\Gates\\Gate_LED.jpg";


	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.LED_Width, UI.LED_Height);
}

void Output::DrawNAND2(GraphicsInfo r_GfxInfo, bool sel) const
{
	string GateImage;
	if (sel)
		GateImage = "..\\Images\\Gates\\Gate_NAND2_Hi.jpg";
	else
		GateImage = "..\\Images\\Gates\\Gate_NAND2.jpg";

	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.NAND2_Width, UI.NAND2_Height);
}

void Output::DrawNOR2(GraphicsInfo r_GfxInfo, bool sel) const
{
	string GateImage;
	if (sel)
		GateImage = "..\\Images\\Gates\\Gate_NOR2_Hi.jpg";
	else
		GateImage = "..\\Images\\Gates\\Gate_NOR2.jpg";

	// Draw NOR2 gate
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.OR2_Width, UI.OR2_Height);
}

void Output::DrawXOR3(GraphicsInfo r_GfxInfo, bool sel) const
{
	string GateImage;
	if (sel)
		GateImage = "..\\Images\\Gates\\Gate_XOR3_Hi.jpg";
	else
		GateImage = "..\\Images\\Gates\\Gate_XOR3.jpg";

	// Draw XOR3 gate
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.OR2_Width, UI.OR2_Height);
}

void Output::DrawAND3(GraphicsInfo r_GfxInfo, bool sel) const
{
	string GateImage;
	if (sel)
		GateImage = "..\\Images\\Gates\\Gate_AND3_Hi.jpg";
	else
		GateImage = "..\\Images\\Gates\\Gate_AND3.jpg";

	// Draw AND3 gate
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.OR2_Width, UI.OR2_Height);
}

void Output::DrawNOR3(GraphicsInfo r_GfxInfo, bool sel) const
{
	string GateImage;
	if (sel)
		GateImage = "..\\Images\\Gates\\Gate_NOR3_Hi.jpg";
	else
		GateImage = "..\\Images\\Gates\\Gate_NOR3.jpg";

	// Draw NOR3 gate
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.OR2_Width, UI.OR2_Height);
}

void Output::DrawINV(GraphicsInfo r_GfxInfo, bool sel) const
{
	string GateImage;
	if (sel)
		GateImage = "..\\Images\\Gates\\Gate_INV_Hi.jpg";
	else
		GateImage = "..\\Images\\Gates\\Gate_INV.jpg";

	// Draw INV gate
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.OR2_Width, UI.OR2_Height);
}

void Output::DrawBUFF(GraphicsInfo r_GfxInfo, bool sel) const
{
	string GateImage;
	if (sel)
		GateImage = "..\\Images\\Gates\\Gate_BUFF_Hi.jpg";
	else
		GateImage = "..\\Images\\Gates\\Gate_BUFF.jpg";

	// Draw BUFF gate
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.OR2_Width, UI.OR2_Height);
}

void Output::DrawSWITCH(GraphicsInfo r_GfxInfo, bool sel) const
{
	string GateImage;
	if (sel)
		GateImage = "..\\Images\\Gates\\Gate_SWITCH_Hi.jpg";
	else
		GateImage = "..\\Images\\Gates\\Gate_SWITCH.jpg";

	// Draw BUFF gate
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.OR2_Width, UI.OR2_Height);
}

void Output::DrawConnection(GraphicsInfo r_GfxInfo, bool sel) const
{
	// set pen color based on selection
	if (sel)
		pWind->SetPen(UI.SelectColor, 3);
	else
		pWind->SetPen(UI.ConnColor, 3);

	// Draw Straight Line if the points of X or the points of y are equal 
	if (r_GfxInfo.x1 == r_GfxInfo.x2 || r_GfxInfo.y1 == r_GfxInfo.y2) {
		pWind->DrawLine(r_GfxInfo.x1, r_GfxInfo.y1, r_GfxInfo.x2, r_GfxInfo.y2);
		return;
	}
//if the points not equal we will make L connection to avoid overlapping
	int midx = (r_GfxInfo.x1 + r_GfxInfo.x2) / 2;
	pWind->DrawLine(r_GfxInfo.x1, r_GfxInfo.y1, midx, r_GfxInfo.y1);
	pWind->DrawLine(midx, r_GfxInfo.y1, midx, r_GfxInfo.y2);
	pWind->DrawLine(midx, r_GfxInfo.y2, r_GfxInfo.x2, r_GfxInfo.y2);

}

void Output::DrawString(int x, int y, string msg) const
{
	pWind->SetPen(UI.MsgColor);
	pWind->SetFont(20, BOLD, BY_NAME, "Arial");
	pWind->DrawString(x, y, msg);
}

Output::~Output()
{
	delete pWind;
}
