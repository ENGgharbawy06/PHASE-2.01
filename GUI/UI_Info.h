#ifndef UI_INFO_H
#define UI_INFO_H
#include <iostream>
using namespace std;
#include "..\CMUgraphicsLib\CMUgraphics.h"
#include "..\Defs.h"

const int x = 70;
const int y = 70;
__declspec(selectany) //prevent redefinition error

struct UI_Info	//User Interface Info
{
	MODE AppMode;		//Application Mode (design or simulation)
	
	static const int	width = 1900, height = 655,	//Window width and height
						wx = 15 , wy = 15,			//Window starting coordinates
						StatusBarHeight = 50,	//Status Bar Height
						ToolBarHeight = 80,		//Tool Bar Height
						ToolItemWidth = 80;		//Width of each item in toolbar menu
static const int LeftButtonHeight = 60;
	color DrawColor;		//Drawing color
	color SelectColor;		//Highlighting color
	color ConnColor;		//Connector color
	color MsgColor;			
	color BkGrndColor;		
color ToolBarBackgroundColor;
color ToolBarBorderColor;
	
	static const int	AND2_Width = x,		//A2 Gate Image default width
						AND2_Height = y;		//AND2 Gate Image default height
	static const int	OR2_Width = x,		//OR2 Gate Image default width
		OR2_Height = y;		//OR2 Gate Image default height
	static const int	XOR2_Width = x,		//XOR2 Gate Image default width
		XOR2_Height = y;		//XOR2 Gate Image default height
	static const int	XNOR2_Width = x,		//XNOR2 Gate Image default width
		XNOR2_Height = y;		//XNOR2 Gate Image default height
	static const int	AND3_Width = x,		//AND3 Gate Image default width
		AND3_Height = y;		//AND3 Gate Image default height
	static const int	NOR3_Width = x,		//NOR3 Gate Image default width
		NOR3_Height = y;		//NOR3 Gate Image default height
	static const int	XOR3_Width = x,		//XOR3 Gate Image default width
		XOR3_Height = y;		//XOR3 Gate Image default height
	static const int    INV_Width = x,        //INV Gate Image default width
		INV_Height = y;       //INV Gate Image default height
	static const int    BUFF_Width = x,       //BUFF Gate Image default width
		BUFF_Height = y;      //BUFF Gate Image default height
	static const int    NAND2_Width = x,      //NAND2 Gate Image default width
		NAND2_Height = y;     //NAND2 Gate Image default height
	static const int    NOR2_Width = x,       //NOR2 Gate Image default width
		NOR2_Height = y;      //NOR2 Gate Image default height
	static const int LED_Width = x,        
		LED_Height = y;       

}UI;	//create a single global object UI
#endif
