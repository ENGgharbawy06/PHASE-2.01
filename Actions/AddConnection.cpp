//#include "AddConnection.h"
//#include "ApplicationManager.h"
//#include "Input.h"
//#include "Output.h"
//#include "Connection.h"
//
//ADDConnection::ADDConnection(ApplicationManager* pApp) : Action(pApp)
//{
//}
//void ADDConnection::ReadActionParameters()
//{
//	//Get a Pointer to the Input / Output Interfaces
//	Output* pOut = pManager->GetOutput();
//	Input* pIn = pManager->GetInput();
//	pOut->PrintMsg("Adding a new Connection: Click on source component");
//	//Read source component
//	int x, y;
//	pIn->GetPointClicked(x, y);
//	SrcCmpnt = pManager->GetComponentAt(x, y);
//	if (SrcCmpnt == nullptr)
//	{
//		pOut->PrintMsg("No component found at the clicked position. Action aborted.");
//		return;
//	}
//	//Assuming source pin is always output pin at index 0
//	SrcPinIndex = 0;
//	pOut->PrintMsg("Click on destination component");
//	//Read destination component
//		
//	pIn->GetPointClicked(x, y);
//	DstCmpnt = pManager->GetComponentAt(x, y);
//	if (DstCmpnt == nullptr)
//	{
//		pOut->PrintMsg("No component found at the clicked position. Action aborted.");
//		return;
//	}
//	//Assuming destination pin is always input pin at index 0
//	DstPinIndex = 0;
//	pOut->ClearStatusBar();
//}
//
//void ADDConnection::Execute()
//{
//	//Read action parameters
//	ReadActionParameters();
//	//If reading parameters was aborted
//	if (SrcCmpnt == nullptr || DstCmpnt == nullptr)
//		return;
//	//Calculate the graphics info for the connection
//	GraphicsInfo GInfo;
//	GInfo.x1 = (SrcCmpnt->GetGraphicsInfo().x1 + SrcCmpnt->GetGraphicsInfo().x2) / 2;
//	GInfo.y1 = (SrcCmpnt->GetGraphicsInfo().y1 + SrcCmpnt->GetGraphicsInfo().y2) / 2;
//	GInfo.x2 = (DstCmpnt->GetGraphicsInfo().x1 + DstCmpnt->GetGraphicsInfo().x2) / 2;
//	GInfo.y2 = (DstCmpnt->GetGraphicsInfo().y1 + DstCmpnt->GetGraphicsInfo().y2) / 2;
//	//Create a new Connection
//	Connection* pConn = new Connection(GInfo, SrcCmpnt, DstCmpnt, SrcPinIndex, DstPinIndex);
//	//Add the connection to the application manager
//	pManager->AddComponent(pConn);
//}
//ADDConnection::~ADDConnection()
//{
//}
//
//
//
//
//
//
