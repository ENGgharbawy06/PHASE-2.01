#include "ApplicationManager.h"
#include "Actions\AddANDgate2.h"
#include "Actions\AddORgate2.h"
#include "Actions\AddNANDgate2.h"
#include "Actions\AddNORgate2.h"
#include "Actions\AddXORgate2.h"
#include "Actions\AddXNORgate2.h"
#include "Actions\AddANDgate3.h"
#include "Actions\AddNORgate3.h"
#include "Actions\AddXORgate3.h"
#include "Actions\AddBUFF.h"
#include "Actions\AddINV.h"
#include "Actions\Select.h"
#include "Components/Connection.h"
#include "Actions\AddConnection.h"
//#include "Actions\CopyAction.h"
//#include "Actions\ActionDelete.h"
//#include "Actions\PasteAction.h"
//#include "Actions\CutAction.h"
//
//
//#include "Actions/SwitchToSim.h"
//#include "Actions/SwitchToDesign.h"
//#include "Actions/Simulate.h"
//#include "Actions/ChangeSwitch.h"
//#include "Actions/Validate.h"
//#include "Actions/CreateTruthTable.h"

//#include "Actions\AddLabel.h"




ApplicationManager::ApplicationManager()
{
	CompCount = 0;
	/*ConnCount = 0;*/
	Clipboard = nullptr;
	SelectedComponent = nullptr;

	for (int i = 0; i < MaxCompCount; i++)
		CompList[i] = NULL;

	//Creates the Input / Output Objects & Initialize the GUI
	OutputInterface = new Output();
	InputInterface = OutputInterface->CreateInput();
}

//////////////////////////////////////////////////////////////////
void ApplicationManager::AddComponent(Component* pComp)
{
	CompList[CompCount++] = pComp;
}

////////////////////////////////////////////////////////////////////
ActionType ApplicationManager::GetUserAction()
{
	//Call input to get what action is required from the user
	return InputInterface->GetUserAction();
}

///////////////////////////////////////////////////////////////////
void ApplicationManager::ExecuteAction(ActionType ActType)
{
	Action* pAct = NULL;
	switch (ActType)
	{
	case ADD_AND_GATE_2:
		pAct = new AddANDgate2(this);
		break;

	case ADD_OR_GATE_2:
		pAct = new AddORgate2(this);
		break;
	case ADD_NAND_GATE_2:
		pAct = new AddNANDgate2(this);
		break;
	case ADD_NOR_GATE_2:
		pAct = new AddNORgate2(this);
		break;
	case ADD_XOR_GATE_2:
		pAct = new AddXORgate2(this);
		break;
	case ADD_XNOR_GATE_2:
		pAct = new AddXNORgate2(this);
		break;
	case ADD_AND_GATE_3:
		pAct = new AddANDgate3(this);
		break;
	case ADD_NOR_GATE_3:
		pAct = new AddNORgate3(this);
		break;
	case ADD_XOR_GATE_3:
		pAct = new AddXORgate3(this);
		break;
	case ADD_INV:
		pAct = new AddINV(this);
		break;
	
	case ADD_BUFF:
		pAct = new AddBuffer(this);
		break;

	case ADD_CONNECTION:
		pAct = new AddConnection(this);
		break;
		
	case SELECT:
		pAct = new Select(this);
		break;
		/*case MOVE:
			pAct = new Move(this);*/
			/*case COPY:
				pAct = new CopyAction(this);
				break;*/
				//case PASTE:
				//	pAct = new PasteAction(this);
				//	break;
				//case CUT:
				//	pAct = new CutAction(this);
				//	break;

	//case DEL:
	//	//TODO: Create Delete Action here
	//	pAct = new ActionDelete(this);
	//	break;

					//case ADD_CONNECTION:
				//	//TODO: Create AddConnection Action here
				//	break;
	case EXIT:
		//TODO: create ExitAction here
		break;
	}

	if (pAct)
	{
		pAct->Execute();
		delete pAct;
		pAct = NULL;
	}
}


void ApplicationManager::UpdateInterface()
{
	for (int i = 0; i < CompCount; i++)
		CompList[i]->Draw(OutputInterface);

	/*for (int i = 0; i < ConnCount; i++)
		ConnCount[i]->Draw(OutputInterface);*/
}

Input* ApplicationManager::GetInput()
{
	return InputInterface;
}

Output* ApplicationManager::GetOutput()
{
	return OutputInterface;
}

// Find component at given coordinates
Component* ApplicationManager::GetComponentAt(int x, int y)
{
	for (int i = 0; i < CompCount; i++)
	{
		GraphicsInfo gfx = CompList[i]->GetGraphicsInfo();
		if (x >= gfx.x1 && x <= gfx.x2 && y >= gfx.y1 && y <= gfx.y2)
		{
			return CompList[i];
		}
	}	
			return nullptr;  //No component found, 3a4an el deselect
	
}

////////////////////////////////////////////////////////////////////
// Delete a component from the list
void ApplicationManager::DeleteComponent(Component* pComp)
{
	if (!pComp) return;

	for (int i = 0; i < CompCount; i++)
	{
		if (CompList[i] == pComp)
		{
			delete CompList[i];

			// Shift remaining components
			for (int j = i; j < CompCount - 1; j++)
				CompList[j] = CompList[j + 1];

			CompList[CompCount - 1] = nullptr;
			CompCount--;
			break;
		}
	}
}

////////////////////////////////////////////////////////////////////
// Break all connections to/from a component
void ApplicationManager::BreakConnections(Component* comp)
{
	// TODO: Implement this to disconnect all wires connected to the component
	// For now, this is a placeholder
	// You'll need to iterate through all connections and remove ones
	// that are connected to this component
}

////////////////////////////////////////////////////////////////////
// Clipboard operations
void ApplicationManager::SetClipboard(Component* c)
{
	Clipboard = c;
}

Component* ApplicationManager::GetClipboard() const
{
	return Clipboard;
}

//////////////////////////////////////////////////////////////////
ApplicationManager::~ApplicationManager()
{
	for (int i = 0; i < CompCount; i++)
		delete CompList[i];
	delete OutputInterface;
}
void ApplicationManager::SetSelected(Component* pComponent)
{

	SelectedComponent = pComponent;
}

Component* ApplicationManager::GetSelected() const
{
	return SelectedComponent;
}

void ApplicationManager::UnselectAll()
{
	for (int i=0; i < CompCount; i++)
	{
		CompList[i]->SetSelected(false);
	}
	SelectedComponent = nullptr;
}