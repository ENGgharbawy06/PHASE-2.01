#include "AddConnection.h"
#include "..\ApplicationManager.h"

AddConnection::AddConnection(ApplicationManager* pApp)
    : Action(pApp)
{
    SrcGate = nullptr;
    DstGate = nullptr;
    SrcPin = nullptr;
    DstPin = nullptr;
}


void AddConnection::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	int x, y;

    // ===============================
	// Select source gate (output pin)
    // ===============================
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

    // ===============================
	// Select destination gate (input)
    // ===============================
	pOut->PrintMsg("Select destination gate (input pin)");
	pIn->GetPointClicked(x, y);

	pComp = pManager->GetComponentAt(x, y);
	if (!pComp || !pComp->IsGate())
	{
		pOut->PrintMsg("Invalid destination: please select a gate");
		SrcGate = nullptr;
		SrcPin = nullptr;
		return;
	}

	DstGate = static_cast<Gate*>(pComp);

	// pick first free input pin
	DstPin = nullptr;
	for (int i = 0; i < DstGate->GetInputPinCount(); i++)
	{
		if (!DstGate->GetInputPin(i)->getIsConnected())  // Changed from isConnected()
		{
			DstPin = DstGate->GetInputPin(i);
			break;
		}
	}

	if (!DstPin)
	{
		pOut->PrintMsg("No free input pins on destination gate");
		SrcGate = nullptr;
		SrcPin = nullptr;
		DstGate = nullptr;
		return;
	}

    // ===============================
	// Graphics info (pin-to-pin)
	GInfo.x1 = SrcPin->getPositionX();  // Changed from getPosition().x
	GInfo.y1 = SrcPin->getPositionY();  // Changed from getPosition().y
	GInfo.x2 = DstPin->getPositionX();  // Changed from getPosition().x
	GInfo.y2 = DstPin->getPositionY();  // Changed from getPosition().y

	pOut->ClearStatusBar();



}
void AddConnection::Execute()
{
	// Read action parameters
	ReadActionParameters();
	// If parameters are invalid, return
	if (!SrcGate || !DstGate || !SrcPin || !DstPin)
		return;
	// Create the connection
	Connection* pConn = new Connection(GInfo, SrcPin, DstPin);

	// Add the connection to the application manager
	pManager->AddComponent(pConn);
	// Connect the pins
	SrcPin->ConnectTo(pConn);
	DstPin->connect();  // Mark input pin as connected
}
AddConnection::~AddConnection()
{
}
void AddConnection::Undo()
{
	// Remove the connection from the application manager
	// Disconnect the pins
	// Note: You need to implement these functionalities in ApplicationManager and Pin classes
}

void AddConnection::Redo()
{
	// Re-add the connection to the application manager
	// Reconnect the pins
	// Note: You need to implement these functionalities in ApplicationManager and Pin classes
}