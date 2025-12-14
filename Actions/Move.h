#pragma once
#ifndef MOVE_H
#define MOVE_H

#include "Action.h"

    class Move : public Action // Inheretance mn el Action
    {
        int x1, y1; // Reference Point (Start)
        int x2, y2; // Destination Point (End)
        int diffx, diffy; //For undo/redo (Fi variables tanya lel move nafsaha fel .cpp)
    public:
        Move(ApplicationManager* pApp);
        virtual void ReadActionParameters();
        virtual void Execute();
        
        
        virtual void UndoAction();
       
        virtual void RedoAction();
    };

#endif

