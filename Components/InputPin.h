#ifndef _INPUTPIN_H
#define _INPUTPIN_H

#include "Pin.h"
class Component; //Forward class declaration

class InputPin : public Pin	//inherited from class Pin
{
	Component* pComp; //Component at which this pin is associated
	bool isConnected; //Flag to indicate whether this pin is connected or not

public:
	InputPin();
	void setComponent(Component* pCmp);	//sets the component of this input pin
	Component* getComponent() const;	//returns the component of this input pin (add const!)
	bool getIsConnected() const; //Returns whether the pin is connected or not
	bool connect(); //Sets the pin as connected
	void disconnect(); //Sets the pin as disconnected

	// Position methods
	int getPositionX() const;
	int getPositionY() const;
};

#endif