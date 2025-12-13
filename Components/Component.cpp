#include "Component.h"

Component::Component(const GraphicsInfo &r_GfxInfo)
{
	m_GfxInfo = r_GfxInfo;	
	selected = false;
}

Component::Component()
{
	m_GfxInfo.x1 = m_GfxInfo.y1 = m_GfxInfo.x2 = m_GfxInfo.y2 = 0; 
	selected = false; 
}

Component::~Component()
{}
