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
#include "Actions\AddLED.h"
#include "Components\Connection.h"
#include "Actions\AddConnection.h"
#include "Actions\AddSwitch.h"
#include "Actions\Move.h"
#include "Actions\UndoAction.h"
#include "Actions\RedoAction.h"
//#include "Actions\CopyAction.h"
//#include "Actions\ActionDelete.h"
//#include "Actions\PasteAction.h"
//#include "Actions\CutAction.h"

#include "Actions/SaveAction.h"
#include "Actions/LoadAction.h"

#include "Actions/SwitchToSim.h"
#include "Actions/SwitchToDesign.h"
#include "Actions/Simulate.h"
#include "Actions/ChangeSwitch.h"
#include "Actions/Validate.h"
#include "Actions/CreateTruthTable.h"
#include "Actions/Probing.h"

#include "Actions\AddLabel.h"
#include <string>
using std::string;



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

	UndoCount = 0; //Initialize el stack lel undo/redo
	UndoPos = -1; // -1 means no actions performed yet
	for (int i = 0; i < MaxUndoCount; i++)
		UndoStack[i] = nullptr;


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

	case ADD_SWITCH:
		pAct = new AddSwitch(this);
		break;
		
	case ADD_LED:
		pAct = new AddLED(this);
		break;

	case SELECT:
		pAct = new Select(this);
		break;
	case MOVE:
		pAct = new Move(this);
		break;

	case UNDO:
		pAct = new UndoAction(this);
		break;

	case REDO:
		pAct = new RedoAction(this);
		break;
	case ADD_LABEL:
		pAct = new AddLabel(this);
		break;

	case SAVE:
		pAct = new SaveAction(this);
		break;

	case LOAD:
		pAct = new LoadAction(this);
		break;

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


//Mariaaam lw ghlt deleteee

	// ====================================================
	//                  MODE SWITCHING
	// ====================================================

	case SIM_MODE:   // User clicked "Simulation Mode" button
		pAct = new Simulate(this);
		break;

	case DSN_MODE:   // User clicked "Design Mode" button
		pAct = new SwitchToDesign(this);
		break;

		// ====================================================
		//                  SIMULATION ACTIONS
		// ====================================================

	case SIMULATE:   // The "Run" button inside Simulation toolbar
		// pAct = new RunSimulation(this); // Uncomment if you have this action
		break;

	case CREATE_TRUTH_TABLE:
		// pAct = new CreateTruthTable(this); // Uncomment if you have this action
		break;

	case VALIDATE: // or ITM_VALIDATE depending on your enum

		pAct = new Validate(this);

		break;

	case EXIT:
		break;
	}

	// ====================================================
	//                  EXECUTION LOGIC
	// ====================================================

	// Execute the created action
	if (pAct)
	{
		pAct->Execute(); // Execute

		// Handle Undo/Redo recording
		if (pAct->isUndoable())
		{
			RecordAction(pAct);
		}
		else
		{
			delete pAct; // Delete non-undoable actions
			pAct = NULL;
		}
	}





}


void ApplicationManager::UpdateInterface()
{

	OutputInterface->ClearDrawingArea();
	for (int i = 0; i < CompCount; i++)
		CompList[i]->Draw(OutputInterface);

	/*for (int i = 0; i < ConnCount; i++)
		ConnCount[i]->Draw(OutputInterface);*/
}

Component* ApplicationManager::GetOneSelectedComponent()
{
	for (int i = 0; i < CompCount; i++)
	{
		if (CompList[i]->IsSelected())
			return CompList[i];
	}
	return nullptr;
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
		// Gates use the standard IsInside (Rectangle) defined in Component.h
		// Connections use the custom IsInside (Lines) we are about to add
		if (CompList[i]->IsInside(x, y))
		{
			return CompList[i];
		}
	}
	return nullptr;
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
			//delete CompList[i]; Commented for undo/redo purposes

			// Shift remaining components
			for (int j = i; j < CompCount - 1; j++)
				CompList[j] = CompList[j + 1];

			CompList[CompCount - 1] = nullptr;
			CompCount--;
			OutputInterface->PrintMsg("Debug: Component found and removed from list.");
			return;
			break;
		}
	}
	OutputInterface->PrintMsg("Debug: Component NOT found in list!");
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
int ApplicationManager::GetSelectedCount() const
{
	int count = 0;
	for (int i = 0; i < CompCount; i++)
	{
		if (CompList[i]->IsSelected())
			count++;
	}
	return count;
}

