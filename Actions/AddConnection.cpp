#include "AddConnection.h"
#include "..\ApplicationManager.h"
#include "..\Components\Gate.h"
#include "..\Components\Connection.h"
#include "..\Components\LED.h"

AddConnection::AddConnection(ApplicationManager* pApp)
    : Action(pApp)
{
    SrcGate = nullptr;
    DstGate = nullptr;
    SrcPin = nullptr;
    DstPin = nullptr;
	m_pConnection=nullptr;
}


void AddConnection::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	int x, y;

    
	pOut->PrintMsg("Select source gate (output pin)");
	pIn->GetPointClicked(x, y);

	Component* pComp = pManager->GetComponentAt(x, y);
	if (!pComp || !pComp->IsGate())
	{
		pOut->PrintMsg("Invalid source: please select a gate");
		return;
	}

	SrcGate = static_cast<Gate*>(pComp);
	SrcPin = SrcGate->GetOutputPin();

	if (!SrcPin->CanConnect())
	{
		pOut->PrintMsg("Source fan-out exceeded");
		SrcGate = nullptr;
		SrcPin = nullptr;
		return;
	}

   
	pOut->PrintMsg("Select destination gate (input pin)");
	pIn->GetPointClicked(x, y);

	pComp = pManager->GetComponentAt(x, y);
	if (!pComp || (!pComp->IsGate() && !pComp->IsLED()))
	{
		pOut->PrintMsg("Invalid destination: please select a gate or LED ");
		SrcGate = nullptr;
		SrcPin = nullptr;
		return;
	}

	

	if (pComp == SrcGate )
	{
		pOut->PrintMsg("Error: Cannot connect a gate to itself (Feedback Loop).");
		SrcGate = nullptr;
		SrcPin = nullptr;
		DstGate = nullptr; 
		return;
	}

	if (pComp->GetGraphicsInfo().x1 < SrcGate->GetGraphicsInfo().x1)
	{
		pOut->PrintMsg("Error: Destination is behind Source. Please move it forward to connect.");

		SrcGate = nullptr;
		SrcPin = nullptr;
		DstGate = nullptr;
		return;
	}
	// pick first free input pin
	DstPin = nullptr;
	if (pComp->IsGate())
	{
		DstGate = static_cast<Gate*>(pComp); // Safe cast now
		for (int i = 0; i < DstGate->GetInputPinCount(); i++)
		{
			if (!DstGate->GetInputPin(i)->getIsConnected())
			{
				DstPin = DstGate->GetInputPin(i);
				break;
			}
		}
	}
	else if (pComp->IsLED())
	{
		DstGate = nullptr; // Explicitly set to null for LEDs

		LED* pled = static_cast<LED*>(pComp);

		if (!pled->GetInputPin()->getIsConnected())
		{
			DstPin = pled->GetInputPin();
		}
	}
	if (!DstPin)
	{
		pOut->PrintMsg("Destination input pins are all connected");
		SrcGate = nullptr;
		SrcPin = nullptr;
		DstGate = nullptr;
		return;
	}

    
	GInfo.x1 = SrcPin->getPositionX(); 
	GInfo.y1 = SrcPin->getPositionY();  
	GInfo.x2 = DstPin->getPositionX();  
	GInfo.y2 = DstPin->getPositionY(); 

	pOut->ClearStatusBar();



}
void AddConnection::Execute()
{
	
	ReadActionParameters();
	// If parameters are invalid, return
	 if (!SrcPin || !DstPin)
		return;
	// Create the connection
	 m_pConnection = new Connection(GInfo, SrcPin, DstPin); //For undo-redo

	// Add the connection to the application manager
	 pManager->AddComponent(m_pConnection);
	// Connect the pins
	SrcPin->ConnectTo(m_pConnection);
	DstPin->connect();  // Mark input pin as connected

	DstPin->setConnection(m_pConnection);
}

void AddConnection::Undo()
{
	// Safety check: law mafi4 connection, mate3mel4 7aga
	if (m_pConnection == nullptr) return;

	// 1. Remove the connection from the ApplicationManager (Visuals)
	// This takes it off the screen but DOES NOT delete it from memory.
	//Law fi connection wel user clicked undo, remove mn el screen 
	// bas ma tms7hash mn el memory 3ashan law 3ayz yredo
	pManager->RemoveComponent(m_pConnection);

	//Disconnect 3a4an el simulation yozbot
	m_pConnection->Disconnect();
}

void AddConnection::Redo()
{
	// nafs el safety check
	if (m_pConnection == nullptr) return;

	// Connect tani ka visuals
	pManager->AddComponent(m_pConnection);

	//7ot el pins tani

	SrcPin->ConnectTo(m_pConnection);
	DstPin->connect();
	DstPin->setConnection(m_pConnection);
}

AddConnection::~AddConnection()
{
}