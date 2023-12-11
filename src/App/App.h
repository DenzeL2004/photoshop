#ifndef _APP_H_
#define _APP_H_

#include "Plug/Math.h"
#include "Impl/Util/Sfml.h"

#include "Impl/RenderTarget/SfmlRenderTarget/RenderTarget.h"
#include "Impl/Graphic/Graphic.h"

#include "Impl/TransformStack/TransformStack.h"

#include "Impl/LayoutBox/BaseLayoutBox/BaseLayoutBox.h"
#include "Impl/Widget/Widget.h"
#include "Impl/Widget/Window/Window.h"
#include "Impl/Widget/Frame/Frame.h"
#include "Impl/Widget/Button/Button.h"
#include "Impl/Widget/TextBox/TextBox.h"
#include "Impl/Widget/EntryField/EntryField.h"

#include "Impl/Canvas/Canvas.h"
#include "Impl/Widget/CanvasManager/CanvasManager.h"

#include "Impl/Widget/Clock/Clock.h"

#include "Impl/Tool/ColorPalette/ColorPalette.h"
#include "Impl/Tool/FilterPalette/FilterPalette.h"

#include "Impl/Tool/ToolPalette/ToolPalette.h"
#include "Impl/Widget/ColorField/ColorField.h"
#include "Impl/Widget/ColorView/ColorView.h"

#include "AppConfig.h"


class AppWidget : public ContainerWidget
{
    public:

        AppWidget();

        virtual ~AppWidget()
        {
            size_t cnt = m_plugin_list.getSize();
            for (size_t it = 0; it < cnt; it++)
            {
                if (m_plugin_list[it])
                {
                    m_plugin_list[it]->release();
                }
            }
        }

        virtual void draw(plug::TransformStack &stack, plug::RenderTarget &target);

        virtual void onEvent(const plug::Event &event, plug::EHC &context);

        void createNewCanvas(const char *file_path = nullptr);

        AppWidget(const AppWidget &other) = delete;
        AppWidget &operator= (const AppWidget &other) = delete;

    protected:

        // virtual void onTick             (const plug::TickEvent &event, plug::EHC &context);

        // virtual void onMouseMove        (const plug::MouseMoveEvent &event, plug::EHC &context);
        // virtual void onMousePressed     (const plug::MousePressedEvent &event, plug::EHC &context);
        // virtual void onMouseReleased    (const plug::MouseReleasedEvent &event, plug::EHC &context);

        virtual void onKeyboardPressed  (const plug::KeyboardPressedEvent &event, plug::EHC &context);
        // virtual void onKeyboardReleased (const plug::KeyboardReleasedEvent &event, plug::EHC &context);

    private:

        void AddFiltersButtons(void);
        void AddFileButtons(void);
        void AddToolsButtons(void);
        
        Container <plug::Plugin*> m_plugin_list;

        FilterPalette m_filter_palette;
        ColorPalette  m_color_palette;
        ToolPalette  m_tool_palette;

        size_t m_canvas_manager_id;
};


class LoadImage : public Action
{
    public:

        LoadImage(AppWidget &app_widget):m_app_widget(app_widget){}
        ~LoadImage(){}

        void operator()()
        {
            plug::Vec2d size = m_app_widget.getLayoutBox().getSize();

            EntryField *entry_window = new EntryField(  BaseLayoutBox((size - Dialog_window_size) / 2, 
                                                        Dialog_window_size, 
                                                        size, false, false));

            Button *cancel_btn = new Button(getPlugTexture(Dialog_button_cancel_released), getPlugTexture(Dialog_button_cancel_pressed), 
                                            getPlugTexture(Dialog_button_cancel_released), getPlugTexture(Dialog_button_cancel_pressed), 
                                            BaseLayoutBox(Entry_button_cancel_pos, Dialog_button_size, Dialog_window_size, false, true),
                                            new EraseLastWidget(m_app_widget));

            Button *confirm_btn = new Button(getPlugTexture(Dialog_button_confirm_released), getPlugTexture(Dialog_button_confirm_pressed), 
                                            getPlugTexture(Dialog_button_confirm_released), getPlugTexture(Dialog_button_confirm_pressed), 
                                            BaseLayoutBox(Entry_button_confirm_pos, Dialog_button_size, Dialog_window_size, false, true),
                                            new LoadImage::AddImage(m_app_widget, *entry_window));

            entry_window->insertWidget(cancel_btn);
            entry_window->insertWidget(confirm_btn);

            m_app_widget.insertWidget(entry_window);
        }

        LoadImage(const LoadImage &other) = delete;
        LoadImage &operator= (const LoadImage &other) = delete;

    private:

        class AddImage : public Action
        {
            public:
                
                AddImage(AppWidget &app_widget, EntryField &entry_field):
                        m_app_widget(app_widget), m_entry_field(entry_field){}
                ~AddImage(){}
            
                void operator()()
                {
                    m_app_widget.createNewCanvas(m_entry_field.getString());
                    m_app_widget.eraseWidget();
                }

                AddImage(const AddImage &other) = delete;
                AddImage &operator= (const AddImage &other) = delete;


            private:
                AppWidget &m_app_widget;
                EntryField &m_entry_field;
        };

        AppWidget &m_app_widget;
};

class AddNewCanvas : public Action
{
    public:

        AddNewCanvas(AppWidget &app_widget):m_app_widget(app_widget){}
        ~AddNewCanvas(){}

        void operator()()
        {
            m_app_widget.createNewCanvas();
        }

        AddNewCanvas(const AddNewCanvas &other) = delete;
        AddNewCanvas &operator= (const AddNewCanvas &other) = delete;

    private:

        AppWidget &m_app_widget;
};

class ApplyFilter : public Action
{
    public:

        ApplyFilter(plug::Widget &widget, size_t type):
                    m_widget(widget),
                    m_type(type){}
        ~ApplyFilter(){}

        void operator()()
        {
            TransformStack stack;
            plug::EHC context = {(plug::TransformStack&)stack, false, false};
            m_widget.onEvent(plug::FilterApplyEvent(m_type), context);
        }

        ApplyFilter(const ApplyFilter &other) = delete;
        ApplyFilter &operator= (const ApplyFilter &other) = delete;

    private:

        plug::Widget &m_widget;
        size_t m_type;
};

class ChooseToolAction : public Action
{
    public:

        ChooseToolAction(plug::Widget &widget, size_t type):
                    m_widget(widget),
                    m_type(type){}
        ~ChooseToolAction(){}

        void operator()()
        {
            TransformStack stack;
            plug::EHC context = {(plug::TransformStack&)stack, false, false};
            m_widget.onEvent(plug::ToolChooseEvent(m_type), context);
        }

        ChooseToolAction(const ChooseToolAction &other) = delete;
        ChooseToolAction &operator= (const ChooseToolAction &other) = delete;

    private:

        plug::Widget &m_widget;
        size_t m_type;
};


void useApp();

#endif