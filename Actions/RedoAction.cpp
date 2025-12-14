#include "RedoAction.h"
#include "..\ApplicationManager.h"

void RedoAction::Execute()
{
	pManager->ExecuteRedo();
}