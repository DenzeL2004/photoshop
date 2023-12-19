#ifndef _POLYLINE_TOOL_H_
#define _POLYLINE_TOOL_H_

#include "Plug/Graphics.h"
#include "Plug/Canvas.h"
#include "Plug/Math.h"

#include "Impl/Tool/PluginUtil.h"
#include "Impl/Util/Sfml.h"

class PolylineToolPreview;

class PolylineTool : public DefTool
{
    public:
        PolylineTool();

        virtual void setColorPalette(plug::ColorPalette &palette);

        virtual void setActiveCanvas(plug::Canvas &canvas);

        virtual void onMainButton(const plug::ControlState &state, const plug::Vec2d &position);
        virtual void onSecondaryButton(const plug::ControlState &state, const plug::Vec2d &position);

        virtual void onModifier1(const plug::ControlState &state){}
        virtual void onModifier2(const plug::ControlState &state){}
        virtual void onModifier3(const plug::ControlState &state){}

        virtual void onMove(const plug::Vec2d &position);

        virtual void onConfirm(void);

        virtual void onCancel(void);

        virtual plug::Widget* getWidget(void);

        virtual ~PolylineTool();

        PolylineTool(const PolylineTool &other) = delete;
        PolylineTool &operator= (const PolylineTool &other) = delete;

    private:
        void drawLine(void);

        plug::ColorPalette *m_color_palette;
        plug::Canvas *m_canvas;

        bool m_active;

        plug::VertexArray m_vertexs;
        plug::Vec2d m_mouse_pos;
        plug::Color m_color;

        double m_radius;

        PolylineToolPreview *m_preview;

        bool m_setting_flags;
        double m_setting_radius;

        plug::Widget *m_setting;
};

extern "C" plug::Plugin* loadPlugin(void);

#endif