#pragma once

#include "..\CMUgraphicsLib\CMUgraphics.h"
#include "UI_Info.h"

class Output;
class Input		
{
private:
	window *pWind;	//Pointer to the Graphics Window
	mutable int LastClickX, LastClickY; 

public:
	Input(window*);
	void GetPointClicked(int &, int &);	//Get coordinate where user clicks
	string GetString(Output*);		//Returns a string entered by the user

	ActionType GetUserAction() const; //Reads the user click and maps it to an action

	void GetLastClick(int &x, int &y) const;

	bool IsCtrlPressed() const; // dy mahtota ashan el cntrl key bysa3dna fel select action 

	~Input();
};
