#ifndef _CANVAS_MANAGER_H_
#define _CANVAS_MANAGER_H_

#include "Container/Container.h"

#include "Impl/Widget/Widget.h"
#include "Impl/Widget/CanvasView/CanvasView.h"
#include "Impl/Widget/Frame/Frame.h"
#include "Impl/Widget/Scrollbar/Scrollbar.h"
#include "Impl/Widget/Button/Button.h"
#include "Impl/Widget/ContainerWidget/ContainerWidget.h"
#include "Impl/Widget/TextBox/TextBox.h"

#include "Impl/TransformStack/TransformStack.h"

#include "App/AppConfig.h"

class CanvasManager;

class CloseCanvasWithSave : public Action
{
    public:
        CloseCanvasWithSave(CanvasManager &manager): 
                          m_canvas_manager(manager){}
        ~CloseCanvasWithSave(){}

        void operator() ();

        CloseCanvasWithSave(const CloseCanvasWithSave &other) = delete;
        CloseCanvasWithSave &operator= (const CloseCanvasWithSave &other) = delete;        

    private:

        class SaveCanvas : public Action
        {
        
            public:
                SaveCanvas(CanvasManager &manager):m_canvas_manager(manager){}
                ~SaveCanvas(){}
            
                void operator() ();

            private:
                CanvasManager &m_canvas_manager;
        };
        
        CanvasManager &m_canvas_manager;
};

class CloseCanvasWithoutSave : public Action
{
    public:
        CloseCanvasWithoutSave(CanvasManager &manager): m_canvas_manager(manager){}
        ~CloseCanvasWithoutSave(){};

        void operator() ();        

        CloseCanvasWithoutSave(const CloseCanvasWithoutSave &other) = delete;
        CloseCanvasWithoutSave &operator= (const CloseCanvasWithoutSave &other) = delete;

    private:
        CanvasManager &m_canvas_manager; 
};

class CanvasManager : public Widget
{
    public:
        friend class CloseCanvasWithoutSave;
        friend class CloseCanvasWithSave;

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
                                        Title(Close_canvas_title_pos, Close_canvas_title, Dialog_title_scale, Canvas_dialog_title_color),
                                        BaseLayoutBox(plug::Vec2d(0, 0), Dialog_window_size, box.getSize(), false, false));

            Button *cancel_btn = new Button(getPlugTexture(Dialog_button_cancel_released), getPlugTexture(Dialog_button_cancel_pressed), 
                                            getPlugTexture(Dialog_button_cancel_released), getPlugTexture(Dialog_button_cancel_pressed), 
                                            BaseLayoutBox(Dialog_button_cancel_pos, Dialog_button_size, Dialog_window_size, false, true),
                                            new Click(m_delete_canvas));

            Button *close_btn = new Button( getPlugTexture(Dialog_button_no_released), getPlugTexture(Dialog_button_no_pressed), 
                                            getPlugTexture(Dialog_button_no_released), getPlugTexture(Dialog_button_no_pressed), 
                                            BaseLayoutBox(Dialog_button_no_pos, Dialog_button_size, Dialog_window_size, false, true),
                                            new CloseCanvasWithoutSave(*this));

            Button *confirm_btn = new Button( getPlugTexture(Dialog_button_yes_released), getPlugTexture(Dialog_button_yes_pressed), 
                                            getPlugTexture(Dialog_button_yes_released), getPlugTexture(Dialog_button_yes_pressed), 
                                            BaseLayoutBox(Dialog_button_yes_pos, Dialog_button_size, Dialog_window_size, false, true),
                                            new CloseCanvasWithSave(*this));

            m_dialog_window->insertWidget(window);
            m_dialog_window->insertWidget(cancel_btn);
            m_dialog_window->insertWidget(close_btn);
            m_dialog_window->insertWidget(confirm_btn);
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

        virtual void onEvent(const plug::Event &event, plug::EHC &context);

        virtual void onParentUpdate(const plug::LayoutBox &parent_box);

        void createCanvas(  ToolPalette &tool_palette, FilterPalette &filter_palette,
                            plug::ColorPalette &color_palette, const char *file_path = nullptr);

        plug::Widget* getActiveCanvas(void);

        CanvasManager(const CanvasManager &other) = delete;
        CanvasManager &operator= (const CanvasManager &other) = delete;

    protected:    

        virtual void onTick             (const plug::TickEvent &event, plug::EHC &context);

        virtual void onMouseMove        (const plug::MouseMoveEvent &event, plug::EHC &context);
        virtual void onMousePressed     (const plug::MousePressedEvent &event, plug::EHC &context);
        virtual void onMouseReleased    (const plug::MouseReleasedEvent &event, plug::EHC &context);

        virtual void onKeyboardPressed  (const plug::KeyboardPressedEvent &event, plug::EHC &context);
        virtual void onKeyboardReleased (const plug::KeyboardReleasedEvent &event, plug::EHC &context);
        
    private:
        Container<Widget*> m_widgets;
        Container<plug::Canvas*> m_canvases;

        size_t m_cnt_canvas;
        bool m_delete_canvas;

        ContainerWidget *m_dialog_window;
}; 


#endif