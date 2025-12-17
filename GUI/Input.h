#pragma once

#include "..\CMUgraphicsLib\CMUgraphics.h"
#include "UI_Info.h"


class Output;
class Input		
{
private:
	window *pWind;	
	mutable int LastClickX, LastClickY; 
	mutable bool IsDragging;
	mutable int DragX1, DragY1, DragX2, DragY2;

public:
	Input(window*);
	void GetPointClicked(int &, int &);	
	string GetString(Output*);		

	ActionType GetUserAction(); 

	void GetLastClick(int &x, int &y) const;
	
	bool GetDragCoordinates(int& x1, int& y1, int& x2, int& y2);

	~Input();
};
