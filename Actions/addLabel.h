#ifndef _ADD_LABEL_H
#define _ADD_LABEL_H

#include "Action.h"
#include "Label.h"

class AddLabel : public Action
{
public:
    AddLabel(ApplicationManager* pApp);

    virtual void ReadActionParameters() override;
    virtual void Execute() override;
    
	virtual void Undo() override {}
	virtual void Redo() override {}
    

};

#endif
