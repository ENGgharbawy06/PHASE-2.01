#include "OutputPin.h"
#include "Connection.h"

OutputPin::OutputPin(int r_FanOut)
{
	m_Conn = 0;
	m_FanOut = r_FanOut > MAX_CONNS ? MAX_CONNS : r_FanOut;
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

int OutputPin::getPositionX() const
{
	// Placeholder - returns 0 for now
	return 0;
}

int OutputPin::getPositionY() const
{
	// Placeholder - returns 0 for now
	return 0;
}