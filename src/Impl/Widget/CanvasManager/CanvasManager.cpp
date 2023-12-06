#include "CanvasManager.h"

#include <cstdio>

void CanvasManager::draw(plug::TransformStack &stack, plug::RenderTarget &target)
{
    plug::Transform trf(getLayoutBox().getPosition(), Default_scale);
    stack.enter(trf);

    size_t size = m_widgets.getSize();
    for (size_t it = 0; it < size; it++)
    {
        m_widgets[it]->draw(stack, target);
    }

    if (m_delete_canvas)
    {
        m_dialog_window->draw(stack, target);
    }

    stack.leave();
}

void CanvasManager::onMouseMove(const plug::MouseMoveEvent &event, plug::EHC &context)
{
    if (context.stopped) return;

    context.stopped = false;
    
    plug::Transform trf(getLayoutBox().getPosition(), Default_scale);
    context.stack.enter(trf);

    if (m_delete_canvas)
    {
        m_dialog_window->onEvent(event, context);
        return;
    }

    int size = static_cast<int>(m_widgets.getSize());
    m_widgets[size - 1]->onEvent(event, context);

    context.stack.leave();
}

void CanvasManager::onMousePressed(const plug::MousePressedEvent &event, plug::EHC &context)
{
    if (context.stopped) return;

    int size = static_cast<int>(m_widgets.getSize());

    plug::Transform trf(getLayoutBox().getPosition(), Default_scale);
    context.stack.enter(trf);

    if (m_delete_canvas)
    {
        m_dialog_window->onEvent(event, context);
        return;
    }

    for (int it = size - 2; it >= 0; it--)
    {
        m_widgets[it]->onEvent(plug::FocuseEvent(false), context);
    }

    context.stopped = false;
    for (int it = size - 1; it >= 0; it--)
    {
        m_widgets[it]->onEvent(event, context);
        
        if (context.stopped)
        {
            m_widgets[size - 1]->onEvent(plug::FocuseEvent(false), context); 

            m_widgets.drown(it);

            m_widgets[size - 1]->onEvent(plug::FocuseEvent(true), context);            

            context.stopped = true;

            break;
        }
    }

    context.stack.leave();
}

void CanvasManager::onMouseReleased(const plug::MouseReleasedEvent &event, plug::EHC &context)
{
    if (context.stopped) return;

    context.stopped = false;

    plug::Transform trf(getLayoutBox().getPosition(), Default_scale);
    context.stack.enter(trf);

    if (m_delete_canvas)
    {
        m_dialog_window->onEvent(event, context);
        return;
    }

    int size = static_cast<int>(m_widgets.getSize());
    for (int it = size - 1; it >= 0; it--)
    {
        m_widgets[it]->onEvent(event, context);
    }

    context.stack.leave();
}

void CanvasManager::onKeyboardPressed(const plug::KeyboardPressedEvent &event, plug::EHC &context)
{
    if (context.stopped) return;
    
    context.stopped = false;

    plug::Transform trf(getLayoutBox().getPosition(), Default_scale);
    context.stack.enter(trf);

    if (m_delete_canvas)
    {
        m_dialog_window->onEvent(event, context);
        return;
    }

    int size = static_cast<int>(m_widgets.getSize());
    m_widgets[size - 1]->onEvent(event, context);

    context.stack.leave();
}

void CanvasManager::onKeyboardReleased(const plug::KeyboardReleasedEvent &event, plug::EHC &context)
{
    if (context.stopped) return;

    context.stopped = false;

    plug::Transform trf(getLayoutBox().getPosition(), Default_scale);
    context.stack.enter(trf);

    if (m_delete_canvas)
    {
        m_dialog_window->onEvent(event, context);
        return;
    }

    int size = static_cast<int>(m_widgets.getSize());
    m_widgets[size - 1]->onEvent(event, context);

    context.stack.leave();
}

