#ifndef _EDIT_LABEL_H
#define _EDIT_LABEL_H

#include "Action.h"
#include "..\Components\Component.h"
#include <string>
using namespace std;

class EditLabel : public Action
{
private:
	
	Component* pComp;      // المكون الذي سنعدل اسمه
	string oldLabel;       // الاسم القديم
	string newLabel;       // الاسم الجديد

	int x, y;

public:
	EditLabel(ApplicationManager* pApp);
	virtual ~EditLabel();

	virtual void ReadActionParameters();
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();
};

#endif