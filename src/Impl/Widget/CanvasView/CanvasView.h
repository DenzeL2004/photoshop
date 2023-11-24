#ifndef _CANVASVIEW_H_
#define _CANVASVIEW_H_

#include "Impl/Widget/Widget.h"
#include "Impl/Canvas/Canvas.h"
#include "Impl/Graphic/Graphic.h"


class CanvasView: public Widget
{
    public:

        CanvasView( plug::Canvas *canvas,
                    const plug::LayoutBox& box, 
                    const plug::Vec2d &scale = Vec2d(1.0, 1.0)):
                    Widget(box), 
                    m_canvas(canvas), 
                    m_scale(scale), 
                    m_canvas_pos(0.0, 0.0){}
                
        virtual ~CanvasView(){}

        virtual void draw(plug::TransformStack &stack, plug::RenderTarget &target);

        void setCanvasPos(const plug::Vec2d &pos) {m_canvas_pos = pos;}
        plug::Vec2d getCanvasPos(void) {return m_canvas_pos;}

    protected:

        virtual void onTick             (const plug::TickEvent &event, plug::EHC &context);

        virtual void onMouseMove        (const plug::MouseMoveEvent &event, plug::EHC &context);
        virtual void onMousePressed     (const plug::MousePressedEvent &event,plug::EHC &context);
        virtual void onMouseReleased    (const plug::MouseReleasedEvent &event, plug::EHC &context);

        virtual void onKeyboardPressed  (const plug::KeyboardPressedEvent &event, plug::EHC &context);
        virtual void onKeyboardReleased (const plug::KeyboardReleasedEvent &event, plug::EHC &context);
    private:
    
        plug::Canvas *m_canvas;      
        plug::Vec2d m_scale;

        plug::Vec2d m_canvas_pos;
};

#endif