#include "Input.h"
#include "Output.h"

Input::Input(window* pW)
{
	pWind = pW; //point to the passed window
}

void Input::GetPointClicked(int &x, int &y)
{
	pWind->WaitMouseClick(x, y);	//Wait for mouse click
}

string Input::GetString(Output *pOut)
{
	string input;
	char ckey = 0;
	pOut->PrintMsg("Enter your string: (Press ENTER to end, ESCAPE to end without saving)");
	while(1)
	{
		pWind->WaitKeyPress(ckey);
		if(ckey == 27) //ESCAPE key
		{
			
			input = "";
			break;
		}
		else if(ckey == 13) //ENTER key
		{
			break;
		}
		else if(ckey == 8) //BACKSPACE key
		{
			if(!input.empty())
			{
				input.pop_back();
			}
		}
		else if(ckey >= 32 && ckey <= 126) //Printable characters
		{
			input.push_back(ckey);
		}
		pOut->PrintMsg("Enter your string: " + input);
	}
	pOut->PrintMsg(input + " is saved.");
	
	return input;
}

//Reads where the user clicks to determine the desired action
ActionType Input::GetUserAction() const
{	
	int x,y;
	pWind->WaitMouseClick(x, y);	//Get the coordinates of the user click
	
	LastClickX = x;
	LastClickY = y;

	if(UI.AppMode == DESIGN )	//application is in design mode
	{
		//[1] If user clicks on the Toolbar
		if ( y >= 0 && y < UI.ToolBarHeight)
		{	
			//Check whick Menu item was clicked
			int ClickedItemOrder = (x / UI.ToolItemWidth);
			//Divide x coord of the point clicked by the menu item width (int division)
			
			//TODO add the rest of the gates
			switch (ClickedItemOrder)
			{
			case ITM_AND2: return ADD_AND_GATE_2;
			case ITM_OR2:  return ADD_OR_GATE_2;
			case ITM_NAND2:return ADD_NAND_GATE_2;
			case ITM_NOR2: return ADD_NOR_GATE_2;
			case ITM_XOR2: return ADD_XOR_GATE_2;
			case ITM_XNOR2:return ADD_XNOR_GATE_2;
			case ITM_AND3: return ADD_AND_GATE_3;
			case ITM_NOR3: return ADD_NOR_GATE_3;
			case ITM_XOR3: return ADD_XOR_GATE_3;
			case ITM_INV:  return ADD_INV;
			case ITM_BUFF: return ADD_BUFF;
			case ITM_CONNECTION: return ADD_CONNECTION;
			case ITM_SWITCH: return ADD_SWITCH;
			case ITM_LED: return ADD_LED;
			case ITM_EXIT: return EXIT;
			case ITM_SIM_MODE: return SIM_MODE;
					

			

			default: return DSN_TOOL;	//A click on empty place in desgin toolbar
			}			
			
		}
		if (y >= UI.height - UI.ToolBarHeight - UI.StatusBarHeight && y < UI.height - UI.StatusBarHeight)
		{
			//Check whick Menu item was clicked
			//==> This assumes that menu items are lined up horizontally <==
			int ClickedItemOrder = (x / UI.ToolItemWidth);
			//Divide x coord of the point clicked by the menu item width (int division)
			//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on
			//TODO add the rest of the gates
			switch (ClickedItemOrder)
			{

			case ITM_UNDO_B: return UNDO;
			case ITM_copy_B: return COPY;
			case ITM_paste_B: return PASTE;
			case ITM_cut_B: return CUT;
			case ITM_REDO_B: return REDO;
			case ITM_SAVE_B: return SAVE;
			case ITM_delete_B: return DEL;
			case ITM_EDIT_B: return EDIT_LABEL;

			default: return BOT_TOOL;	//A click on empty place in desgin toolbar
			}
		}
		//[2] User clicks on the drawing area
		if ( y >= UI.ToolBarHeight && y < UI.height - UI.ToolBarHeight - UI.StatusBarHeight)
		{
			return SELECT;	//user want to select/unselect a component
		}
		
		//[3] User clicks on the status bar
		if ( y >= UI.height - UI.StatusBarHeight)
		{
			return STATUS_BAR;
		}
		
	}
	else if (UI.AppMode == SIMULATION)//Application is in Simulation mode TODO
	{
		if (y >= 0 && y < UI.ToolBarHeight)
		{
			int ClickedItemOrder = (x / UI.ToolItemWidth);
			switch (ClickedItemOrder)
			{
			case ITM_VALIDATE: return VALIDATE;
			case ITM_SIMULATE: return SIMULATE;
			case ITM_TRUTH_TABLE: return CREATE_TRUTH_TABLE;
			case ITM_DSN_MODE: return DSN_MODE;
			case ITM_CHANGE_SWITCH: return CHANGE_SWITCH;
			case ITM_EXIT2: return EXIT;
			default: return SIM_TOOL;	//A click on empty place in simulation toolbar
			}
		}
		//[2] User clicks on the drawing area
		if (y >= UI.ToolBarHeight && y < UI.height - UI.ToolBarHeight - UI.StatusBarHeight)
		{
			return SELECT;	//user want to select/unselect a component
		}
		//[3] User clicks on the status bar
		if (y >= UI.height - UI.StatusBarHeight)
		{
			return STATUS_BAR;
		}
		if (y >= UI.height - UI.ToolBarHeight - UI.StatusBarHeight &&
			y < UI.height - UI.StatusBarHeight)
		{
			
			return SIM_TOOL;  
		}
	
	}
	
	

}

void Input::GetLastClick(int& x, int& y) const
{
	x = LastClickX;
	y = LastClickY;
}


Input::~Input()
{
	
}


