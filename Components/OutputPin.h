#ifndef _OUTPUTPIN_H
#define _OUTPUTPIN_H

#include "Pin.h"
class Connection;	//Forward class declaration

class OutputPin : public Pin	//inherited from class Pin
{
private:
	//Array of connections (pointers) to be connected to that OutputPin
	Connection* m_Connections[MAX_CONNS];
	int m_FanOut;	//Maximum No. of connections connected to that output pin
	int m_Conn;		//Actual No. of connections connected to that output pin

public:
	OutputPin(int r_FanOut);
	bool ConnectTo(Connection* r_Conn);	//connect to a new connection
	void DisconnectAll(); //Disconnects all connections

	// New methods
	bool CanConnect() const { return m_Conn < m_FanOut; }
	int getPositionX() const;
	int getPositionY() const;
};

#endif