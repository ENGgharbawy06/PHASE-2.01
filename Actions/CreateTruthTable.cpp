//#include "CreateTruthTable.h"
//#include "..\ApplicationManager.h"
//#include "..\Components\Switch.h" 
//#include "..\Components\LED.h"
//#include <string>
//
//CreateTruthTable::CreateTruthTable(ApplicationManager* pApp) : Action(pApp)
//{
//	m_SwitchList = NULL;
//	m_LEDList = NULL;
//	m_NumSwitches = 0;
//	m_NumLEDs = 0;
//}
//
//CreateTruthTable::~CreateTruthTable()
//{
//	// Clean up memory if the action is destroyed
//	if (m_SwitchList) delete[] m_SwitchList;
//	if (m_LEDList) delete[] m_LEDList;
//}
//
//void CreateTruthTable::ReadActionParameters()
//{
//	// No parameters needed from the user
//}
//
//void CreateTruthTable::Execute()
//{
//	Output* pOut = pManager->GetOutput();
//
//	// ---------------------------------------------------------
//	// 1. Identify and Count Switches and LEDs (Two-Pass Logic)
//	// ---------------------------------------------------------
//
//	// Reset counts
//	m_NumSwitches = 0;
//	m_NumLEDs = 0;
//
//	// Ensure we don't leak memory if Execute is called twice
//	if (m_SwitchList) { delete[] m_SwitchList; m_SwitchList = NULL; }
//	if (m_LEDList) { delete[] m_LEDList; m_LEDList = NULL; }
//
//	int compCount = pManager->GetCompCount();
//
//	// -- PASS 1: Count how many Switches and LEDs exist --
//	for (int i = 0; i < compCount; ++i)
//	{
//		Component* pComp = pManager->GetComponent(i);
//
//		if (dynamic_cast<Switch*>(pComp))
//			m_NumSwitches++;
//		else if (dynamic_cast<LED*>(pComp))
//			m_NumLEDs++;
//	}
//
//	// Validation: Do we have valid inputs?
//	if (m_NumSwitches == 0)
//	{
//		pOut->PrintMsg("Error: No Switches found! Cannot create Truth Table.");
//		return;
//	}
//	if (m_NumSwitches > 5)
//	{
//		pOut->PrintMsg("Error: Too many switches (>5). Table would be too large.");
//		return;
//	}
//
//	// -- PASS 2: Allocate exact memory and Fill the arrays --
//
//	// Dynamic Allocation
//	m_SwitchList = new Component * [m_NumSwitches];
//	m_LEDList = new Component * [m_NumLEDs];
//
//	int sIndex = 0;
//	int lIndex = 0;
//
//	for (int i = 0; i < compCount; ++i)
//	{
//		Component* pComp = pManager->GetComponent(i);
//
//		if (dynamic_cast<Switch*>(pComp))
//			m_SwitchList[sIndex++] = pComp;
//		else if (dynamic_cast<LED*>(pComp))
//			m_LEDList[lIndex++] = pComp;
//	}
//
//	pOut->PrintMsg("Generating Truth Table... Click inside the table to close it.");
//
//	// ---------------------------------------------------------
//	// 2. Setup the Truth Table Window
//	// ---------------------------------------------------------
//
//	// Calculate 2^N using bitwise shift (No cmath needed)
//	int rows = 1 << m_NumSwitches;
//
//	int cols = m_NumSwitches + m_NumLEDs;
//	int cellHeight = 25;
//	int cellWidth = 50;
//	int headerHeight = 30;
//	int startX = 20;
//	int startY = 10;
//
//	int winWidth = (cols * cellWidth) + (2 * startX);
//	int winHeight = (rows * cellHeight) + headerHeight + (2 * startY);
//
//	window* pTTWind = new window(winWidth, winHeight, 200, 200);
//	pTTWind->ChangeTitle("Truth Table");
//
//	// Draw Headers
//	pTTWind->SetPen(BLACK);
//	pTTWind->SetFont(14, BOLD, BY_NAME, "Arial");
//
//	int cx = startX;
//	int cy = startY;
//
//	// Draw Switch Labels (S0, S1...)
//	for (int i = 0; i < m_NumSwitches; i++)
//	{
//		string label = "S" + to_string(i);
//		pTTWind->DrawString(cx + (i * cellWidth), cy, label);
//	}
//	// Draw LED Labels (L0, L1...)
//	for (int i = 0; i < m_NumLEDs; i++)
//	{
//		string label = "L" + to_string(i);
//		pTTWind->DrawString(cx + ((m_NumSwitches + i) * cellWidth), cy, label);
//	}
//
//	cy += headerHeight;
//	pTTWind->SetPen(RED, 2);
//	pTTWind->DrawLine(0, cy, winWidth, cy); // Separator line
//	pTTWind->SetPen(BLACK);
//
//	// ---------------------------------------------------------
//	// 3. Simulation Loop
//	// ---------------------------------------------------------
//
//	for (int i = 0; i < rows; ++i)
//	{
//		// A. Set Switches based on binary bits of 'i'
//		for (int bit = 0; bit < m_NumSwitches; ++bit)
//		{
//			Switch* pSwitch = (Switch*)m_SwitchList[bit];
//
//			// Extract bit value (0 or 1)
//			// (m_NumSwitches - 1 - bit) ensures S0 is MSB (Leftmost)
//			int state = (i >> (m_NumSwitches - 1 - bit)) & 1;
//
//			pSwitch->SetStatus(state ? HIGH : LOW);
//
//			// Draw Input Value to Table
//			pTTWind->DrawInteger(cx + (bit * cellWidth) + 10, cy + (i * cellHeight), state);
//		}
//
//		// B. Propagate Signals (Simulate)
//		// Run multiple passes to allow signals to propagate through all gates
//		for (int iter = 0; iter < compCount * 2; ++iter)
//		{
//			for (int c = 0; c < compCount; ++c)
//			{
//				pManager->GetComponent(c)->Operate();
//			}
//		}
//
//		// C. Read LEDs and Draw Output
//		for (int l = 0; l < m_NumLEDs; ++l)
//		{
//			LED* pLED = (LED*)m_LEDList[l];
//
//			// Assuming GetInputPinStatus(0) returns the state of the LED's input
//			int status = pLED->GetInputPinStatus(0);
//
//			int val = (status == HIGH) ? 1 : 0;
//			pTTWind->DrawInteger(cx + ((m_NumSwitches + l) * cellWidth) + 10, cy + (i * cellHeight), val);
//		}
//	}
//
//	// ---------------------------------------------------------
//	// 4. Cleanup
//	// ---------------------------------------------------------
//
//	// Wait for user to click to close window
//	int x, y;
//	pTTWind->WaitMouseClick(x, y);
//
//	delete pTTWind;
//
//	// Free the dynamic arrays
//	delete[] m_SwitchList;
//	delete[] m_LEDList;
//	m_SwitchList = NULL;
//	m_LEDList = NULL;
//}
//
//void CreateTruthTable::Undo() {}
//void CreateTruthTable::Redo() {}