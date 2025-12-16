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

	// 1. تحديد المكون
	pIn->GetPointClicked(x, y);
	pComp = pManager->GetComponentAt(x, y);

	if (pComp == nullptr)
	{
		pOut->PrintMsg("Error: No component selected!");
		return;
	}

	// 2. التأكد أن المكون يمتلك اسماً أصلاً
	oldLabel = pComp->GetLabel();
	if (oldLabel == "")
	{
		pOut->PrintMsg("Error: This component has no label to edit! Use 'Add Label' instead.");
		pComp = nullptr; // إلغاء العملية
		return;
	}

	// 3. طلب الاسم الجديد
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

	// لو مفيش مكون تم اختياره أو العملية اتلغت
	if (pComp == nullptr) return;

	// 1. تحديث الاسم المخزن داخل المكون الأصلي (البوابة نفسها)
	// عشان لما نيجي نعمل Edit تاني، أو نعمل Save، يبقى الاسم الجديد موجود
	pComp->SetLabel(newLabel);

	// 2. تحديث الشكل المرئي (الكائن Label اللي طاير فوق البوابة)
	int count = pManager->GetCompCount();
	for (int i = 0; i < count; i++)
	{
		Component* c = pManager->GetComponent(i);

		// شرط البحث:
		// 1. هل المكون ده Label؟ (باستخدام الدالة اللي ضفناها IsLabel)
		// 2. هل النص اللي جواه هو نفس النص القديم اللي بنعدله؟
		if (c->IsLabel() && c->GetLabel() == oldLabel)
		{
			c->SetLabel(newLabel); // دلوقتي دي هتسمع في الـ Draw علطول لأننا لغينا m_Text
			break; // لقيناه وعدلناه، نخرج من اللوب
		}
	}

	// 3. رسالة تأكيد وتحديث الشاشة (مهم جداً عشان التغيير يظهر)
	pManager->GetOutput()->PrintMsg("Label updated successfully.");
	pManager->UpdateInterface();
}

void EditLabel::Undo()
{
	//if (pComp == nullptr) return;

	//// 1. إرجاع الاسم القديم في المكون
	//pComp->SetLabel(oldLabel);

	//// 2. إرجاع الاسم القديم في الـ Label المرئي
	//int count = pManager->GetCompCount();
	//for (int i = 0; i < count; i++)
	//{
	//	Component* c = pManager->GetComponent(i);
	//	if (dynamic_cast<Label*>(c) && c->GetLabel() == newLabel)
	//	{
	//		c->SetLabel(oldLabel);
	//		break;
	//	}
	//}

	// for orashy Undo
}

void EditLabel::Redo()
{
	//if (pComp == nullptr) return;

	//// 1. إرجاع الاسم الجديد في المكون
	//pComp->SetLabel(newLabel);

	//// 2. إرجاع الاسم الجديد في الـ Label المرئي
	//int count = pManager->GetCompCount();
	//for (int i = 0; i < count; i++)
	//{
	//	Component* c = pManager->GetComponent(i);
	//	if (dynamic_cast<Label*>(c) && c->GetLabel() == oldLabel)
	//	{
	//		c->SetLabel(newLabel);
	//		break;
	//	}
	//}

	// for orashy Redo
}