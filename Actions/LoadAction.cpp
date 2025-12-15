#include "LoadAction.h"
#include "../ApplicationManager.h"
#include <fstream>

LoadAction::LoadAction(ApplicationManager* pApp) : Action(pApp) {}

void LoadAction::ReadActionParameters() {}

void LoadAction::Execute()
{
    ifstream in("circuit.txt");
    if (!in.is_open())
    {
        pManager->GetOutput()->PrintMsg("Error: Cannot open circuit.txt");
        return;
    }

    pManager->Load(in);

    pManager->GetOutput()->PrintMsg("Circuit Loaded Successfully.");
}
