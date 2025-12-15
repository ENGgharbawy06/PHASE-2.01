#ifndef _ADD_LABEL_H
#define _ADD_LABEL_H

#include "Action.h"
#include "..\Components\Label.h"

class AddLabel : public Action
{
private:
    GraphicsInfo labelGfx;
    std::string labelText;
	Label* pLabel;



public:
    AddLabel(ApplicationManager* pApp);

    virtual void ReadActionParameters() override;
    virtual void Execute() override;
    
    virtual void Undo() override;
    virtual void Redo() override;
    virtual bool isUndoable() const override { return true; };
	virtual ~AddLabel();
    

};

#endif
