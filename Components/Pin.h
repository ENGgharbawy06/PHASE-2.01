#ifndef _PIN_H
#define _PIN_H

#include "..\Defs.h"

class Pin
{
protected:
	STATUS m_Status;
public:
	Pin();
	void setStatus(STATUS r_Status);
	STATUS getStatus();
};

#endif