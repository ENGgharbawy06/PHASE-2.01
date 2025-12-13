#ifndef _ADD_CONNECTION_H
#define _ADD_CONNECTION_H

#include "Actions/Action.h"
#include "..\Components\Gate.h"
#include "..\Components\InputPin.h"
#include "..\Components\\OutputPin.h"
#include "..\Components\Connection.h"

class AddConnection : public Action
{
private:
    Gate* SrcGate;   // source gate
    Gate* DstGate;   // destination gate
    OutputPin* SrcPin;    // source output pin
    InputPin* DstPin;    // destination input pin
    GraphicsInfo GInfo;    // graphics info for drawing the wire

public:
    AddConnection(ApplicationManager* pApp);

    virtual void ReadActionParameters() override;
    virtual void Execute() override;
    virtual ~AddConnection();
	virtual void Undo() override;
	virtual void Redo() override;
};

#endif
