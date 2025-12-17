#include "EditLabel.h"
#include "..\ApplicationManager.h"
#include "..\GUI\Input.h"
#include "..\GUI\Output.h"
#include "..\Components\Label.h"

EditLabel::EditLabel(ApplicationManager* pApp) : Action(pApp)
{
	pComp = nullptr;
}

EditLabel::~EditLabel()
{
}

void EditLabel::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMsg("Edit Label: Click on the component you want to edit.");

	
	pIn->GetPointClicked(x, y);
	pComp = pManager->GetComponentAt(x, y);

	if (pComp == nullptr)
	{
		pOut->PrintMsg("Error: No component selected!");
		return;
	}

	// atakd من إن في Label أصلاً عشان نعدله
	oldLabel = pComp->GetLabel();
	if (oldLabel == "")
	{
		pOut->PrintMsg("Error: This component has no label to edit! Use 'Add Label' instead.");
		pComp = nullptr; 
		return;
	}

	// طلب الاسم الجديد
	pOut->PrintMsg("Current Label: " + oldLabel + " | Enter new label:");
	newLabel = pIn->GetString(pOut);

	if (newLabel.empty())
	{
		pOut->PrintMsg("Edit Cancelled.");
		pComp = nullptr;
		return;
	}

	pOut->ClearStatusBar();
}

void EditLabel::Execute()
{
	ReadActionParameters();

	
	if (pComp == nullptr) return;

	// تحديث الاسم في المكون نفسه
	pComp->SetLabel(newLabel);

	
	int count = pManager->GetCompCount();
	for (int i = 0; i < count; i++)
	{
		Component* c = pManager->GetComponent(i);

		
		if (c->IsLabel() && c->GetLabel() == oldLabel)
		{
			c->SetLabel(newLabel); 
			break; 
		}
	}

	
	pManager->GetOutput()->PrintMsg("Label updated successfully.");
	pManager->UpdateInterface();
}

void EditLabel::Undo()
{
	
}

void EditLabel::Redo()
{
	
}