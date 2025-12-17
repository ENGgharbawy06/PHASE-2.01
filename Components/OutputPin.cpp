#include "OutputPin.h"
#include "Connection.h"
#include "Component.h" 

OutputPin::OutputPin(int r_FanOut)
{
	m_Conn = 0;
	m_FanOut = r_FanOut > MAX_CONNS ? MAX_CONNS : r_FanOut;
	pComp = nullptr; 
}

bool OutputPin::ConnectTo(Connection* r_Conn)
{
	if (m_Conn < m_FanOut)
	{
		m_Connections[m_Conn++] = r_Conn;
		return true;
	}

	return false;
}

bool OutputPin::Disconnect(Connection* r_Conn)
{
	for (int i = 0; i < m_Conn; i++)
	{
		if (m_Connections[i] == r_Conn)
		{
			
			m_Connections[i] = m_Connections[m_Conn - 1];
			m_Connections[m_Conn - 1] = nullptr; 
			m_Conn--;
			return true;
		}
	}
	return false;
}

void OutputPin::DisconnectAll()
{
	for (int i = 0; i < m_Conn; i++)
	{
		if (m_Connections[i])
		{
			m_Connections[i] = nullptr;
		}
	}
	m_Conn = 0;
}

void OutputPin::setComponent(Component* pCmp)
{
	pComp = pCmp;
}

int OutputPin::getPositionX() const
{
	if (pComp)
		return pComp->GetGraphicsInfo().x2; 
	return 0;
}

int OutputPin::getPositionY() const
{
	if (pComp)
		return (pComp->GetGraphicsInfo().y1 + pComp->GetGraphicsInfo().y2) / 2; 
	return 0;
}