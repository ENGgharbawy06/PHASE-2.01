#include "Label.h"
#include "..\GUI\Output.h"

Label::Label(const GraphicsInfo& r_GfxInfo, const std::string& txt)
{
    m_GfxInfo = r_GfxInfo;
    m_Text = txt;
}

void Label::Draw(Output* pOut)
{
    pOut->DrawLabel(m_GfxInfo, m_Text);
}

void Label::SetText(const std::string& txt)
{
    m_Text = txt;
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
    return new Label(newGfx, m_Text);
}


