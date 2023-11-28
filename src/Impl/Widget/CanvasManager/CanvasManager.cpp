#include "CanvasManager.h"


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
    for (int it = size - 1; it >= 0; it--)
    {
        //m_widgets[it]->onEvent(false);
    }

    context.stopped = false;
    for (int it = size - 1; it >= 0; it--)
    {
        m_delete_canvas = false;
        m_widgets[it]->onEvent(event, context);
        
        if (context.stopped)
        {
            m_widgets.drown(it);
            m_canvases.drown(it);
            
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

// void CanvasManager::createCanvas(ToolPalette *tool_palette, FilterPalette *filter_palette)
// {
//     assert(tool_palette != nullptr && "tool_palette is nullptr");
//     assert(filter_palette != nullptr && "filter_palette is nullptr");

//     char *buf = (char*)calloc(BUFSIZ, sizeof(char));
//     if (!buf)
//     {
//         PROCESS_ERROR(ERR_MEMORY_ALLOC, "allocate memory to buf failed\n");
//         return;
//     }

//     m_cnt_canvas++;
//     sprintf(buf, "canvas %lu", m_cnt_canvas);

//     Frame *frame = new Frame(   "src/img/frame.png", Title(Title_offset, buf, sf::Color::Black), 
//                                 Frame_size, Frame_pos, this);

//     Button *close_btn = new Button( Cross_Button_Release, Cross_Button_Covered, 
//                                     Cross_Button_Release, Cross_Button_Covered, 
//                                     new Click(&m_delete_canvas), 
//                                     Close_button_size, Close_button_pos, frame);

//     Canvas *canvas = new Canvas(    tool_palette, filter_palette, Canvas_size,
//                                     Canvas_view_size, Canvas_pos, frame);

//     m_canvases.pushBack(canvas);

    
//     Scrollbar *scroll_hor = new Scrollbar(  canvas, Scrollbar::Type::HORIZONTAL, 
//                                             Scroll_hor_size, Scroll_hor_pos, frame);

//     Button *left_btn = new Button(  Left_Scl_Rel, Left_Scl_Prs, Left_Scl_Rel, Left_Scl_Prs,
//                                     new ScrollCanvas(Dot(-5.0, 0.0), canvas), 
//                                     Buttons_scroll_size, Left_pos, scroll_hor);

//     Button *right_btn = new Button( Right_Scl_Rel, Right_Scl_Prs, Right_Scl_Rel, Right_Scl_Prs, 
//                                     new ScrollCanvas(Vec2d(5.0, 0.0), canvas), 
//                                     Buttons_scroll_size, Right_pos, scroll_hor);

//     Button *hor_btn = new Button(   Hor_Scl, Hor_Scl, Hor_Scl, Hor_Scl, 
//                                     new ScrollCanvas(Dot(0, 0), canvas), 
//                                     Buttons_scroll_size, Vec2d(0.0, 0.0), scroll_hor);
    
//     Scrollbar *scroll_ver = new Scrollbar(  canvas, Scrollbar::Type::VERTICAL, 
//                                             Scroll_ver_size, Scroll_ver_pos, frame);

//     Button *up_btn = new Button(    Up_Scl_Rel, Up_Scl_Prs, Up_Scl_Rel, Up_Scl_Prs, 
//                                     new ScrollCanvas(Dot(0.0, -5.0), canvas), 
//                                     Buttons_scroll_size, Up_pos, scroll_ver);

//     Button *down_btn = new Button(  Down_Scl_Rel, Down_Scl_Prs, Down_Scl_Rel, Down_Scl_Prs, 
//                                     new ScrollCanvas(Vec2d(0.0, 5.0), canvas), 
//                                     Buttons_scroll_size, Down_pos, scroll_ver);

//     Button *ver_btn = new Button(   Ver_Scl, Ver_Scl, Ver_Scl, Ver_Scl, 
//                                     new ScrollCanvas(Dot(0, 0), canvas), 
//                                     Buttons_scroll_size, Vec2d(0.0, 0.0), scroll_ver);


//     scroll_hor->addButtons(left_btn, right_btn, hor_btn);
//     scroll_ver->addButtons(up_btn, down_btn, ver_btn);

//     frame->addWidget(close_btn);
//     frame->addWidget(scroll_hor);
//     frame->addWidget(scroll_ver);
//     frame->addWidget(canvas);
    
//     frame->onUpdate(getLayoutBox());

//     m_widgets.pushBack(frame);
// }

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
