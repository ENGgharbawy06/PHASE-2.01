#include "Move.h"
#include "..\ApplicationManager.h"
#include "..\Components\Connection.h"
#include "..\Components\InputPin.h" 
#include "..\Components\OutputPin.h" 
#include "..\Components\Gate.h"

Move::Move(ApplicationManager* pApp) :Action(pApp)
{
}

void Move::ReadActionParameters()
{
}


bool CheckConnectionIntersection(GraphicsInfo rect, Connection* pConn)
{
	GraphicsInfo connGfx = pConn->GetGraphicsInfo();
	int midx = (connGfx.x1 + connGfx.x2) / 2;

	// 3 segments of the connection
	// 1. Horizontal: Source -> Mid
	// 2. Vertical: Mid(y1) -> Mid(y2)
	// 3. Horizontal: Mid -> Dest

	//  1 (Horizontal)
	int seg1_x_min = (connGfx.x1 < midx) ? connGfx.x1 : midx;
	int seg1_x_max = (connGfx.x1 > midx) ? connGfx.x1 : midx;
	if (connGfx.y1 >= rect.y1 && connGfx.y1 <= rect.y2) // Y overlap
		if (seg1_x_min <= rect.x2 && seg1_x_max >= rect.x1) // X overlap
			return true;

	//  2 (Vertical)
	int seg2_y_min = (connGfx.y1 < connGfx.y2) ? connGfx.y1 : connGfx.y2;
	int seg2_y_max = (connGfx.y1 > connGfx.y2) ? connGfx.y1 : connGfx.y2;
	if (midx >= rect.x1 && midx <= rect.x2) // X overlap
		if (seg2_y_min <= rect.y2 && seg2_y_max >= rect.y1) // Y overlap
			return true;

	//  3 (Horizontal)
	int seg3_x_min = (midx < connGfx.x2) ? midx : connGfx.x2;
	int seg3_x_max = (midx > connGfx.x2) ? midx : connGfx.x2;
	if (connGfx.y2 >= rect.y1 && connGfx.y2 <= rect.y2) // Y overlap
		if (seg3_x_min <= rect.x2 && seg3_x_max >= rect.x1) // X overlap
			return true;

	return false;
}

void Move::Execute()
{
    Output* pOut = pManager->GetOutput();
    Input* pIn = pManager->GetInput();

    // 1. Check how many items are selected
    int count = pManager->GetSelectedCount();

    if (count == 0)
    {
        pOut->PrintMsg("Error: No components selected. Please select component(s) first.");
        return;
    }

    int dx = 0, dy = 0;
    Component* pComp = nullptr; // Pointer to the single selected component (if count == 1)

    
    // Handle Case 1: Single Component
    if (count == 1)
    {
        pComp = pManager->GetOneSelectedComponent();

        if (dynamic_cast<Connection*>(pComp) == NULL)
        {
            pOut->PrintMsg("Move Component: Click on the new destination.");
            int destX, destY;
            pOut->GetValidDrawingPoint(destX, destY, pIn);

            GraphicsInfo GInfo = pComp->GetGraphicsInfo();
            int centerX = (GInfo.x1 + GInfo.x2) / 2;
            int centerY = (GInfo.y1 + GInfo.y2) / 2;

            dx = destX - centerX;
            dy = destY - centerY;
        }
        else
        {
         
            pOut->PrintMsg("Move Connection: Click Reference Point, then Destination.");
            int x1, y1, x2, y2;
            pOut->GetValidDrawingPoint(x1, y1, pIn);
            pOut->PrintMsg("Click Destination...");
            pOut->GetValidDrawingPoint(x2, y2, pIn);
            dx = x2 - x1;
            dy = y2 - y1;
        }
    }
    // Handle Case 2: Multiple Components
    else
    {
        pOut->PrintMsg("Move Selected: Click on a Reference Point (Start).");
        int x1, y1;
        pOut->GetValidDrawingPoint(x1, y1, pIn);
        pOut->PrintMsg("Click on the Destination Point (End).");
        int x2, y2;
        pOut->GetValidDrawingPoint(x2, y2, pIn);
        dx = x2 - x1;
        dy = y2 - y1;
    }

   

   
    for (int i = 0; i < pManager->GetCompCount(); i++)
    {
        Component* c = pManager->GetComponent(i);
        if (c->IsSelected())
        {
            
            GraphicsInfo GInfo = c->GetGraphicsInfo();
            int newX1 = GInfo.x1 + dx;
            int newY1 = GInfo.y1 + dy;
            int newX2 = GInfo.x2 + dx;
            int newY2 = GInfo.y2 + dy;
            int newWidth = newX2 - newX1;
            int newHeight = newY2 - newY1;

            // 1. BOUNDARY CHECKS
            if (newY1 < UI.ToolBarHeight || newY2 >(UI.height - UI.StatusBarHeight))
            {
                pOut->PrintMsg("Error: Cannot move into the Toolbar or Status Bar.");
                return; // Stop execution
            }

            
            if (dynamic_cast<Connection*>(c))
                continue;

            // 2. COMPONENT COLLISION CHECK 
            if (pManager->CheckCollision(newX1, newY1, newWidth, newHeight, c))
            {
                pOut->PrintMsg("Error: Move causes overlap with another component.");
                return;
            }

            // 3. CONNECTION COLLISION CHECK 
            for (int j = 0; j < pManager->GetCompCount(); j++)
            {
                Component* other = pManager->GetComponent(j);
                Connection* conn = dynamic_cast<Connection*>(other);
                if (conn && !conn->IsSelected()) // Only check non-moving connections
                {
                    GraphicsInfo newRect = { newX1, newY1, newX2, newY2 };
                    if (CheckConnectionIntersection(newRect, conn))
                    {
                        pOut->PrintMsg("Error: Cannot place component over a connection.");
                        return;
                    }
                }
            }

            // 4. LOGICAL CONSTRAINT (Left < Right)
            if (count == 1 && !dynamic_cast<Connection*>(c))
            {
                
                for (int inp = 0; inp < 3; inp++)
                {
                    InputPin* pIn = c->GetInputPin(inp);
                    if (pIn && pIn->getIsConnected())
                    {
                        Connection* conn = pIn->getConnection();
                        if (conn)
                        {
                            Component* srcComp = conn->getSourcePin()->getComponent();
                           
                            if (!srcComp->IsSelected())
                            {
                                if (srcComp->GetGraphicsInfo().x1 >= newX1)
                                {
                                    pOut->PrintMsg("Error: Invalid Position. Source component (Left) cannot be to the right of destination.");
                                    return;
                                }
                            }
                        }
                    }
                }

              
                OutputPin* pOutPin = c->GetOutputPin();
                if (pOutPin)
                {
                    
                    for (int k = 0; k < pManager->GetCompCount(); k++)
                    {
                        Connection* conn = dynamic_cast<Connection*>(pManager->GetComponent(k));
                        if (conn && conn->getSourcePin() == pOutPin)
                        {
                            Component* dstComp = conn->getDestPin()->getComponent();
                          
                            if (!dstComp->IsSelected())
                            {
                                if (newX1 >= dstComp->GetGraphicsInfo().x1)
                                {
                                    pOut->PrintMsg("Error: Invalid Position. Destination component (Right) cannot be to the left of source.");
                                    return;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

   
    pManager->MoveSelected(dx, dy);
    pOut->PrintMsg("Move completed.");
    diffx = dx;
    diffy = dy;
}

void Move::Undo()
{
	pManager->MoveSelected(-diffx, -diffy);

}

void Move::Redo()
{
	pManager->MoveSelected(diffx, diffy);
}