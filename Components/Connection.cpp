#include "Connection.h"
#include "Gate.h"

Connection::Connection(const GraphicsInfo &r_GfxInfo, OutputPin *pSrcPin,InputPin *pDstPin):Component(r_GfxInfo)	
{
	SrcPin = pSrcPin;
	DstPin = pDstPin;
}
void Connection::setSourcePin(OutputPin *pSrcPin)
{	SrcPin = pSrcPin;	}

bool Connection::IsConnection() const
{
	return true; // "Yes, I am a connection"
}

OutputPin* Connection::getSourcePin()
{	return SrcPin;	}


void Connection::setDestPin(InputPin *pDstPin)
{	DstPin = pDstPin;	}

InputPin* Connection::getDestPin()
{	return DstPin;	}


void Connection::Operate()
{
	if (SrcPin && DstPin)
	{
		//Status of connection destination pin = status of connection source pin
		DstPin->setStatus((STATUS)SrcPin->getStatus());
	}
}

void Connection::Draw(Output* pOut)
{
	if (SrcPin) {
		m_GfxInfo.x1 = SrcPin->getPositionX();
		m_GfxInfo.y1 = SrcPin->getPositionY();
	}

	if (DstPin) {
		m_GfxInfo.x2 = DstPin->getPositionX();
		m_GfxInfo.y2 = DstPin->getPositionY();
	}

	
	pOut->DrawConnection(m_GfxInfo, selected);
}



int Connection::GetOutPinStatus()	
{
	return DstPin->getStatus();
}


int Connection::GetInputPinStatus(int n)	
{
	return SrcPin->getStatus();		
}

void Connection::setInputPinStatus(int n, STATUS s)
{
	SrcPin->setStatus(s);
}

Component* Connection::Clone(const GraphicsInfo& gfx) const
{
	return new Connection(gfx, nullptr, nullptr);
}


bool Connection::IsInside(int x, int y)
{
	int Tolerance = 4;
	int midx = (m_GfxInfo.x1 + m_GfxInfo.x2) / 2;

	// Helper variables to calculate distance without std::abs
	int distY1 = y - m_GfxInfo.y1;
	if (distY1 < 0) distY1 = -distY1; // Absolute value

	int distX = x - midx;
	if (distX < 0) distX = -distX;    // Absolute value

	int distY2 = y - m_GfxInfo.y2;
	if (distY2 < 0) distY2 = -distY2; // Absolute value

	// ---------------------------------------------------
	// 1. Check First Horizontal Segment (Source -> Mid)
	// ---------------------------------------------------
	if (distY1 <= Tolerance)
	{
		// Calculate min and max X manually
		int smallerX = (m_GfxInfo.x1 < midx) ? m_GfxInfo.x1 : midx;
		int largerX = (m_GfxInfo.x1 > midx) ? m_GfxInfo.x1 : midx;

		if (x >= smallerX && x <= largerX)
			return true;
	}

	// ---------------------------------------------------
	// 2. Check Vertical Segment (at Mid)
	// ---------------------------------------------------
	if (distX <= Tolerance)
	{
		// Calculate min and max Y manually
		int smallerY = (m_GfxInfo.y1 < m_GfxInfo.y2) ? m_GfxInfo.y1 : m_GfxInfo.y2;
		int largerY = (m_GfxInfo.y1 > m_GfxInfo.y2) ? m_GfxInfo.y1 : m_GfxInfo.y2;

		if (y >= smallerY && y <= largerY)
			return true;
	}

	// ---------------------------------------------------
	// 3. Check Second Horizontal Segment (Mid -> Dest)
	// ---------------------------------------------------
	if (distY2 <= Tolerance)
	{
		// Calculate min and max X manually
		int smallerX = (midx < m_GfxInfo.x2) ? midx : m_GfxInfo.x2;
		int largerX = (midx > m_GfxInfo.x2) ? midx : m_GfxInfo.x2;

		if (x >= smallerX && x <= largerX)
			return true;
	}

	return false;
}
Connection::~Connection()
{
	 
	if (DstPin != nullptr)
	{
		
		DstPin->setConnection(nullptr);
	}

	
	if (SrcPin != nullptr)
	{
		
		SrcPin->Disconnect(this);
	}
}

void Connection::Disconnect()
{
	
	if (DstPin != nullptr)
	{
		DstPin->setConnection(nullptr);
	}

	
	if (SrcPin != nullptr)
	{
		SrcPin->Disconnect(this);
	}
}

// 2. دالة الإعادة (تستدعى عند الـ Undo)
//void Connection::Reconnect()
//{
//	// إعادة ربط الـ Destination Pin
//	if (DstPin != nullptr)
//	{
//		DstPin->setConnection(this);
//	}
//
//	// إعادة ربط الـ Source Pin
//	if (SrcPin != nullptr)
//	{
//		SrcPin->ConnectTo(this); // تأكد أن هذه الدالة موجودة في OutputPin
//	}
//}

void Connection::Save(ofstream& out)
{
	Component* srcComp = SrcPin->getComponent();
	Component* dstComp = DstPin->getComponent();

	if (!srcComp || !dstComp) return;

	// Find which input pin number this is (1-based)
	int pinNum = 1;
	if (Gate* g = dynamic_cast<Gate*>(dstComp))
	{
		for (int i = 0; i < g->GetInputPinCount(); i++)
		{
			if (g->GetInputPin(i) == DstPin)
			{
				pinNum = i + 1;
				break;
			}
		}
	}

	out << srcComp->GetID() << " "
		<< dstComp->GetID() << " "
		<< pinNum << "\n";
}

void Connection::Load(ifstream& in)
{
	// Connections are loaded in ApplicationManager::Load()
	// This function is not used directly
}