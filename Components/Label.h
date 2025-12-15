#ifndef _LABEL_H
#define _LABEL_H

#include "Component.h"
#include <string>

class Label : public Component
{
private:
    std::string m_Text;

public:
    Label(const GraphicsInfo& r_GfxInfo, const std::string& txt);

    virtual void Draw(Output* pOut) override;
    virtual void Operate() override {}   // Label لا تعمل operate

    void SetText(const std::string& txt);
    std::string GetText() const;
};

#endif
