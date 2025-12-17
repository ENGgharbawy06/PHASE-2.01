#include "Delete.h"
#include "../ApplicationManager.h"
#include "../GUI/Input.h"
#include "../GUI/Output.h"
#include "../Components/Connection.h"

Delete::Delete(ApplicationManager* pApp)
    : Action(pApp)
{
    DeletedCount = 0;
}

void Delete::ReadActionParameters()
{
    Output* pOut = pManager->GetOutput();
    Input* pIn = pManager->GetInput();

	pOut->PrintMsg("Delete Mode: Select components, press ENTER, then click the Delete icon ..."); // ba2ol lel user rzay ye delete el components

    // clear old selection
    pManager->UnselectAll();

    int x, y;

    while (true)
    {
        pIn->GetPointClicked(x, y);

        // ENTER key = x = y = -1 from modified GetPointClicked
        if (x == -1 && y == -1)
            break;

        Component* c = pManager->GetComponentAt(x, y);
        if (c)
        {
            c->SetSelected(!c->IsSelected());
            pManager->UpdateInterface();
        }
    }

    pOut->ClearStatusBar();
}

void Delete::Execute()
{
    ReadActionParameters();

    DeletedCount = 0;

    int count = pManager->GetCompCount();

    for (int i = 0; i < count; i++)
    {
        Component* c = pManager->GetComponent(i);

        if (c && c->IsSelected())
        {
            if (c->IsConnection())
            {
                Connection* pConn = (Connection*)c;
                pConn->Disconnect();
            }

            DeletedArray[DeletedCount++] = c;  // save for undo

            pManager->BreakConnections(c);

            pManager->DeleteComponent(c);

            i--;      // because array shifted left
            count--;
        }
    }

    pManager->UpdateInterface();
}

void Delete::Undo()
{
    for (int i = 0; i < DeletedCount; i++)
    {
        pManager->AddComponent(DeletedArray[i]);
    }

    pManager->UpdateInterface();
}

void Delete::Redo()
{
    for (int i = 0; i < DeletedCount; i++)
    {
        pManager->DeleteComponent(DeletedArray[i]);
    }

    pManager->UpdateInterface();
}
