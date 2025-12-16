#include "CreateTruthTable.h"
#include "..\ApplicationManager.h"
#include "..\Components\Switch.h" 
#include "..\Components\LED.h"
#include "..\CMUgraphicsLib\CMUgraphics.h"
#include <string>

// Standard C++ Arrays only (No Vectors, No Algorithms)

using namespace std;

CreateTruthTable::CreateTruthTable(ApplicationManager* pApp) : Action(pApp)
{
	m_SwitchList = NULL;
	m_LEDList = NULL;
	m_NumSwitches = 0;
	m_NumLEDs = 0;
}

CreateTruthTable::~CreateTruthTable()
{
	if (m_SwitchList) delete[] m_SwitchList;
	if (m_LEDList) delete[] m_LEDList;
}

void CreateTruthTable::ReadActionParameters()
{
	// No parameters needed
}

void CreateTruthTable::Execute()
{
	Output* pOut = pManager->GetOutput();

	// ---------------------------------------------------------
	// 1. MEMORY CLEANUP
	// ---------------------------------------------------------
	if (m_SwitchList) { delete[] m_SwitchList; m_SwitchList = NULL; }
	if (m_LEDList) { delete[] m_LEDList; m_LEDList = NULL; }
	m_NumSwitches = 0;
	m_NumLEDs = 0;

	int compCount = pManager->GetCompCount();

	// ---------------------------------------------------------
	// 2. COUNT COMPONENTS (PASS 1)
	// ---------------------------------------------------------
	for (int i = 0; i < compCount; ++i)
	{
		Component* pComp = pManager->GetComponent(i);
		if (!pComp) continue;

		if (dynamic_cast<Switch*>(pComp))
			m_NumSwitches++;
		else if (dynamic_cast<LED*>(pComp))
			m_NumLEDs++;
	}

	// Safety Checks
	if (m_NumSwitches == 0)
	{
		pOut->PrintMsg("Error: No Switches found!");
		return;
	}
	if (m_NumSwitches > 5) // Limit to 5 switches (32 rows) to prevent freezing
	{
		pOut->PrintMsg("Error: Too many switches (>5). Circuit too complex for Auto-TruthTable.");
		return;
	}

	// ---------------------------------------------------------
	// 3. FILL ARRAYS (PASS 2)
	// ---------------------------------------------------------
	m_SwitchList = new Component * [m_NumSwitches];
	m_LEDList = new Component * [m_NumLEDs];

	int sIndex = 0;
	int lIndex = 0;

	for (int i = 0; i < compCount; ++i)
	{
		Component* pComp = pManager->GetComponent(i);
		if (!pComp) continue;

		if (dynamic_cast<Switch*>(pComp))
			m_SwitchList[sIndex++] = pComp;
		else if (dynamic_cast<LED*>(pComp))
			m_LEDList[lIndex++] = pComp;
	}

	// ---------------------------------------------------------
	// 4. SORT SWITCHES (Visual Order: Left to Right)
	// ---------------------------------------------------------
	// Bubble sort based on X position so S0 is the left-most switch
	for (int i = 0; i < m_NumSwitches - 1; i++)
	{
		for (int j = 0; j < m_NumSwitches - i - 1; j++)
		{
			if (m_SwitchList[j]->GetGraphicsInfo().x1 > m_SwitchList[j + 1]->GetGraphicsInfo().x1)
			{
				Component* temp = m_SwitchList[j];
				m_SwitchList[j] = m_SwitchList[j + 1];
				m_SwitchList[j + 1] = temp;
			}
		}
	}

	// ---------------------------------------------------------
	// 5. PREPARE WINDOW
	// ---------------------------------------------------------
	int rows = 1 << m_NumSwitches; // 2^N
	int cols = m_NumSwitches + m_NumLEDs;

	pOut->PrintMsg("Truth Table: " + to_string(m_NumSwitches) + " Switches -> " + to_string(rows) + " Rows generated.");

	int cellHeight = 25;
	int cellWidth = 70; // Wider columns for better readability
	int headerHeight = 30;
	int startX = 15;
	int startY = 15;

	int winWidth = (cols * cellWidth) + (2 * startX) + 20;
	int winHeight = (rows * cellHeight) + headerHeight + (2 * startY) + 20;

	window* pTTWind = new window(winWidth, winHeight, 200, 100);
	pTTWind->ChangeTitle("Truth Table");

	// Draw Headers
	pTTWind->SetPen(BLACK);
	pTTWind->SetFont(12, BOLD, BY_NAME, "Arial");

	int cx = startX;
	int cy = startY;

	// Switch Headers
	for (int i = 0; i < m_NumSwitches; i++)
	{
		string label = m_SwitchList[i]->GetLabel();
		if (label == "" || label == "$") label = "IN " + to_string(i);
		pTTWind->DrawString(cx + (i * cellWidth) + 5, cy, label);
	}

	// Red Divider Line
	pTTWind->SetPen(RED, 2);
	int divX = cx + (m_NumSwitches * cellWidth);
	pTTWind->DrawLine(divX, 0, divX, winHeight);
	pTTWind->SetPen(BLACK);

	// LED Headers
	for (int i = 0; i < m_NumLEDs; i++)
	{
		string label = m_LEDList[i]->GetLabel();
		if (label == "" || label == "$") label = "OUT " + to_string(i);
		pTTWind->DrawString(cx + ((m_NumSwitches + i) * cellWidth) + 5, cy, label);
	}

	cy += headerHeight;
	pTTWind->DrawLine(0, cy, winWidth, cy);

	// ---------------------------------------------------------
	// 6. SIMULATION LOOP (Generate All 2^N Combinations)
	// ---------------------------------------------------------

	for (int i = 0; i < rows; ++i)
	{
		// A. SET INPUTS (0 or 1)
		for (int bit = 0; bit < m_NumSwitches; ++bit)
		{
			Switch* pSwitch = (Switch*)m_SwitchList[bit];

			// Binary Logic: Get the bit at position 'bit' from integer 'i'
			int state = (i >> (m_NumSwitches - 1 - bit)) & 1;

			// Force the pin status directly
			// This overrides any "selection" logic to ensure the simulation sees the value
			pSwitch->GetOutputPin()->setStatus(state ? HIGH : LOW);

			// Draw '0' or '1'
			pTTWind->DrawInteger(cx + (bit * cellWidth) + 25, cy + (i * cellHeight) + 5, state);
		}

		// B. PROPAGATE SIGNAL (The "Heavy" Lifting)
		// We loop MANY times to ensure the signal travels through Wires -> Gates -> Wires -> LEDs
		int propagationLimit = compCount * 3;

		for (int iter = 0; iter < propagationLimit; ++iter)
		{
			for (int c = 0; c < compCount; ++c)
			{
				Component* pComp = pManager->GetComponent(c);
				if (!pComp) continue;

				// IMPORTANT: Do NOT Operate switches (we set them manually).
				// DO Operate everything else (Gates AND CONNECTIONS).
				if (dynamic_cast<Switch*>(pComp) == NULL)
				{
					pComp->Operate();
				}
			}
		}

		// C. READ OUTPUTS
		for (int l = 0; l < m_NumLEDs; ++l)
		{
			LED* pLED = (LED*)m_LEDList[l];

			int status = LOW;
			// Check if Input Pin 0 exists and read it
			if (pLED->GetInputPin(0))
				status = pLED->GetInputPin(0)->getStatus();
			else if (pLED->GetInputPin()) // Try helper if index failed
				status = pLED->GetInputPin()->getStatus();

			int val = (status == HIGH) ? 1 : 0;
			pTTWind->DrawInteger(cx + ((m_NumSwitches + l) * cellWidth) + 25, cy + (i * cellHeight) + 5, val);
		}
	}

	// ---------------------------------------------------------
	// 7. CLEANUP
	// ---------------------------------------------------------
	int x, y;
	pTTWind->WaitMouseClick(x, y); // Wait for user to close
	delete pTTWind;
}

void CreateTruthTable::Undo() {}
void CreateTruthTable::Redo() {}