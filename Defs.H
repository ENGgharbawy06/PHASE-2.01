#ifndef CONST_H
#define CONST_H

//This header file contains some definitions to be used all over the application

//All possible actions
enum ActionType 
{
	ADD_BUFF,			//Add 1-input Buffer gate
	ADD_INV,			//Add 1-input Inverter gate
	ADD_AND_GATE_2,		//Add 2-input AND gate
	ADD_OR_GATE_2,		//Add 2-input OR gate
	ADD_NAND_GATE_2,	//Add 2-input NAND gate
	ADD_NOR_GATE_2,		//Add 2-input NOR gate
	ADD_XOR_GATE_2,		//Add 2-input XOR gate
	ADD_XNOR_GATE_2,	//Add 2-input XNOR gate
	ADD_AND_GATE_3,		//Add 3-input AND gate
	ADD_NOR_GATE_3,		//Add 3-input NOR gate
	ADD_XOR_GATE_3,		//Add 3-input XOR gate
	ADD_SWITCH,			//Add Switch
	ADD_LED,			//Add LED
	ADD_CONNECTION,		//Add Wire Connection

	ADD_LABEL,			//Add Label to a Component, a Connection
	EDIT_LABEL,			//Edit Label of a Component, a Connection

	CREATE_TRUTH_TABLE,	//Create Truth Table of the Circuit

	CHANGE_SWITCH,		//Change Switch Status in Simulation Mode

	SELECT,		//Select a Component, a Connection
	DEL,		//Delete a Component, a Connection
	MOVE,		//Move a Component, a Connection

	SAVE,		//Save the whole Circuit to a file
	LOAD,		//Load a Circuit from a file

	COPY,  
    PASTE,
    CUT,

	UNDO,		//Undo the last Action performed
	REDO,		//Redo the last Action canceled (BONUS)

	DSN_MODE,	//Switch to Design mode
	SIM_MODE,	//Switch to Simulation mode

	EXIT,		//Exit the application

	STATUS_BAR,		//A click on the status bar
	DSN_TOOL,	//A click on an empty place in the design tool bar
	BOT_TOOL, //A click on an empty place in the bottom tool bar
	SIM_TOOL,	//A click on an empty place in the simulation tool bar
	VALIDATE,
	SIMULATE,
};

enum STATUS
{
	LOW,
	HIGH
};
//test num 9

enum MODE	//Modes of operation
{
	DESIGN,
	SIMULATION
};

enum DsgnMenuItem //The items of the design menu
{
	ITM_AND2,		
	ITM_OR2,		
	ITM_NAND2,
	ITM_NOR2,
	ITM_XOR2,
	ITM_XNOR2,
	ITM_AND3,
	ITM_XOR3,
	ITM_NOR3,
	ITM_INV,
	ITM_BUFF,
	ITM_SWITCH,
	ITM_CONNECTION,
	ITM_LED,
	ITM_SIM_MODE,
	ITM_EXIT,
	ITM_DSN_CNT		//no. of design menu items ==> This should be the last line in this enum
};

enum BottomMenuItem
{
	ITM_UNDO_B,
	ITM_REDO_B,
	ITM_SAVE_B,
	ITM_EDIT_B,
	ITM_delete_B,
	ITM_copy_B,
	ITM_paste_B,
	ITM_cut_B,
	ITM_BTM_CNT
	
};

enum SimMenuItem //The items of the simulation menu
{	ITM_VALIDATE,      // Validate circuit
	ITM_SIMULATE,      // Start/Run simulation
	ITM_TRUTH_TABLE,   // Generate truth table
	ITM_DSN_MODE,      // Switch back to design mode   
	ITM_CHANGE_SWITCH, // Change switch status
	ITM_EXIT2,
	ITM_SIM_CNT //no. of simulation menu items ==> This should be the last line in this enum
};

// Maximum number of input pins that can be connected to any output pin
#define MAX_CONNS 20

// Default fan out
enum FANOUT
{
	AND2_FANOUT = 50 //Default fan out of 2-input AND gate
};

// Each component occupies a rectangular area so it needs 2 points to represent that area
// This structure can be extended if desired
struct GraphicsInfo
{
	int x1, y1, x2, y2;
};

#endif
