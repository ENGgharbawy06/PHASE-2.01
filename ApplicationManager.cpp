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
#include "Components\LED.h"
#include "Components\Label.h"
#include "Actions\Move.h"
#include "Actions\UndoAction.h"
#include "Actions\RedoAction.h"
#include "Actions\CopyAction.h"
#include "Actions\Delete.h"
#include "Actions\PasteAction.h"
#include "Actions\CutAction.h"

#include "Actions/SaveAction.h"
#include "Actions/LoadAction.h"

#include "Actions/SwitchToSim.h"
#include "Actions/SwitchToDesign.h"
#include "Actions/Simulate.h"
#include "Actions/ChangeSwitch.h"
#include "Actions/Validate.h"
#include "Actions/CreateTruthTable.h"
#include "Actions/Probing.h"
#include "Actions\EditLabel.h"
#include "Actions\AddLabel.h"
#include <string>



ApplicationManager::ApplicationManager()
{
	CompCount = 0;
	Clipboard = nullptr;
	SelectedComponent = nullptr;

	for (int i = 0; i < MaxCompCount; i++)
		CompList[i] = nullptr;

	//Creates the Input / Output Objects & Initialize the GUI
	OutputInterface = new Output();
	InputInterface = OutputInterface->CreateInput();

	UndoCount = 0; //Initialize el stack lel undo/redo
	UndoPos = -1; // -1 means no actions performed yet
	for (int i = 0; i < MaxUndoCount; i++)
		UndoStack[i] = nullptr;


}


void ApplicationManager::AddComponent(Component* pComp)
{
								        // Assign a unique ID based on the current count
	pComp->SetID(CompCount);

	CompList[CompCount++] = pComp;
}

ActionType ApplicationManager::GetUserAction()
{
	//Call input to get what action is required from the user
	return InputInterface->GetUserAction();
}


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
	case DEL:
		pAct = new Delete(this);
		break;


	case COPY:
		pAct = new CopyAction(this);
		break;

	case PASTE:
		pAct = new PasteAction(this);
		break;
		
	case CUT:
		pAct = new CutAction(this);
		break;

	case EDIT_LABEL:
		pAct = new EditLabel(this);
		break;

	
	//MODE SWITCHING

	case SIM_MODE:   // User clicked "Simulation Mode" button
		pAct = new SwitchToSim(this);
		break;

	case DSN_MODE:   // User clicked "Design Mode" button
		pAct = new SwitchToDesign(this);
		break;

		//SIMULATION ACTIONS

	case SIMULATE:
		pAct = new Simulate(this);   
		break;

	case CREATE_TRUTH_TABLE:
		pAct = new CreateTruthTable(this);
		break;

	case VALIDATE:
		pAct = new Validate(this);
		break;

	case CHANGE_SWITCH:               
		pAct = new ChangeSwitch(this);  
		break;

	

	case EXIT:
		break;  
	}

	if (pAct)
	{
		pAct->Execute();

		// Handle Undo/Redo (to see if the action is undoable or not)
		if (pAct->isUndoable())
		{
			RecordAction(pAct);
		}
		else
		{
			delete pAct;
			pAct = NULL;
		}
	}
} 

		


void ApplicationManager::ExecuteCircuit()
{
	// Iterate multiple times to ensure signals propagate through all levels of the circuit
	// (e.g., Switch -> Connection -> Gate -> Connection -> LED)
	//beyebda2 3and switch aw gate w beye5las 3and gate aw led
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < CompCount; j++)
		{
			if (CompList[j])
				CompList[j]->Operate();
		}
	}
}


void ApplicationManager::UpdateInterface()
{

	OutputInterface->ClearDrawingArea();
	for (int i = 0; i < CompCount; i++)
		CompList[i]->Draw(OutputInterface);

	
}
Input* ApplicationManager::GetInput()
{
	return InputInterface;
}

Output* ApplicationManager::GetOutput()
{
	return OutputInterface;
}

Component* ApplicationManager::GetComponentAt(int x, int y)
{
	for (int i = 0; i < CompCount; i++)
	{
		if (CompList[i]->IsInside(x, y))
		{
			return CompList[i];
		}
	}
	return nullptr;
}

//COLLISION DETECTION HELPER
//3a4an el MOVE kanet bete3mel overlap 3ala components w connections tanya

bool ApplicationManager::CheckCollision(int newX, int newY, int newWidth, int newHeight, Component* skipComp)
{
	// Calculate the rectangle of the component we are trying to PLACE/MOVE (lel move button)
	int newLeft = newX;
	int newRight = newX + newWidth;
	int newTop = newY;
	int newBottom = newY + newHeight;

	for (int i = 0; i < CompCount; i++)
	{
		Component* c = CompList[i];

		
		if (c == nullptr || c == skipComp || dynamic_cast<Connection*>(c))
			continue;

		GraphicsInfo gfx = c->GetGraphicsInfo(); 

		int existingLeft = gfx.x1;
		int existingRight = gfx.x2;
		int existingTop = gfx.y1;
		int existingBottom = gfx.y2;

		// Two rectangles overlap if:
		// (Left1 < Right2) AND (Right1 > Left2) AND (Top1 < Bottom2) AND (Bottom1 > Top2)

		bool overlapX = (newLeft < existingRight) && (newRight > existingLeft);
		bool overlapY = (newTop < existingBottom) && (newBottom > existingTop);

		if (overlapX && overlapY)
		{
			return true; // Collision found!
		}
	}

	return false; 
}


