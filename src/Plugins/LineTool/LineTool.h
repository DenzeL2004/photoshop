#ifndef _LINE_TOOL_H_
#define _LINE_TOOL_H_

#include "Impl/Tool/PluginUtil.h"
#include "Plug/Graphics.h"
#include "Plug/Canvas.h"
#include "Plug/Math.h"

class LineToolPreview;

class LineTool : public DefTool
{
    public:
        LineTool();

        virtual void setColorPalette(plug::ColorPalette &palette);

        virtual void setActiveCanvas(plug::Canvas &canvas);

        virtual void onMainButton(const plug::ControlState &state, const plug::Vec2d &position);
        virtual void onSecondaryButton(const plug::ControlState &state, const plug::Vec2d &position){}

        virtual void onModifier1(const plug::ControlState &state){}
        virtual void onModifier2(const plug::ControlState &state){}
        virtual void onModifier3(const plug::ControlState &state){}

        virtual void onMove(const plug::Vec2d &position);

        virtual void onConfirm(void);

        virtual void onCancel(void);

        virtual plug::Widget* getWidget(void);

        virtual ~LineTool();

        LineTool(const LineTool &other) = delete;
        LineTool &operator= (const LineTool &other) = delete;

    private:
        plug::ColorPalette *m_color_palette;
        plug::Canvas *m_canvas;

        bool m_active;

        plug::Vec2d m_begin_pos;
        plug::Vec2d m_end_pos;
        plug::Color m_color;

        LineToolPreview *m_preview;
};

extern "C" plug::Plugin* loadPlugin(void);

#endif