// Moves all selected components by the calculated difference
void ApplicationManager::MoveSelected(int dx, int dy)
{
	for (int i = 0; i < CompCount; i++)
	{
		if (CompList[i]->IsSelected())
		{
			GraphicsInfo GInfo = CompList[i]->GetGraphicsInfo();

			// Update coordinates
			GInfo.x1 += dx;
			GInfo.x2 += dx;
			GInfo.y1 += dy;
			GInfo.y2 += dy;

			// Optional: Add boundary checks here to prevent moving outside window
			if (GInfo.x1 < 0) continue; // Example check
			if (GInfo.y1 < UI.ToolBarHeight) continue; // Don't move into toolbar

			CompList[i]->SetGraphicsInfo(GInfo);
		}
	}
}
void ApplicationManager::RecordAction(Action* pAct)
{
	if (!pAct->isUndoable()) return;

	// 1. If we are somewhere in the middle (because we undid some actions), 
	//    we must delete the "future" actions before adding a new one.
	while (UndoCount > UndoPos + 1)
	{
		UndoCount--;
		if (UndoStack[UndoCount])
			delete UndoStack[UndoCount];
		UndoStack[UndoCount] = NULL;
	}

	// 2. If stack is full, shift everything left to make room at the end
	if (UndoCount == MaxUndoCount)
	{
		if (UndoStack[0]) delete UndoStack[0]; // Delete oldest action

		// Shift
		for (int i = 0; i < MaxUndoCount - 1; i++)
			UndoStack[i] = UndoStack[i + 1];

		UndoCount--; // We removed one
		UndoPos--;   // Position moves back one
	}

	// 3. Add the new action
	UndoPos++;
	UndoStack[UndoPos] = pAct;
	UndoCount++;
}

void ApplicationManager::ExecuteUndo()
{
	if (UndoPos > -1)
	{
		UndoStack[UndoPos]->Undo();
		UndoPos--;
	}
	else
	{
		OutputInterface->PrintMsg("Nothing to Undo!");
	}
}

void ApplicationManager::ExecuteRedo()
{
	if (UndoPos < UndoCount - 1)
	{
		UndoPos++;
		UndoStack[UndoPos]->Redo();
	}
	else
	{
		OutputInterface->PrintMsg("Nothing to Redo!");
	}
}


Component* ApplicationManager::GetComponent(int index) const
{
	if (index >= 0 && index < CompCount)
		return CompList[index];
	return nullptr;
}

int ApplicationManager::GetCompCount() const
{
	return CompCount;
}




void ApplicationManager::ClearAll()
{
	for (int i = 0; i < CompCount; ++i)
	{
		delete CompList[i];
		CompList[i] = nullptr;
	}

	CompCount = 0;
	Clipboard = nullptr;
	SelectedComponent = nullptr;
	// لو عندك NextID ضيف السطر دا
	// NextID = 1;
}



