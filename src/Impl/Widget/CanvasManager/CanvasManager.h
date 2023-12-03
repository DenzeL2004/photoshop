#ifndef _CANVAS_MANAGER_H_
#define _CANVAS_MANAGER_H_

#include "Container/Container.h"

#include "Impl/Widget/Widget.h"
#include "Impl/Widget/CanvasView/CanvasView.h"
#include "Impl/Widget/Frame/Frame.h"
#include "Impl/Widget/Scrollbar/Scrollbar.h"
#include "Impl/Widget/Button/Button.h"
#include "Impl/Widget/ContainerWidget/ContainerWidget.h"

#include "App/AppConfig.h"

class CanvasManager : public Widget
{
    public:

        CanvasManager(  const plug::LayoutBox& box):
                        Widget(box),
                        m_widgets(),
                        m_canvases(),
                        m_cnt_canvas(0),
                        m_delete_canvas(false),
                        m_dialog_window(nullptr)
        {
            m_dialog_window = new ContainerWidget(BaseLayoutBox((box.getSize() - Dialog_window_size ) * 0.5, Dialog_window_size, box.getSize(), false, false));

            Window *window = new Window(getPlugTexture(Dialog_window_texture),
                                        Title(Close_canvas_title_pos, "Do you want to save it?", Dialog_title_scale, Canvas_dialog_title_color),
                                        BaseLayoutBox(plug::Vec2d(0, 0), Dialog_window_size, box.getSize(), false, false));

            Button *close_btn = new Button( getPlugTexture(Cross_button_released), getPlugTexture(Cross_button_pressed), 
                                            getPlugTexture(Cross_button_released), getPlugTexture(Cross_button_pressed), 
                                            BaseLayoutBox(Vec2d(Dialog_window_size.x - Cross_button_size.x, 0), Cross_button_size, Dialog_window_size, false, true),
                                            new Click(m_delete_canvas));

            m_dialog_window->insertWidget(window);
            m_dialog_window->insertWidget(close_btn);
        }
    
        ~CanvasManager()
        {
            size_t size = m_canvases.getSize();
            for (size_t it = 0; it < size; it++)
                delete m_canvases[it];

            size = m_canvases.getSize();
            for (size_t it = 0; it < size; it++)
                delete m_widgets[it];

            delete m_dialog_window;
        };

        virtual void draw(plug::TransformStack &stack, plug::RenderTarget &target);

        virtual void onParentUpdate(const plug::LayoutBox &parent_box);

        void createCanvas(  FilterPalette &filter_palette,
                            plug::ColorPalette &color_palette, const char *file_path = nullptr);

        plug::Canvas* getActiveCanvas(void);

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

        Container<plug::Canvas*> m_canvases;

        size_t m_cnt_canvas;

        ContainerWidget *m_dialog_window;
}; 

#endif