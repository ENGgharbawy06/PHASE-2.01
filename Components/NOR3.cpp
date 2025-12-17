#include "NOR3.h"

NOR3::NOR3(const GraphicsInfo& r_GfxInfo, int r_FanOut) : Gate(3, r_FanOut)
{
    m_GfxInfo = r_GfxInfo;

    
    m_InputPins[0].setPosition(m_GfxInfo.x1, m_GfxInfo.y1 + 14);

    
    m_InputPins[1].setPosition(m_GfxInfo.x1, (m_GfxInfo.y1 + m_GfxInfo.y2) / 2);

    
    m_InputPins[2].setPosition(m_GfxInfo.x1, m_GfxInfo.y2 - 13);
}

void NOR3::SetGraphicsInfo(GraphicsInfo NewGfx)
{
    Component::SetGraphicsInfo(NewGfx);

    
    m_InputPins[0].setPosition(m_GfxInfo.x1, m_GfxInfo.y1 + 14);

    
    m_InputPins[1].setPosition(m_GfxInfo.x1, (m_GfxInfo.y1 + m_GfxInfo.y2) / 2);

    
    m_InputPins[2].setPosition(m_GfxInfo.x1, m_GfxInfo.y2 - 13);
}

void NOR3::Operate()
{
    STATUS in1 = m_InputPins[0].getStatus();
    STATUS in2 = m_InputPins[1].getStatus();
    STATUS in3 = m_InputPins[2].getStatus();

   
    if (in1 == LOW && in2 == LOW && in3 == LOW)
        m_OutputPin.setStatus(HIGH);
    else
        m_OutputPin.setStatus(LOW);
}

void NOR3::Draw(Output* pOut)
{
    pOut->DrawNOR3(m_GfxInfo, selected);
}

int NOR3::GetOutPinStatus()
{
    return m_OutputPin.getStatus();
}

int NOR3::GetInputPinStatus(int n)
{
    return m_InputPins[n - 1].getStatus();
}

void NOR3::setInputPinStatus(int n, STATUS s)
{
    m_InputPins[n - 1].setStatus(s);
}

Component* NOR3::Clone(const GraphicsInfo& newGfx) const
{
    return new NOR3(newGfx, NOR3_FANOUT);
}

void NOR3::Save(ofstream& out)
{
    out << "NOR3 "
        << GetID() << " "
        << (GetLabel() == "" ? "$" : GetLabel()) << " "
        << m_GfxInfo.x1 << " " << m_GfxInfo.y1 << "\n";
}

void NOR3::Load(ifstream& in)
{
    int id, x, y;
    string lbl;

    in >> id >> lbl >> x >> y;

    SetID(id);
    if (lbl != "$")
        SetLabel(lbl);

    m_GfxInfo.x1 = x;
    m_GfxInfo.y1 = y;

    m_GfxInfo.x2 = x + UI.NOR3_Width;
    m_GfxInfo.y2 = y + UI.NOR3_Height;

    m_InputPins[0].setPosition(m_GfxInfo.x1, m_GfxInfo.y1 + 14);
    m_InputPins[1].setPosition(m_GfxInfo.x1, (m_GfxInfo.y1 + m_GfxInfo.y2) / 2);
    m_InputPins[2].setPosition(m_GfxInfo.x1, m_GfxInfo.y2 - 13);
}

NOR3::~NOR3()
{
}
