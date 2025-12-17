#ifndef APPLICATION_MANAGER_H
#define APPLICATION_MANAGER_H

#include "Defs.h"
#include "GUI/Output.h"          // Fixed slash
#include "GUI/Input.h"           // Fixed slash
#include "Actions/Action.h"      // Fixed slash
#include "Components/Component.h" // Fixed slash
#include <fstream>
#include <string>

using std::string;
using std::ofstream;
using std::ifstream;

class ApplicationManager
{
	enum { MaxCompCount = 200 };

private:
	int CompCount;
	Component* CompList[MaxCompCount];

	Output* OutputInterface;
	Input* InputInterface;

	Component* Clipboard;
	Component* SelectedComponent;

	Action* UndoStack[MaxUndoCount];
	int UndoCount;
	int UndoPos;

public:
	Component* GetComponent(int index) const;
	int GetCompCount() const;

	ApplicationManager();
	~ApplicationManager();

	ActionType GetUserAction();
	void ExecuteAction(ActionType);
	void UpdateInterface();

	Output* GetOutput();
	Input* GetInput();

	void AddComponent(Component* pComp);
	void DeleteComponent(Component* pComp);
	Component* GetComponentAt(int x, int y);
	void BreakConnections(Component* comp);

	void SetClipboard(Component* c);
	Component* GetClipboard() const;

	void RemoveComponent(Component* pComp);
	void SetSelected(Component* pComponent);
	Component* GetSelected() const;
	void UnselectAll();
	int GetSelectedCount() const;
	void MoveSelected(int x, int y);

	void ExecuteCircuit();
	void RecordAction(Action* pAct);
	void ExecuteUndo();
	void ExecuteRedo();

	void ClearAll();
	Component* CreateComponentByType(const string& type, const GraphicsInfo& gfx);
	void Save(ofstream& out);
	void Load(ifstream& in);

	bool CheckCollision(int newX, int newY, int newWidth, int newHeight, Component* skipComp = nullptr);
	Component* GetOneSelectedComponent();
};

#endif