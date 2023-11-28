#ifndef _CANVAS_MANAGER_H_
#define _CANVAS_MANAGER_H_

#include "Impl/Widget/Widget.h"
#include "Impl/Widget/CanvasView/CanvasView.h"
#include "Container/Container.h"

class CanvasManager : public Widget
{
    public:

        CanvasManager(  const plug::LayoutBox& box):
                        Widget(box),
                        m_widgets(),
                        m_canvases(),
                        m_cnt_canvas(0),
                        m_delete_canvas(false){}
    
        ~CanvasManager()
        {
            size_t size = m_canvases.getSize();
            for (size_t it = 0; it < size; it++)
                delete m_canvases[it];

            size = m_canvases.getSize();
            for (size_t it = 0; it < size; it++)
                delete m_widgets[it];
        };

        virtual void draw(plug::TransformStack &stack, plug::RenderTarget &target);

        virtual void onParentUpdate(const plug::LayoutBox &parent_box);

        //void createCanvas(ToolPalette *tool_palette, FilterPalette *filter_palette);

        Canvas* getActiveCanvas(void);

    protected:    

        virtual void onTick             (const plug::TickEvent &event, plug::EHC &context);

        virtual void onMouseMove        (const plug::MouseMoveEvent &event, plug::EHC &context);
        virtual void onMousePressed     (const plug::MousePressedEvent &event, plug::EHC &context);
        virtual void onMouseReleased    (const plug::MouseReleasedEvent &event, plug::EHC &context);

        virtual void onKeyboardPressed  (const plug::KeyboardPressedEvent &event, plug::EHC &context);
        virtual void onKeyboardReleased (const plug::KeyboardReleasedEvent &event, plug::EHC &context);

        
    private:
        Container<Widget*> m_widgets;
        bool m_delete_canvas;

        Container<Canvas*> m_canvases;

        size_t m_cnt_canvas;
}; 

#endif