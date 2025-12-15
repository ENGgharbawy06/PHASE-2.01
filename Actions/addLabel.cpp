//#include "addLabel.h"
//#include "..\ApplicationManager.h"
//#include "..\GUI\Input.h"
//#include "..\GUI\Output.h"
//
//AddLabel::AddLabel(ApplicationManager* pApp) : Action(pApp) {}
//
//void AddLabel::ReadActionParameters()
//{
//    // Nothing here (handled in Execute)
//}
//
//void AddLabel::Execute()
//{
//    Output* pOut = pManager->GetOutput();
//    Input* pIn = pManager->GetInput();
//
//    int x, y;
//    pOut->PrintMsg("Click where you want to place the label");
//    pIn->GetPointClicked(x, y);
//
//    pOut->PrintMsg("Enter label text");
//    std::string txt = pIn->GetString(pOut);
//
//    GraphicsInfo GInfo;
//    GInfo.x1 = x;
//    GInfo.y1 = y;
//
//    Label* pLabel = new Label(GInfo, txt);
//    pManager->AddComponent(pLabel);
//
//    pOut->ClearStatusBar();
//}
