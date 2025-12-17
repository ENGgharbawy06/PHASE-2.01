#ifndef _INPUTPIN_H
#define _INPUTPIN_H

#include "Pin.h"
class Component; 
class Connection; 

class InputPin : public Pin	
{
	Component* pComp; 
	bool isConnected; 
	int m_X, m_Y; 
	Connection* m_Connection;

public:
	InputPin(); 
	void setComponent(Component* pCmp);	
	Component* getComponent() const;	
	bool getIsConnected() const; 
	void setConnection(Connection* pConn);
	Connection* getConnection() const;
	bool connect(); 
	void disconnect(); 
	void setPosition(int x, int y); 
	
	int getPositionX() const;
	int getPositionY() const;
};

#endif