void CanvasManager::onTick(const plug::TickEvent &event, plug::EHC &context)
{
    if (context.stopped) return;

    context.stopped = false;

    plug::Transform trf(getLayoutBox().getPosition(), Default_scale);
    context.stack.enter(trf);

    if (m_delete_canvas)
    {
        m_dialog_window->onEvent(event, context);
        return;
    }

    int size = static_cast<int>(m_widgets.getSize());
    m_widgets[size - 1]->onEvent(event, context);

    context.stack.leave();
}


void CanvasManager::onEvent(const plug::Event &event, plug::EHC &context)
{
    if (context.stopped) return;

    size_t size = m_widgets.getSize(); 
    if (size == 0) return;

    size_t event_type = event.getType();

    switch (event_type)
    {
        case plug::SaveCanvas:  case plug::FilterApply:
        case plug::ToolChoose: 
        {
            m_widgets[size - 1]->onEvent(event, context);
        }
        break;
        
        default:
            Widget::onEvent(event, context);
            break;
    }
}

void CanvasManager::createCanvas(ToolPalette &tool_palette, FilterPalette &filter_palette,
                                 plug::ColorPalette &color_palette, const char *file_path)
{
    char *buf = new char[BUFSIZ];
    if (!buf)
    {
        PROCESS_ERROR(ERR_MEMORY_ALLOC, "allocate memory to buf failed\n");
        return;
    }

    m_cnt_canvas++;
    sprintf(buf, "CANVAS %lu", m_cnt_canvas);

    Frame *frame = new Frame(   getPlugTexture(Canvas_frame_texture), 
                                Title(Canvas_frame_title_pos, buf, 2.0, Canvas_frame_title_color), 
                                BaseLayoutBox(Canvas_frame_pos, Canvas_frame_size, getLayoutBox().getSize(), true, true), this);

    delete[] buf;

    Button *close_btn = new Button( getPlugTexture(Cross_button_released), getPlugTexture(Cross_button_pressed), 
                                    getPlugTexture(Cross_button_released), getPlugTexture(Cross_button_pressed), 
                                    BaseLayoutBox(Vec2d(Canvas_frame_size.x - Cross_button_size.x, 0), Cross_button_size, Canvas_frame_size, false, true),
                                    new Click(m_delete_canvas));

    Canvas *canvas = nullptr;

    if (file_path)
    {
        canvas = new Canvas(file_path);
    }
    else
    {
        canvas = new Canvas(Default_canvas_width, Default_canvas_height, color_palette.getBGColor());
    }

    m_canvases.pushBack(canvas);

    
    CanvasView *canvas_view = new CanvasView(  *canvas, tool_palette, filter_palette, color_palette,
                                                BaseLayoutBox(Canvas_view_pos, Canvas_view_size, Canvas_frame_size, true, true));

    Scrollbar *scroll_ver = new Scrollbar(  *canvas_view, Scrollbar::Type::VERTICAL, 
                                            BaseLayoutBox(Vec2d(Canvas_frame_size.x - 30, 80), Vec2d(25, Canvas_view_size.y), Canvas_frame_size, true, true),
                                            Scrollbar_up_released, Scrollbar_up_pressed,
                                            Scrollbar_down_released, Scrollbar_down_pressed,
                                            Scrollbar_released, Scrollbar_pressed);

    Scrollbar *scroll_hor = new Scrollbar(  *canvas_view, Scrollbar::Type::HORIZONTAL, 
                                            BaseLayoutBox(Vec2d(5, 50), Vec2d(Canvas_view_size.x, 25), Canvas_frame_size, true, true),
                                            Scrollbar_left_released, Scrollbar_left_pressed,
                                            Scrollbar_right_released, Scrollbar_right_pressed,
                                            Scrollbar_released, Scrollbar_pressed);

    
    frame->addWidget(canvas_view);
    frame->addWidget(scroll_hor);
    frame->addWidget(scroll_ver);
    frame->addWidget(close_btn);

    frame->onParentUpdate(getLayoutBox());

    m_widgets.pushBack(frame);
}

