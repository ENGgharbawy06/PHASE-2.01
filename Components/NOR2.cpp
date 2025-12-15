#include "NOR2.h"

NOR2::NOR2(const GraphicsInfo& r_GfxInfo, int r_FanOut) : Gate(2, r_FanOut)
{
    m_GfxInfo.x1 = r_GfxInfo.x1;
    m_GfxInfo.y1 = r_GfxInfo.y1;
    m_GfxInfo.x2 = r_GfxInfo.x2;
    m_GfxInfo.y2 = r_GfxInfo.y2;

    m_InputPins[0].setPosition(m_GfxInfo.x1, m_GfxInfo.y1 + 15);
    m_InputPins[1].setPosition(m_GfxInfo.x1, m_GfxInfo.y2 - 16);
}

void NOR2::SetGraphicsInfo(GraphicsInfo NewGfx)
{
    Component::SetGraphicsInfo(NewGfx);

    // Pin 1 (Top)
    m_InputPins[0].setPosition(m_GfxInfo.x1, m_GfxInfo.y1 + 15);
    // Pin 2 (Bottom)
    m_InputPins[1].setPosition(m_GfxInfo.x1, m_GfxInfo.y2 - 16);
}

void NOR2::Operate()
{
    STATUS in1 = m_InputPins[0].getStatus();
    STATUS in2 = m_InputPins[1].getStatus();

    if (in1 == LOW && in2 == LOW)
        m_OutputPin.setStatus(HIGH);
    else
        m_OutputPin.setStatus(LOW);
}

void NOR2::Draw(Output* pOut)
{
    pOut->DrawNOR2(m_GfxInfo, selected);
}

int NOR2::GetOutPinStatus()
{
    return m_OutputPin.getStatus();
}

int NOR2::GetInputPinStatus(int n)
{
    return m_InputPins[n - 1].getStatus();
}

void NOR2::setInputPinStatus(int n, STATUS s)
{
    m_InputPins[n - 1].setStatus(s);
}

Component* NOR2::Clone(const GraphicsInfo& newGfx) const
{
    return new NOR2(newGfx, NOR2_FANOUT);
}

void NOR2::Save(ofstream& out)
{
    out << "NOR2 "
        << GetID() << " "
        << (GetLabel() == "" ? "$" : GetLabel()) << " "
        << m_GfxInfo.x1 << " " << m_GfxInfo.y1 << "\n";
}

void NOR2::Load(ifstream& in)
{
    int id, x, y;
    string lbl;

    in >> id >> lbl >> x >> y;

    SetID(id);
    if (lbl != "$")
        SetLabel(lbl);

    m_GfxInfo.x1 = x;
    m_GfxInfo.y1 = y;

    m_GfxInfo.x2 = x + UI.NOR2_Width;
    m_GfxInfo.y2 = y + UI.NOR2_Height;

    m_InputPins[0].setPosition(m_GfxInfo.x1, m_GfxInfo.y1 + 15);
    m_InputPins[1].setPosition(m_GfxInfo.x1, m_GfxInfo.y2 - 15);
}
NOR2::~NOR2()
{
}
