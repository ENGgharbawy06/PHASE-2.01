#include "Connection.h"

Connection::Connection(const GraphicsInfo &r_GfxInfo, OutputPin *pSrcPin,InputPin *pDstPin):Component(r_GfxInfo)	
	
{
	SrcPin = pSrcPin;
	DstPin = pDstPin;
}
void Connection::setSourcePin(OutputPin *pSrcPin)
{	SrcPin = pSrcPin;	}

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
	pOut->DrawConnection(m_GfxInfo, selected);
}



int Connection::GetOutPinStatus()	//returns status of outputpin if LED, return -1
{
	return DstPin->getStatus();
}


int Connection::GetInputPinStatus(int n)	//returns status of Inputpin # n if SWITCH, return -1
{
	return SrcPin->getStatus();	//n is ignored as connection has only one input pin (src pin)	
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