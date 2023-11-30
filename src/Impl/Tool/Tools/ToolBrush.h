#ifndef _TOOL_BRUSH_H_
#define _TOOL_BRUSH_H_

#include "Plug/Tool.h"

class BrushData : public plug::PluginData
{
    public:
        BrushData():
            m_name("DENZEL_BRUSH"), 
            m_texture_path("img/RedPressed.png"){}

    virtual const char *getName(void) const { return m_name;}
    virtual const char *getTexturePath(void) const { return m_texture_path; }

    private:
        const char* m_name;
        const char* m_texture_path;
};

class ToolBrush : public plug::Tool
{
    public:
        ToolBrush():m_color_palette(nullptr),
                    m_canvas(nullptr), 
                    m_active(false){}

        virtual void setColorPalette(plug::ColorPalette &palette);

        virtual void setActiveCanvas(plug::Canvas &canvas);

        virtual void onMainButton(const plug::ControlState &state, const plug::Vec2d &position);
        virtual void onSecondaryButton(const plug::ControlState &state, const plug::Vec2d &position){}

        virtual void onModifier1(const plug::ControlState &state){}
        virtual void onModifier2(const plug::ControlState &state){}
        virtual void onModifier3(const plug::ControlState &state){}

        virtual void onMove(const plug::Vec2d &position);

        virtual void onConfirm(void);

        virtual void onCancel(void){}

        virtual plug::Widget *getWidget() { return nullptr; }

        virtual plug::Plugin *tryGetInterface(size_t interface_id) 
        {
            switch (interface_id)
            {
                case static_cast<size_t>(plug::PluginGuid::Plugin):
                {
                    addReference();
                    return static_cast<plug::Plugin*>(this);
                }

                case static_cast<size_t>(plug::PluginGuid::Tool):
                {
                    addReference();
                    return static_cast<plug::Tool*>(this);
                }

                default:
                    return nullptr;
            }
        }

        virtual void addReference(void){m_cnt_reference++;}
        virtual void release(void)
        {
            m_cnt_reference--;

            if (m_cnt_reference <= 0)
            {
                delete this;
            }
        }

        virtual const plug::PluginData *getPluginData(void) const 
        {
            return &m_data;
        }

    private:

        plug::ColorPalette *m_color_palette;
        plug::Canvas *m_canvas;

        plug::Vec2d m_hold_pos;

        bool m_active;

        int m_cnt_reference;

        const BrushData m_data;
};

extern "C" plug::Plugin* loadPlugin(void);

#endif