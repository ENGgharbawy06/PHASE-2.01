#ifndef _ACTION_H
#define _ACTION_H

class ApplicationManager; 


class Action
{
protected:
	ApplicationManager *pManager;	//Actions needs AppMngr to do their job
public:
	Action(ApplicationManager *pApp) { pManager = pApp; }	//constructor
	
	//Reads parameters required for action to execute
	virtual void ReadActionParameters()=0;
	
	//Execute action (code depends on action type)

	virtual bool isUndoable() const { return true; } //El default true w law el action kan save aw load fa hayeb2a false

	virtual void Execute()=0;

	//To undo this action (code depends on action type)
	virtual void Undo()=0;

	//To redo this action (code depends on action type)
	virtual void Redo()=0;

};

#endif