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
    virtual void Operate() override {}   

    void SetText(const std::string& txt);
    std::string GetText() const;
    virtual int GetOutPinStatus() override;
    virtual int GetInputPinStatus(int n) override;
    virtual void setInputPinStatus(int n, STATUS s) override;
	virtual Component* Clone(const GraphicsInfo& newGfx) const override;
    virtual void Save(ofstream& out) override;
    virtual void Load(ifstream& in) override;
    virtual bool IsLabel() const { return true; }
	

};

#endif
