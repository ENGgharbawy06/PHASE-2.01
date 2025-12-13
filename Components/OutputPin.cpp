#include "OutputPin.h"
#include "Connection.h"
#include "Component.h" // <--- ضروري هنا عشان نقدر نستخدم دوال Component

OutputPin::OutputPin(int r_FanOut)
{
	m_Conn = 0;
	m_FanOut = r_FanOut > MAX_CONNS ? MAX_CONNS : r_FanOut;
	pComp = nullptr; // <--- استخدم nullptr أو NULL (بحروف كبيرة) وليس Null
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

// تنفيذ الدالة بنفس الاسم الموجود في الـ header
void OutputPin::setComponent(Component* pCmp)
{
	pComp = pCmp;
}

int OutputPin::getPositionX() const
{
	if (pComp)
		return pComp->GetGraphicsInfo().x2; // الـ Output بيكون عند الحافة اليمنى (x2)
	return 0;
}

int OutputPin::getPositionY() const
{
	if (pComp)
		return (pComp->GetGraphicsInfo().y1 + pComp->GetGraphicsInfo().y2) / 2; // في منتصف الارتفاع
	return 0;
}