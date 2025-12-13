#include "InputPin.h"

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
	// Placeholder - returns 0 for now
	return 0;
}

int InputPin::getPositionY() const
{
	// Placeholder - returns 0 for now
	return 0;
}