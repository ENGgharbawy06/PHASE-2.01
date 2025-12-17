#ifndef _OUTPUTPIN_H
#define _OUTPUTPIN_H

#include "Pin.h"
class Connection;	
class Component;    

class OutputPin : public Pin	
{
private:
	//Array of connections (pointers) 
	Connection* m_Connections[MAX_CONNS];
	int m_FanOut;	//Maximum No. of connections connected m3 el output pin 
	int m_Conn;		//Actual No. of connections connected m3 el output pin 


	Component* pComp; 

public:
	OutputPin(int r_FanOut);
	bool ConnectTo(Connection* r_Conn);	//connect
	void DisconnectAll(); //Disconnects 
	bool Disconnect(Connection* r_Conn); //Disconnects 

	
	void setComponent(Component* pCmp);
	Component* getComponent() const { return pComp; }

	
	bool CanConnect() const { return m_Conn < m_FanOut; }
	int getPositionX() const;
	int getPositionY() const;
};

#endif