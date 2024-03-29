#ifndef _CANVASVIEW_H_
#define _CANVASVIEW_H_

#include <cstring>

#include "Impl/Widget/Widget.h"
#include "Impl/Canvas/Canvas.h"
#include "Impl/Graphic/Graphic.h"

#include "Plug/Event/Event.h"

#include "Impl/Tool/ColorPalette/ColorPalette.h"

#include "Impl/Tool/PluginUtil.h"
#include "Impl/Tool/FilterPalette/FilterPalette.h"
#include "Impl/Tool/ToolPalette/ToolPalette.h"

#include "App/AppConfig.h"

namespace plug
{

const size_t Focuse = 25;

struct FocuseEvent : public plug::Event 
{
    FocuseEvent(const bool flag)
      : Event(Focuse), focuse_flag(flag){}
      
    bool focuse_flag;
};

const size_t SaveCanvas = 26;

struct SaveEvent : public plug::Event 
{
    SaveEvent(const char* const &path)
      : Event(SaveCanvas), file_path(path){}
      
    const char* const file_path;
};

const size_t FilterApply = 27;

struct FilterApplyEvent : public plug::Event 
{
    FilterApplyEvent(size_t type)
      : Event(FilterApply), filter_type(type){}
      
    size_t filter_type;
};

const size_t ToolChoose = 28;

struct ToolChooseEvent : public plug::Event 
{
    ToolChooseEvent(size_t type)
      : Event(ToolChoose), tool_type(type){}
      
    size_t tool_type;
};

}

class CanvasView: public Widget
{
    public:

        CanvasView( plug::Canvas &canvas,
                    ToolPalette &tool_palette,
                    FilterPalette &filter_palette,
                    plug::ColorPalette &color_palette,
                    const plug::LayoutBox& box):
                    Widget(box), 
                    m_canvas(canvas),
                    m_texture(nullptr),
                    m_update_texture(true),
                    m_focuse(false),
                    m_canvas_pos(0.0, 0.0),
                    m_color_palette(color_palette),
                    m_filter_palette(filter_palette),
                    m_tool_palette(tool_palette), 
                    m_tool(nullptr){}

        CanvasView(const CanvasView &other) = delete;
        virtual CanvasView &operator= (const CanvasView &other) = delete;

        virtual ~CanvasView()
        {
            delete m_texture;

            if (m_tool) m_tool->release();
        }

        virtual void draw(plug::TransformStack &stack, plug::RenderTarget &target);

        virtual void onParentUpdate(const plug::LayoutBox &parent_box);

        virtual void onEvent(const plug::Event &event, plug::EHC &context);

        void setCanvasPos(const plug::Vec2d &pos)
        {
            m_canvas_pos = pos;
            m_update_texture = true;
        }

        plug::Vec2d getCanvasPos(void) {return m_canvas_pos;}
        plug::Vec2d getCanvasSize(void) {return m_canvas.getSize();}

    protected:

        virtual void onTick             (const plug::TickEvent &event, plug::EHC &context);

        virtual void onMouseMove        (const plug::MouseMoveEvent &event, plug::EHC &context);
        virtual void onMousePressed     (const plug::MousePressedEvent &event,plug::EHC &context);
        virtual void onMouseReleased    (const plug::MouseReleasedEvent &event, plug::EHC &context);

        virtual void onKeyboardPressed  (const plug::KeyboardPressedEvent &event, plug::EHC &context);
        virtual void onKeyboardReleased (const plug::KeyboardReleasedEvent &event, plug::EHC &context);

        virtual void onFocuse           (const plug::FocuseEvent &event, plug::EHC &context);
        virtual void onSave             (const plug::SaveEvent &event, plug::EHC &context);
        virtual void onFilterApply      (const plug::FilterApplyEvent &event, plug::EHC &context);
        virtual void onToolChoose       (const plug::ToolChooseEvent &event, plug::EHC &context);
    
    private:

        void updateTexture(void);

        plug::Canvas &m_canvas;      
        plug::Vec2d m_scale;

        plug::Texture *m_texture;

        bool m_update_texture;

        plug::Vec2d m_canvas_pos;

        bool m_focuse;

        plug::ColorPalette &m_color_palette;
        FilterPalette &m_filter_palette;
        ToolPalette &m_tool_palette;

        plug::Tool* m_tool;
};

#endif