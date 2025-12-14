#include "InputPin.h"
#include "Component.h"

InputPin::InputPin()
{
	isConnected = false;
	pComp = nullptr;  // Initialize to nullptr
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