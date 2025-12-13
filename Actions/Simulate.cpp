#include "Simulate.h"
#include "..\ApplicationManager.h"
#include "..\GUI\Output.h"
#include <iostream>

using namespace std;

// --- تصحيح الـ Constructor ---
// لازم نستدعي Action(pApp) في قائمة التهيئة
Simulate::Simulate(ApplicationManager* pApp) : Action(pApp)
{
    // Initialize simulation parameters
    cout << "Initializing Simulation Parameters" << endl;

    // pManager = pApp; // السطر ده ملوش لازمة لأن Action(pApp) عملته خلاص

    timeStep = 0.1;
    totalTime = 10.0;
    currentTime = 0.0;

    cout << "Simulation Initialized with time step: " << timeStep << " and total time: " << totalTime << endl;
}

Simulate::~Simulate() {
}

// --- دوال المحاكاة (زي ما إنت كاتبها) ---
void Simulate::initialize() {
    cout << " Initializing Simulation" << endl;
}

void Simulate::update() {
    currentTime += timeStep;
}

void Simulate::run() {
    initialize();
    while (currentTime < totalTime) {
        update();
    }
    finalize();
}

void Simulate::finalize() {
    cout << "Simulation Complete at t=   " << currentTime << endl;
}

void Simulate::ReadActionParameters()
{
   
}

void Simulate::Execute()
{
    Output* pOut = pManager->GetOutput();

    // 2. طباعة الرسالة
    pOut->PrintMsg("Simulation Mode: Click switches to toggle, or click Truth Table.");

    pOut->CreateSimulationToolBar();

    // 4. (خطوة مهمة جداً ناقصة) حساب قيم الدائرة عشان اللمبات تنور
    //pManager->ExecuteCircuit();

    // 5. تحديث الواجهة (اختياري لو ExecuteCircuit بتعملها)
    // pManager->UpdateInterface(); 
}

void Simulate::Undo()
{
}

void Simulate::Redo()
{
}