#ifndef _COMPONENT_H
#define _COMPONENT_H

#include "..\Defs.h"
#include "..\GUI\Output.h"
#include <fstream>
using std::ofstream;
using std::ifstream;
using std::string;

class InputPin;
class OutputPin;

class Component
{
private:
    string m_Label;
    int m_ID;
protected:
    GraphicsInfo m_GfxInfo;
    bool selected;
public:
    Component(const GraphicsInfo& r_GfxInfo);
    Component();

    virtual void Operate() = 0;
    virtual void Draw(Output* pOut) = 0;

    virtual bool IsGate() const { return false; }
    virtual bool IsLabel() const { return false; }
    virtual int GetOutPinStatus() = 0;
    virtual int GetInputPinStatus(int n) = 0;
    virtual void setInputPinStatus(int n, STATUS s) = 0;
    virtual Component* Clone(const GraphicsInfo& newGfx) const = 0;
    virtual bool IsLED() const { return false; }
    virtual void SetSelected(bool select) { selected = select; }
    virtual bool IsSelected() const { return selected; }

    virtual void SetLabel(const string& lbl) { m_Label = lbl; }
    string GetLabel() const { return m_Label; }
    virtual bool IsConnection() const { return false; }
    virtual OutputPin* GetOutputPin() { return nullptr; }
    virtual InputPin* GetInputPin(int index) { return nullptr; }

    void SetID(int id) { m_ID = id; }
    int GetID() const { return m_ID; }

    virtual void Save(ofstream& out);
    virtual void Load(ifstream& in);



    virtual bool IsInside(int x, int y)
    {
        if (x >= m_GfxInfo.x1 && x <= m_GfxInfo.x2 &&
            y >= m_GfxInfo.y1 && y <= m_GfxInfo.y2)
            return true;
        return false;
    }

    GraphicsInfo GetGraphicsInfo() const { return m_GfxInfo; }

    virtual void SetGraphicsInfo(GraphicsInfo NewGfx)
    {
        m_GfxInfo = NewGfx;
    }

    virtual ~Component();
};

#endif