void CanvasManager::onParentUpdate(const plug::LayoutBox &parent_box)
{
    plug::LayoutBox *layout_box =  &getLayoutBox();
    layout_box->onParentUpdate(parent_box);
    
    size_t cnt = m_widgets.getSize();
    for (size_t it = 0; it < cnt; it++)
    {
        m_widgets[it]->onParentUpdate(*layout_box);
    }
}

plug::Widget* CanvasManager::getActiveCanvas(void)
{
    size_t size = m_widgets.getSize();
    if (size == 0)
        return nullptr;

    return m_widgets[size - 1];
}

void CloseCanvasWithoutSave::operator()()
{
    if (m_canvas_manager.m_delete_canvas)
    {
        m_canvas_manager.m_widgets.popBack();
        m_canvas_manager.m_canvases.popBack();
        m_canvas_manager.m_delete_canvas = false;
    }
}

void CloseCanvasWithSave::operator()()
{
    ContainerWidget *entry_window = new ContainerWidget(BaseLayoutBox(plug::Vec2d(0, 0), Dialog_window_size, 
                                                        m_canvas_manager.m_dialog_window->getLayoutBox().getSize(), false, false));

    Window *window = new Window(getPlugTexture(Entry_window_texture),
                                Title(Filt_path_title_pos, File_path_name, Entry_title_scale, Canvas_dialog_title_color),
                                BaseLayoutBox(Entry_window_pos, Entry_window_size, entry_window->getLayoutBox().getSize(), false, false));

    Window *entry_field = new Window(getPlugTexture(Entry_field_texture),
                                Title(),
                                BaseLayoutBox(Entry_field_pos, Entry_field_size, entry_window->getLayoutBox().getSize(), false, false));


    Button *cancel_btn = new Button(getPlugTexture(Dialog_button_cancel_released), getPlugTexture(Dialog_button_cancel_pressed), 
                                    getPlugTexture(Dialog_button_cancel_released), getPlugTexture(Dialog_button_cancel_pressed), 
                                    BaseLayoutBox(Entry_button_cancel_pos, Dialog_button_size, Dialog_window_size, false, true),
                                    new EraseLastWidget(*m_canvas_manager.m_dialog_window));

    Button *confirm_btn = new Button(getPlugTexture(Dialog_button_confirm_released), getPlugTexture(Dialog_button_confirm_pressed), 
                                     getPlugTexture(Dialog_button_confirm_released), getPlugTexture(Dialog_button_confirm_pressed), 
                                     BaseLayoutBox(Entry_button_confirm_pos, Dialog_button_size, Dialog_window_size, false, true),
                                     new CloseCanvasWithSave::SaveCanvas(m_canvas_manager));

    TextBox *text_box = new TextBox(30, Entry_title_scale, BaseLayoutBox(Entry_field_pos + plug::Vec2d(40, 25), Entry_field_size, entry_window->getLayoutBox().getSize(), false, false));
    text_box->setColor(plug::White);

    entry_window->insertWidget(window);
    entry_window->insertWidget(entry_field);
    entry_window->insertWidget(cancel_btn);
    entry_window->insertWidget(confirm_btn);
    entry_window->insertWidget(text_box);

    m_canvas_manager.m_dialog_window->insertWidget(entry_window);
}   

void CloseCanvasWithSave::SaveCanvas::operator()()
{
    ContainerWidget *entery_window = static_cast<ContainerWidget*>(m_canvas_manager.m_dialog_window->getLastWidget());
    TextBox *text_box = static_cast<TextBox*>(entery_window->getLastWidget());

    m_canvas_manager.m_delete_canvas = false;    

    TransformStack stack;
    plug::EHC context = {(plug::TransformStack&)stack, false, false};
    m_canvas_manager.onEvent(plug::SaveEvent(text_box->getString()), context);

    m_canvas_manager.m_dialog_window->eraseWidget();
    m_canvas_manager.m_widgets.popBack();
}