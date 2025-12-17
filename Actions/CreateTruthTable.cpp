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
}

void CreateTruthTable::Execute()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput(); // Need Input to wait for click



	if (m_SwitchList) { delete[] m_SwitchList; m_SwitchList = NULL; }
	if (m_LEDList) { delete[] m_LEDList; m_LEDList = NULL; }
	m_NumSwitches = 0;
	m_NumLEDs = 0;

	int compCount = pManager->GetCompCount();

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
	// Restrict to 4 or 5 switches max to fit on screen
	if (m_NumSwitches > 5) 
	{
		pOut->PrintMsg("Error: Too many switches (>5). Logic too complex for auto-table.");
		return;
	}

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

	// Sort Switches (Left -> Right)
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


	// Clear the circuit to make room for the table
	pOut->ClearDrawingArea();
	pOut->PrintMsg("Truth Table generated. Click anywhere to return to circuit.");

	int startX = 20;
	int startY = 100; // Start below the toolbar
	int colWidth = 30; 
	int rowHeight = 25;
	
	int currentX = startX;
	int currentY = startY;

	// Draw Headers (el switches wel leds)
	for (int i = 0; i < m_NumSwitches; ++i)
	{
		pOut->DrawString(currentX, currentY, "S" + to_string(i));
		currentX += colWidth;
	}
	currentX += 10; // SPACING
	for (int i = 0; i < m_NumLEDs; ++i)
	{
		pOut->DrawString(currentX, currentY, "L" + to_string(i));
		currentX += colWidth;
	}

	currentY += rowHeight;


	
	// Save original states
	int* originalStates = new int[m_NumSwitches];
	for (int i = 0; i < m_NumSwitches; ++i)
	{
		Switch* pSwitch = (Switch*)m_SwitchList[i];
		originalStates[i] = pSwitch->GetOutputPin()->getStatus();
	}

	int numRows = 1 << m_NumSwitches;

	for (int i = 0; i < numRows; ++i)
	{
		// Reset X for new row
		currentX = startX;

		// A. SET INPUTS
		for (int j = 0; j < m_NumSwitches; ++j)
		{
			int bit = (i >> (m_NumSwitches - 1 - j)) & 1;
			Switch* pSwitch = (Switch*)m_SwitchList[j];
			pSwitch->GetOutputPin()->setStatus(bit ? HIGH : LOW);

			pOut->DrawString(currentX, currentY, to_string(bit));
			currentX += colWidth;
		}

		// B. PROPAGATE SIGNALS
		int maxPropagations = compCount * 2; 
		for (int iter = 0; iter < maxPropagations; ++iter)
		{
			for (int k = 0; k < compCount; ++k)
			{
				Component* pComp = pManager->GetComponent(k);
				if (pComp && !dynamic_cast<Switch*>(pComp))
					pComp->Operate();
			}
		}

		// C. READ OUTPUTS
		currentX += 10; // Jump the gap
		for (int k = 0; k < m_NumLEDs; ++k)
		{
			LED* pLED = (LED*)m_LEDList[k];
			int status = LOW;
			if (pLED->GetInputPin(0))
				status = pLED->GetInputPin(0)->getStatus();

			pOut->DrawString(currentX, currentY, to_string(status == HIGH ? 1 : 0));
			currentX += colWidth;
		}

		currentY += rowHeight;
	}


	
	// Wait for user to click ANYWHERE to finish
	int x, y;
	pIn->GetPointClicked(x, y);

	// Restore original switch states
	for (int i = 0; i < m_NumSwitches; ++i)
	{
		Switch* pSwitch = (Switch*)m_SwitchList[i];
		pSwitch->GetOutputPin()->setStatus((STATUS)originalStates[i]);
	}
	delete[] originalStates;

	// Run circuit one last time to restore LED states
	for (int iter = 0; iter < compCount * 2; ++iter)
	{
		for (int k = 0; k < compCount; ++k)
		{
			Component* pComp = pManager->GetComponent(k);
			if (pComp && !dynamic_cast<Switch*>(pComp))
				pComp->Operate();
		}
	}

	pOut->PrintMsg("Truth Table finished. Circuit restored.");
}

void CreateTruthTable::Undo()
{
}

void CreateTruthTable::Redo()
{
}