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
                    canvas_(canvas), 
                    scale_(scale), 
                    canvas_pos_(0.0, 0.0){}
                
        virtual ~CanvasView(){}

        virtual void draw(plug::TransformStack &stack, plug::RenderTarget &target);

        void setCanvasPos(const plug::Vec2d &pos) {canvas_pos_ = pos;}
        plug::Vec2d getCanvasPos(void) {return canvas_pos_;}

    protected:

        virtual void onTick             (const plug::TickEvent &event, plug::EHC &context);

        virtual void onMouseMove        (const plug::MouseMoveEvent &event, plug::EHC &context);
        virtual void onMousePressed     (const plug::MousePressedEvent &event,plug::EHC &context);
        virtual void onMouseReleased    (const plug::MouseReleasedEvent &event, plug::EHC &context);

        virtual void onKeyboardPressed  (const plug::KeyboardPressedEvent &event, plug::EHC &context);
        virtual void onKeyboardReleased (const plug::KeyboardReleasedEvent &event, plug::EHC &context);
    private:
    
        plug::Canvas *canvas_;      
        plug::Vec2d scale_;

        plug::Vec2d canvas_pos_;
};

#endif