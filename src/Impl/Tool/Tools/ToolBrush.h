#ifndef _TOOL_BRUSH_H_
#define _TOOL_BRUSH_H_

#include "Plug/Tool/Tool.h"

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

        virtual plug::Plugin *tryGetInterface(size_t interface_id) {return nullptr;}
        virtual void addReference(void){}
        virtual void release(void){}
        virtual const plug::PluginData *getPluginData(void) const {return nullptr;}

    private:

        void drawForm(const plug::Vec2d &position);

        plug::ColorPalette *m_color_palette;
        plug::Canvas *m_canvas;

        plug::Vec2d m_hold_pos;

        bool m_active;
};




#endif