Component* ApplicationManager::CreateComponentByType(const string& type, const GraphicsInfo& gfx)
{
	if (type == "SWTCH")
		return new Switch(gfx, SWITCH_FANOUT);

	if (type == "LED")
		return new LED(gfx, 1);

	if (type == "AND2")
		return new AND2(gfx, AND2_FANOUT);

	if (type == "OR2")
		return new OR2(gfx, OR2_FANOUT);

	if (type == "NAND2")
		return new NAND2(gfx, NAND2_FANOUT);

	if (type == "NOR2")                  // ← 
		return new NOR2(gfx, NOR2_FANOUT);

	if (type == "NOR3")
		return new NOR3(gfx, NOR3_FANOUT);

	if (type == "XOR2")
		return new XOR2(gfx, XOR2_FANOUT);

	if (type == "XNOR2")
		return new XNOR2(gfx, XNOR2_FANOUT);

	if (type == "AND3")
		return new AND3(gfx, AND3_FANOUT);

	if (type == "XOR3")
		return new XOR3(gfx, XOR3_FANOUT);

	if (type == "INV")
		return new INV(gfx, INV_FANOUT);

	if (type == "BUFF")
		return new BUFF(gfx, BUFF_FANOUT);

	return nullptr;
}


void ApplicationManager::Save(ofstream& out)
{
	int realCount = 0;

	for (int i = 0; i < CompCount; i++)
		if (dynamic_cast<Connection*>(CompList[i]) == nullptr)
			realCount++;

	out << realCount << "\n";

	// Save components
	for (int i = 0; i < CompCount; ++i)
		if (!dynamic_cast<Connection*>(CompList[i]))
			CompList[i]->Save(out);

	out << "Connections\n";

	// Save connections ONLY
	for (int i = 0; i < CompCount; ++i)
		if (auto* C = dynamic_cast<Connection*>(CompList[i]))
			C->Save(out);

	out << "-1\n";
}



void ApplicationManager::Load(ifstream& in)
{
	ClearAll();

	int count;
	in >> count;

	// مصفوفة ثابتة بدل vector
	const int MAXMAP = 500;
	Component* idMap[MAXMAP];

	for (int i = 0; i < MAXMAP; i++)
		idMap[i] = nullptr;

	// --- تحميل الكمبوننتس ---
	for (int i = 0; i < count; i++)
	{
		string type;
		in >> type;

		GraphicsInfo gfx;
		gfx.x1 = gfx.y1 = gfx.x2 = gfx.y2 = 0;

		Component* comp = CreateComponentByType(type, gfx);
		if (!comp)
		{
			// لو النوع مش معروف نعدي السطر
			int dummyID, x1, y1, x2, y2;
			string dummyLabel;
			in >> dummyID >> dummyLabel >> x1 >> y1 >> x2 >> y2;
			continue;
		}

		comp->Load(in);  // يضبط: ID + label + gfx

		int ID = comp->GetID();
		if (ID >= 0 && ID < MAXMAP)
			idMap[ID] = comp;

		CompList[CompCount++] = comp;
	}

	// --- قراءة connections ---
	string word;
	in >> word; // المفروض "Connections"

	while (true)
	{
		int srcID;
		in >> srcID;

		if (!in || srcID == -1)
			break;

		int dstID, pinNo;
		in >> dstID >> pinNo;

		if (srcID < 0 || srcID >= MAXMAP ||
			dstID < 0 || dstID >= MAXMAP)
			continue;

		Component* src = idMap[srcID];
		Component* dst = idMap[dstID];

		if (!src || !dst)
			continue;

		OutputPin* srcPin = nullptr;
		InputPin* dstPin = nullptr;

		// مصدر السلك لازم Gate أو Switch (كله Gate عندك)
		if (Gate* g = dynamic_cast<Gate*>(src))
			srcPin = g->GetOutputPin();

		// الطرف المستقبل
		if (Gate* g = dynamic_cast<Gate*>(dst))
			dstPin = g->GetInputPin(pinNo - 1);
		else if (LED* L = dynamic_cast<LED*>(dst))
			dstPin = L->GetInputPin();

		if (!srcPin || !dstPin) continue;

		GraphicsInfo gfx;
		gfx.x1 = gfx.y1 = gfx.x2 = gfx.y2 = 0;

		Connection* conn = new Connection(gfx, srcPin, dstPin);
		CompList[CompCount++] = conn;
	}
}




ApplicationManager::~ApplicationManager()
{
	for (int i = 0; i < CompCount; i++)
		delete CompList[i];
	delete OutputInterface;
}




