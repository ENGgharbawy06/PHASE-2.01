#include "AddConnection.h"
#include "ApplicationManager.h"
#include "Input.h"
#include "Output.h"

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
        if (!DstGate->GetInputPin(i)->isConnected())
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
    // ===============================
    GInfo.x1 = SrcPin->getPosition().x;
    GInfo.y1 = SrcPin->getPosition().y;
    GInfo.x2 = DstPin->getPosition().x;
    GInfo.y2 = DstPin->getPosition().y;

    pOut->ClearStatusBar();
}

void AddConnection::Execute()
{
    ReadActionParameters();

    if (!SrcGate || !DstGate || !SrcPin || !DstPin)
        return;

    Connection* pConn = new Connection(GInfo, SrcPin, DstPin);
    pManager->AddComponent(pConn);
}

AddConnection::~AddConnection()
{
}
