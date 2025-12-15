#include "InputPin.h"
#include "Component.h"

InputPin::InputPin()
{
	isConnected = false;
	pComp = nullptr;  // Initialize to nullptr
	m_Connection = nullptr;
	m_X = 0;
	m_Y = 0;
}

void InputPin::setComponent(Component* pCmp)
{
	this->pComp = pCmp;
}

Component* InputPin::getComponent() const  // Add const here!
{
	return pComp;
}

bool InputPin::getIsConnected() const
{
	return isConnected;
}

bool InputPin::connect()
{
	if (!isConnected)
	{
		isConnected = true;
		return true;
	}
	return false;
}

void InputPin::disconnect()
{
	isConnected = false;
	m_Connection = nullptr;
}

void InputPin::setConnection(Connection* pConn)
{
	m_Connection = pConn;
}

Connection* InputPin::getConnection() const
{
	return m_Connection;
}


int InputPin::getPositionX() const
{
	
	return m_X;
}

int InputPin::getPositionY() const
{
	
	return m_Y;
}

void InputPin::setPosition(int x, int y)
{
	m_X = x;
	m_Y = y;
}