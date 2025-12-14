#pragma once

#include "Action.h" // Assumed base class for all user commands
#include "Actions/Action.h" // Alternative include path, use the correct one for your project

// Class responsible for switching the application's operating mode
// from Simulation Mode back to Design Mode.
class SwitchToDesign : public Action
{
public:
    // Constructor
    // Takes a pointer to the ApplicationManager (pApp) to interact with the main state
    SwitchToDesign(ApplicationManager* pApp);

    // Reads parameters from the user (typically empty for a mode switch)
    virtual void ReadActionParameters();

    // Executes the action: Calls ApplicationManager to set the mode and updates the toolbar.
    virtual void Execute();

    // Undo: Not typically implemented for simple mode switches, but required by the base Action class.
    virtual void Undo();

    // Redo: Not typically implemented for simple mode switches, but required by the base Action class.
    virtual void Redo();

    // Virtual destructor is good practice for classes used polymorphically
    virtual ~SwitchToDesign() {}
};