// Delete a component from the list
void ApplicationManager::DeleteComponent(Component* pComp)
{
	if (!pComp) return;

	for (int i = 0; i < CompCount; i++)
	{
		if (CompList[i] == pComp)
		{
			

			// Shift remaining components
			for (int j = i; j < CompCount - 1; j++)
				CompList[j] = CompList[j + 1];

			CompList[CompCount - 1] = nullptr;
			CompCount--;
			OutputInterface->PrintMsg("Component found and removed from list.");
			return;
			break;
		}
	}
	OutputInterface->PrintMsg("Component NOT found in list!");
}

// Break all connections to/from a component
void ApplicationManager::BreakConnections(Component* pComp)
{
	
	if (!pComp) return;

	//Get the Pins of the component we are deleting
	OutputPin* pCompOut = pComp->GetOutputPin();

	// Check up to 3 inputs (covers most gates). 
	InputPin* pCompIn0 = pComp->GetInputPin(0);
	InputPin* pCompIn1 = pComp->GetInputPin(1);
	InputPin* pCompIn2 = pComp->GetInputPin(2);

	//Loop through all components to find WIRES
	for (int i = 0; i < CompCount; i++)
	{
		Component* c = CompList[i];

		// Check if this component says "I am a connection"
		if (c->IsConnection())
		{
			Connection* pConn = (Connection*)c;

			bool shouldDelete = false;

			//CHECK 1: Is the wire starting FROM the deleted component?
			if (pCompOut != nullptr && pConn->getSourcePin() == pCompOut)
			{
				shouldDelete = true;
			}

			//CHECK 2: Is the wire going TO the deleted component?
			InputPin* wireDest = pConn->getDestPin();

			if (wireDest != nullptr)
			{
				if (wireDest == pCompIn0 || wireDest == pCompIn1 || wireDest == pCompIn2)
				{
					shouldDelete = true;
				}
			}

			//DELETE THE WIRE IF MATCHED
			if (shouldDelete)
			{
				DeleteComponent(pConn);
				i--; // Step back index since list shifted
			}
		}
	}
}

//setting up the clipboard

void ApplicationManager::SetClipboard(Component* c)   
{
	Clipboard = c;
}

Component* ApplicationManager::GetClipboard() const  
{
	return Clipboard;
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

			if (GInfo.x1 < 0) continue; // Example check
			if (GInfo.y1 < UI.ToolBarHeight) continue; // Don't move into toolbar

			CompList[i]->SetGraphicsInfo(GInfo);
		}
	}
}
void ApplicationManager::RecordAction(Action* pAct)
{
	if (!pAct->isUndoable()) return;

	//If we are somewhere in the middle (because we undid some actions), 
	//we must delete the "future" actions before adding a new one.
	while (UndoCount > UndoPos + 1)
	{
		UndoCount--;
		if (UndoStack[UndoCount])
			delete UndoStack[UndoCount];
		UndoStack[UndoCount] = NULL;
	}

	//If stack is full, shift everything left to make room at the end
	if (UndoCount == MaxUndoCount)
	{
		if (UndoStack[0]) delete UndoStack[0]; // Delete oldest action

		// Shift
		for (int i = 0; i < MaxUndoCount - 1; i++)
			UndoStack[i] = UndoStack[i + 1];

		UndoCount--; // We removed one
		UndoPos--;   // Position moves back one
	}

	//Add the new action
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

	if (type == "NOR2")
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

	if (type == "LABEL")
		return new Label(gfx, "");

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

	const int MAXMAP = 500;
	Component* idMap[MAXMAP];

	for (int i = 0; i < MAXMAP; i++)
		idMap[i] = nullptr;

	// components
	for (int i = 0; i < count; i++)
	{
		string type;
		in >> type;

		GraphicsInfo gfx;
		gfx.x1 = gfx.y1 = gfx.x2 = gfx.y2 = 0;

		Component* comp = CreateComponentByType(type, gfx);
		if (!comp)
		{
			// if unknown ignore 
			int dummyID, x1, y1, x2, y2;
			string dummyLabel;
			in >> dummyID >> dummyLabel >> x1 >> y1 >> x2 >> y2;
			continue;
		}

		comp->Load(in);  

		int ID = comp->GetID();
		if (ID >= 0 && ID < MAXMAP)
			idMap[ID] = comp;

		CompList[CompCount++] = comp;
	}

	// read connections 
	string word;
	in >> word; 

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

		
		if (Gate* g = dynamic_cast<Gate*>(src))
			srcPin = g->GetOutputPin();

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

Component* ApplicationManager::GetOneSelectedComponent()
{
	for (int i = 0; i < CompCount; i++)
		if (CompList[i]->IsSelected())
			return CompList[i];

	return nullptr;
}

// Remove a component from the list WITHOUT deleting it (Undo/Redo friendly)
void ApplicationManager::RemoveComponent(Component* pComp)
{
	if (!pComp) return;

	for (int i = 0; i < CompCount; i++)
	{
		if (CompList[i] == pComp)
		{
			// Shift remaining components
			for (int j = i; j < CompCount - 1; j++)
				CompList[j] = CompList[j + 1];

			CompList[CompCount - 1] = nullptr;
			CompCount--;
			return;
		}
	}
}


ApplicationManager::~ApplicationManager()
{
	for (int i = 0; i < CompCount; i++)
		delete CompList[i];
	delete OutputInterface;
}

