#include "InputPin.h"

InputPin::InputPin()
{}

void InputPin::setComponent(Component *pCmp)
{
	this->pComp = pCmp;
}

Component* InputPin::getComponent()
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
