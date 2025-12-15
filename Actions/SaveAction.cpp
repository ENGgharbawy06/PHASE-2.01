#include "SaveAction.h"
#include "../ApplicationManager.h"
#include <fstream>

SaveAction::SaveAction(ApplicationManager* pApp) : Action(pApp) {}

void SaveAction::ReadActionParameters() {}

void SaveAction::Execute()
{
    ofstream out("circuit.txt");
    if (!out.is_open())
    {
        pManager->GetOutput()->PrintMsg("Error: Cannot open circuit.txt");
        return;
    }

    pManager->Save(out);

    pManager->GetOutput()->PrintMsg("Circuit Saved Successfully.");
}
