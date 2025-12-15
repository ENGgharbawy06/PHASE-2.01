#include "Component.h"

Component::Component(const GraphicsInfo& r_GfxInfo)
{
    m_GfxInfo = r_GfxInfo;
    selected = false;
    m_ID = -1;
    m_Label = "";
}

Component::Component()
{
    m_GfxInfo.x1 = m_GfxInfo.y1 = m_GfxInfo.x2 = m_GfxInfo.y2 = 0;
    selected = false;
    m_ID = -1;
    m_Label = "";
}

void Component::Save(ofstream& out)
{
}

void Component::Load(ifstream& in)
{
}

Component::~Component()
{
}
