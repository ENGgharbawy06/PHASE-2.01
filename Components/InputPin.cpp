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
	// Placeholder - returns 0 for now
	return pComp->GetGraphicsInfo().x1;
}

int InputPin::getPositionY() const
{
	// Placeholder - returns 0 for now
	return (pComp->GetGraphicsInfo().y1 + pComp->GetGraphicsInfo().y2) / 2;
}