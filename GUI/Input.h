#pragma once

#include "..\CMUgraphicsLib\CMUgraphics.h"
#include "UI_Info.h"


class Output;
class Input		
{
private:
	window *pWind;	//Pointer to the Graphics Window
	mutable int LastClickX, LastClickY; 
	mutable bool IsDragging;
	mutable int DragX1, DragY1, DragX2, DragY2;

public:
	Input(window*);
	void GetPointClicked(int &, int &);	//Get coordinate where user clicks
	string GetString(Output*);		//Returns a string entered by the user

	ActionType GetUserAction(); //Reads the user click and maps it to an action

	void GetLastClick(int &x, int &y) const;
	
	bool GetDragCoordinates(int& x1, int& y1, int& x2, int& y2);

	~Input();
};
