
#ifndef APPLICATION_MANAGER_H
#define APPLICATION_MANAGER_H

#include "Defs.h"
#include "GUI\Output.h"
#include "GUI\Input.h"
#include "Actions\Action.h"
#include "Components\Component.h"

//Main class that manages everything in the application.
class ApplicationManager
{
	enum { MaxCompCount = 200 };	//Max no of Components	

private:
	int CompCount;		//Actual number of Components
	Component* CompList[MaxCompCount];	//List of all Components (Array of pointers)

	Output* OutputInterface; //pointer to the Output Clase Interface
	Input* InputInterface; //pointer to the Input Clase Interface

	Component* Clipboard;  //Clipboard for copy/paste/cut operations

	Component* SelectedComponent;

	//int ConnCount;  // Track number of connections
	//Connection* ConnList[MaxCompCount];  // Separate array for connections


public:
	ApplicationManager(); //constructor

	//Reads the required action from the user and returns the corresponding action type
	ActionType GetUserAction();

	//Creates an action and executes it
	void ExecuteAction(ActionType);

	void UpdateInterface();	//Redraws all the drawing window

	//Gets a pointer to Input / Output Object
	Output* GetOutput();
	Input* GetInput();

	//Adds a new component to the list of components
	void AddComponent(Component* pComp);

	//Deletes a component from the list
	void DeleteComponent(Component* pComp);

	//Finds component at given coordinates
	Component* GetComponentAt(int x, int y);

	//Breaks all connections to/from a component
	void BreakConnections(Component* comp);

	// ==== Clipboard operations ====
	void SetClipboard(Component* c);
	Component* GetClipboard() const;

	void SetSelected(Component* pComponent);

	Component* GetSelected() const;

	void UnselectAll();

	int GetSelectedCount() const;
	void MoveSelected(int x, int y);

	/*void AddConnection(Connection* pConn);
	Connection* GetConnectionAt(int x, int y);*/

	//destructor
	~ApplicationManager();

};

#endif