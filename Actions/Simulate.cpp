#include "Simulate.h"
#include "..\ApplicationManager.h"
#include "..\GUI\Output.h"
#include <iostream>

using namespace std;

Simulate::Simulate(ApplicationManager* pApp) : Action(pApp)
{
}

Simulate::~Simulate()
{
}

void Simulate::ReadActionParameters()
{
}

void Simulate::Execute()
{
    Output* pOut = pManager->GetOutput();

    // Notify the user
    pOut->PrintMsg("Simulation Mode: Circuit Simulated.");

    // Ensure the toolbar is correct (optional, depending on your logic)
    pOut->CreateSimulationToolBar();

    // 1. Calculate the circuit outputs
    pManager->ExecuteCircuit();

    // 2. Update the visual interface (turn on/off LEDs)
    pManager->UpdateInterface();
}

void Simulate::Undo()
{
}

void Simulate::Redo()
{
}