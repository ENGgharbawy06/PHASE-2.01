#include "Label.h"
#include "..\GUI\Output.h"

Label::Label(const GraphicsInfo& r_GfxInfo, const std::string& txt)
{
    m_GfxInfo = r_GfxInfo;
    SetLabel(txt);
}

void Label::Draw(Output* pOut)
{
    pOut->DrawLabel(m_GfxInfo, GetLabel());
}

void Label::SetText(const std::string& txt)
{
    SetLabel(txt);
}

std::string Label::GetText() const
{
    return m_Text;
}

int Label::GetOutPinStatus() { return -1; }
int Label::GetInputPinStatus(int n) { return -1; }
void Label::setInputPinStatus(int n, STATUS s) {}
Component* Label::Clone(const GraphicsInfo& newGfx) const
{
    return new Label(newGfx, GetLabel());
}

void Label::Save(ofstream& out)
{
    out << "LABEL "
        << GetID() << " "
        << (GetLabel() == "" ? "$" : GetLabel()) << " "
        << m_GfxInfo.x1 << " " << m_GfxInfo.y1 << " "
        << GetLabel() << "\n";
}

void Label::Load(ifstream& in)
{
    int id, x, y;
    string lbl;

    in >> id >> lbl >> x >> y;

    SetID(id);
    if (lbl != "$")
        SetLabel(lbl);

    
    in.ignore(); 
    getline(in, m_Text);

    m_GfxInfo.x1 = x;
    m_GfxInfo.y1 = y;
    m_GfxInfo.x2 = x + 40;
    m_GfxInfo.y2 = y + 15;
}

