#ifndef APPLICATION_MANAGER_H
#define APPLICATION_MANAGER_H
#include "Defs.h"
#include "GUI\Output.h"
#include "GUI\Input.h"
#include "Actions\Action.h"
#include "Components\Component.h"
#include <vector>

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

	// === multi-selection support ===
	std::vector<Component*> SelectedComponents;

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

	// === selection API ===
	void SetSelected(Component* pComponent); // keep for backward compatibility (single selected pointer)
	Component* GetSelected() const;

	void AddToSelection(Component* c);
	void RemoveFromSelection(Component* c);
	void ClearSelection();
	std::vector<Component*> GetAllSelected() const;

	// === helpers for delete/undo/redo ===
	int GetComponentIndex(Component* c) const;
	void InsertComponentAt(int index, Component* c);

	//destructor
	~ApplicationManager();

	// Optional getters for components array/count (useful if other code needs them)
	int GetCompCount() const { return CompCount; }
	Component** GetCompList() { return CompList; }
};
#endif