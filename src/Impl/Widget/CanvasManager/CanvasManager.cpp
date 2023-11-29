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

    stack.leave();
}

void CanvasManager::onMouseMove(const plug::MouseMoveEvent &event, plug::EHC &context)
{
    size_t size = m_widgets.getSize();
    if (size == 0)
    {
        context.stopped = false;
        return;
    }

    plug::Transform trf(getLayoutBox().getPosition(), Default_scale);
    context.stack.enter(trf);
    
    m_widgets[size - 1]->onEvent(event, context);

    context.stack.leave();
}

void CanvasManager::onMousePressed(const plug::MousePressedEvent &event, plug::EHC &context)
{
    plug::Transform trf(getLayoutBox().getPosition(), Default_scale);
    context.stack.enter(trf);

    int size = static_cast<int>(m_widgets.getSize());
    for (int it = size - 2; it >= 0; it--)
    {
        m_widgets[it]->onEvent(plug::FocuseEvent(false), context);
    }

    context.stopped = false;
    for (int it = size - 1; it >= 0; it--)
    {
        m_delete_canvas = false;
        m_widgets[it]->onEvent(event, context);
        
        if (context.stopped)
        {
            m_widgets[size - 1]->onEvent(plug::FocuseEvent(false), context); 

            m_widgets.drown(it);
            m_canvases.drown(it);

            m_widgets[size - 1]->onEvent(plug::FocuseEvent(true), context);            
            
            if (m_delete_canvas)
            {
                m_widgets.popBack();
                m_canvases.popBack();
            }

            context.stopped = true;

            break;
        }
    }

    context.stack.leave();
}

void CanvasManager::onMouseReleased(const plug::MouseReleasedEvent &event, plug::EHC &context)
{
    plug::Transform trf(getLayoutBox().getPosition(), Default_scale);
    context.stack.enter(trf);

    context.stopped = false;

    int size = static_cast<int>(m_widgets.getSize());
    for (int it = size - 1; it >= 0; it--)
    {
        m_widgets[it]->onEvent(event, context);
    }

    context.stack.leave();
}

void CanvasManager::onKeyboardPressed(const plug::KeyboardPressedEvent &event, plug::EHC &context)
{
    size_t size = m_widgets.getSize();
    if (size == 0)
    {
        context.stopped = false;
        return;
    }

    plug::Transform trf(getLayoutBox().getPosition(), Default_scale);
    context.stack.enter(trf);

    m_widgets[size - 1]->onEvent(event, context);

    context.stack.leave();
}

void CanvasManager::onKeyboardReleased(const plug::KeyboardReleasedEvent &event, plug::EHC &context)
{
    size_t size = m_widgets.getSize();
    if (size == 0)
    {
        context.stopped = false;
        return;
    }

    plug::Transform trf(getLayoutBox().getPosition(), Default_scale);
    context.stack.enter(trf);

    m_widgets[size - 1]->onEvent(event, context);

    context.stack.leave();
}

void CanvasManager::onTick(const plug::TickEvent &event, plug::EHC &context)
{
   size_t size = m_widgets.getSize();
    if (size == 0)
    {
        context.stopped = false;
        return;
    }

    plug::Transform trf(getLayoutBox().getPosition(), Default_scale);
    context.stack.enter(trf);

    m_widgets[size - 1]->onEvent(event, context);

    context.stack.leave();
}

void CanvasManager::createCanvas(const char *file_path)
{
    // assert(tool_palette != nullptr && "tool_palette is nullptr");
    // assert(filter_palette != nullptr && "filter_palette is nullptr");

    char *buf = new char[BUFSIZ];
    if (!buf)
    {
        PROCESS_ERROR(ERR_MEMORY_ALLOC, "allocate memory to buf failed\n");
        return;
    }

    m_cnt_canvas++;
    sprintf(buf, "CANVAS %lu", m_cnt_canvas);

    Frame *frame = new Frame(   getPlugTexture(Canvas_frame_texture), 
                                Title(Canvas_frame_title_pos, buf, 2.0, plug::Black), 
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
        canvas = new Canvas(Default_canvas_width, Default_canvas_height);
    }

    m_canvases.pushBack(canvas);

    
    CanvasView *canvas_view = new CanvasView(  *canvas, 
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

Canvas* CanvasManager::getActiveCanvas(void)
{
    size_t size = m_canvases.getSize();
    if (size == 0)
        return nullptr;

    return m_canvases[size - 1];
}
