#pragma once
#include "..\Defs.h"
#include "Input.h"

class Output	
{
private:
	window* pWind;	
	
public:
	Output(); 
	Input* CreateInput() const; 
	void ChangeTitle(string Title) const;

	void CreateDesignToolBar() const;	//Tool bar of the design mode
	void CreateSimulationToolBar() const;//Tool bar of the simulation mode
	void CreateStatusBar() const;	//Status bar
	void CreateBottomToolBar() const; // Bottom ToolBar
	void ClearStatusBar() const;		//Clears the status bar
	void ClearDrawingArea() const;	//Clears the drawing area
	void GetValidDrawingPoint(int& x, int& y, Input* pIn) const;

	window* CreateWind(int wd, int h, int x, int y) const; //Creates user interface window
	
    
	void DrawAND2(GraphicsInfo r_GfxInfo, bool selected = false) const;
	void DrawNAND2(GraphicsInfo r_GfxInfo, bool selected=false) const;
	void DrawNOR2(GraphicsInfo r_GfxInfo, bool selected = false) const;
	void DrawXOR2(GraphicsInfo r_GfxInfo, bool selected = false) const;
	void DrawOR2(GraphicsInfo r_GfxInfo, bool selected = false) const;
	void DrawXNOR2(GraphicsInfo r_GfxInfo, bool selected = false) const;
	void DrawLED(GraphicsInfo r_GfxInfo, bool selected = false) const;
	void DrawAND3(GraphicsInfo r_GfxInfo, bool selected = false) const;
	void DrawNOR3(GraphicsInfo r_GfxInfo, bool selected = false) const;
	void DrawXOR3(GraphicsInfo r_GfxInfo, bool selected = false) const;
	void DrawINV(GraphicsInfo r_GfxInfo, bool selected = false) const;
	void DrawBUFF(GraphicsInfo r_GfxInfo, bool selected = false) const;
	void DrawSWITCH(GraphicsInfo r_GfxInfo, bool selected=false) const;
	void DrawLabel(const GraphicsInfo& GfxInfo, const std::string& txt)const;

	
	void DrawConnection(GraphicsInfo r_GfxInfo, bool selected = false) const;

	void DrawString(int x, int y, string msg) const;
	
	void PrintMsg(string msg) const;	//Print a message on Status bar
		
	~Output();
};
