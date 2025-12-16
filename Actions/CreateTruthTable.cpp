#include "CreateTruthTable.h"
#include "..\ApplicationManager.h"
#include "..\Components\Switch.h"
#include "..\Components\LED.h"
#include "..\Components\Connection.h"
#include "..\CMUgraphicsLib\CMUgraphics.h"
#include <iomanip>
#include <iostream>

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
	// No parameters needed from the user
}

void CreateTruthTable::Execute()
{
	Output* pOut = pManager->GetOutput();

	// ---------------------------------------------------------
	// 1. INITIALIZATION & COMPONENT COUNTING
	// ---------------------------------------------------------

	// Clean up old lists if they exist
	if (m_SwitchList) { delete[] m_SwitchList; m_SwitchList = NULL; }
	if (m_LEDList) { delete[] m_LEDList; m_LEDList = NULL; }
	m_NumSwitches = 0;
	m_NumLEDs = 0;

	int compCount = pManager->GetCompCount();

	// Pass 1: Count Switches and LEDs
	for (int i = 0; i < compCount; ++i)
	{
		Component* pComp = pManager->GetComponent(i);
		if (!pComp) continue;

		if (dynamic_cast<Switch*>(pComp))
			m_NumSwitches++;
		else if (dynamic_cast<LED*>(pComp))
			m_NumLEDs++;
	}

	if (m_NumSwitches == 0)
	{
		pOut->PrintMsg("Error: No Switches found to generate Truth Table.");
		return;
	}
	if (m_NumSwitches > 5) // Restriction to prevent freezing (2^5 = 32 rows)
	{
		pOut->PrintMsg("Error: Too many switches (>5). Logic too complex for auto-table.");
		return;
	}

	// ---------------------------------------------------------
	// 2. FILL COMPONENT LISTS
	// ---------------------------------------------------------
	m_SwitchList = new Component * [m_NumSwitches];
	m_LEDList = new Component * [m_NumLEDs];

	int sIdx = 0, lIdx = 0;
	for (int i = 0; i < compCount; ++i)
	{
		Component* pComp = pManager->GetComponent(i);
		if (!pComp) continue;

		if (dynamic_cast<Switch*>(pComp))
			m_SwitchList[sIdx++] = pComp;
		else if (dynamic_cast<LED*>(pComp))
			m_LEDList[lIdx++] = pComp;
	}

	// ---------------------------------------------------------
	// 3. SORT SWITCHES (Visual Order: Left -> Right)
	// ---------------------------------------------------------
	// This ensures the columns match the visual layout of switches
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
	// 4. SETUP TRUTH TABLE WINDOW
	// ---------------------------------------------------------
	// Calculate Dimensions
	int numRows = 1 << m_NumSwitches; // 2^N
	int numCols = m_NumSwitches + m_NumLEDs;

	int colWidth = 50;
	int rowHeight = 25;
	int headerHeight = 30;

	int winWidth = (numCols * colWidth) + 20;
	int winHeight = (numRows * rowHeight) + headerHeight + 20;

	if (winWidth < 200) winWidth = 200; // Minimum size

	window* pTTWind = new window(winWidth, winHeight, 200, 100);
	pTTWind->ChangeTitle("Truth Table");

	// Draw Headers
	int currentX = 10;
	int currentY = 5;

	pTTWind->SetPen(BLACK, 2);
	pTTWind->SetFont(20, BOLD, BY_NAME, "Arial");

	// Draw Switch Headers (S0, S1...)
	for (int i = 0; i < m_NumSwitches; ++i)
	{
		string label = "S" + to_string(i);
		// If component has a specific label, you could use that:
		// if (m_SwitchList[i]->GetLabel() != "") label = m_SwitchList[i]->GetLabel();
		pTTWind->DrawString(currentX, currentY, label);
		currentX += colWidth;
	}

	// Draw Separator
	pTTWind->DrawLine(currentX - 10, 0, currentX - 10, winHeight);

	// Draw LED Headers (L0, L1...)
	for (int i = 0; i < m_NumLEDs; ++i)
	{
		string label = "L" + to_string(i);
		pTTWind->DrawString(currentX, currentY, label);
		currentX += colWidth;
	}

	pTTWind->DrawLine(0, headerHeight, winWidth, headerHeight);

	// ---------------------------------------------------------
	// 5. GENERATE ROWS & SIMULATE (CRITICAL STEP)
	// ---------------------------------------------------------
	currentY = headerHeight + 5;

	for (int i = 0; i < numRows; ++i)
	{
		currentX = 10;

		// A. SET INPUTS
		// Extract bits from 'i' to set switches (00, 01, 10, 11...)
		for (int j = 0; j < m_NumSwitches; ++j)
		{
			// Get bit at position (NumSwitches - 1 - j)
			int bit = (i >> (m_NumSwitches - 1 - j)) & 1;

			Switch* pSwitch = (Switch*)m_SwitchList[j];

			// Force the status directly on the output pin
			// We skip calling pSwitch->Operate() later because we set the value manually here
			pSwitch->GetOutputPin()->setStatus(bit ? HIGH : LOW);

			// Draw Input Value (0 or 1)
			pTTWind->DrawString(currentX, currentY, to_string(bit));
			currentX += colWidth;
		}

		// B. PROPAGATE SIGNALS (SIMULATION)
		// We must run the circuit logic MULTIPLE TIMES to ensure signals flow 
		// from Switches -> Gates -> Connections -> Gates -> LEDs

		int maxPropagations = compCount * 2; // Heuristic safety margin
		for (int iter = 0; iter < maxPropagations; ++iter)
		{
			for (int k = 0; k < compCount; ++k)
			{
				Component* pComp = pManager->GetComponent(k);
				if (!pComp) continue;

				// Simulate everything EXCEPT Switches (we set them manually above)
				if (dynamic_cast<Switch*>(pComp) == NULL)
				{
					pComp->Operate();
				}
			}
		}

		// C. READ OUTPUTS
		for (int k = 0; k < m_NumLEDs; ++k)
		{
			LED* pLED = (LED*)m_LEDList[k];

			int status = LOW;
			// LEDs usually have 1 InputPin at index 0
			if (pLED->GetInputPin(0))
				status = pLED->GetInputPin(0)->getStatus();

			// Draw Output Value (0 or 1)
			pTTWind->DrawString(currentX, currentY, to_string(status == HIGH ? 1 : 0));
			currentX += colWidth;
		}

		currentY += rowHeight;
	}

	// Wait for click to close
	pTTWind->WaitMouseClick(currentX, currentY);
	delete pTTWind;
}

void CreateTruthTable::Undo()
{
}

void CreateTruthTable::Redo()
{
}