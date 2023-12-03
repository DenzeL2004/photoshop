#include "Frame.h"
#include "Impl/Graphic/Graphic.h"

const double Border_width = 10.0;

void Frame::draw(plug::TransformStack &stack, plug::RenderTarget &target)
{
    Window::draw(stack, target);
    
    plug::Transform trf(getLayoutBox().getPosition(), Default_scale);
    stack.enter(trf);

    size_t cnt = m_widgets.getSize();
    for (size_t it = 0; it < cnt; it++)
    {
        m_widgets[it]->draw(stack, target);
    }

    stack.leave();
}

void Frame::onEvent(const plug::Event &event, plug::EHC &context)
{
    plug::Transform trf(getLayoutBox().getPosition(), Default_scale);    
    context.stack.enter(trf);

    bool handel_event = false;

    size_t size = m_widgets.getSize();

    for (size_t it = 0; it < size; it++)
    {
        context.stopped = false;
        m_widgets[it]->onEvent(event, context);

        if (context.stopped)
        {
            handel_event = true;
        }
    }

    if (!handel_event)
    {
        Window::onEvent(event, context);
    }

    context.stopped |= handel_event;

    context.stack.leave();
}

void Frame::onParentUpdate(const plug::LayoutBox &parent_box)
{
    plug::LayoutBox *layout_box =  &getLayoutBox();
    layout_box->onParentUpdate(parent_box);
    
    size_t size = m_widgets.getSize();
    for (size_t it = 0; it < size; it++)
        m_widgets[it]->onParentUpdate(*layout_box);
}

void Frame::onMouseMove(const plug::MouseMoveEvent &event, plug::EHC &context)
{
    context.stopped = false;

    plug::Vec2d local_pos = context.stack.restore(event.pos);

    if(m_state)
    {
        if (m_state == Borders::TOP)
            moveFrame(local_pos);
        else
            resizeFrame(local_pos);

        context.stopped = true;
    }  
}

void Frame::clickOnBorder()
{
    plug::Vec2d size = getLayoutBox().getSize();

    m_state = 0;

    if (m_hold_pos.x > Eps && m_hold_pos.x < Border_width - Eps)
        m_state |= Frame::Borders::LEFT;

    if (m_hold_pos.x > size.x - Border_width + Eps && m_hold_pos.x < size.x - Eps)
        m_state |= Frame::Borders::RIGHT;

    if (m_hold_pos.y > size.y - Border_width + Eps && m_hold_pos.y < size.y - Eps)
        m_state |= Frame::Borders::BOTTOM;
}


void Frame::resizeFrame(const plug::Vec2d &local_pos)
{
    plug::LayoutBox* layout_box = &getLayoutBox();

    plug::Vec2d size = layout_box->getSize();

    plug::Vec2d pos = layout_box->getPosition();

    plug::Vec2d delta = local_pos - m_prev_pos;
   
    if (m_state & Frame::Borders::LEFT) 
    {
        if (size.x <= Size_min_limit.x + Eps) return;
            moveFrame(plug::Vec2d(local_pos.x, m_hold_pos.y));
        
        delta.x = pos.x - layout_box->getPosition().x;
    }    

    plug::Vec2d new_size = size;

    if (m_state & Frame::Borders::LEFT || m_state & Frame::Borders::RIGHT)
        new_size += plug::Vec2d(delta.x, 0.0);

    if (m_state & Frame::Borders::BOTTOM)
        new_size += plug::Vec2d(0.0, delta.y);

    if (new_size.x >= Size_min_limit.x + Eps && new_size.y >= Size_min_limit.y + Eps)
    {
        if (m_parent != nullptr)
        {
            plug::Vec2d parent_size = m_parent->getLayoutBox().getSize();
            plug::Vec2d new_pos = layout_box->getPosition();
            if (new_pos.x + new_size.x <= parent_size.x - Eps &&
                new_pos.y + new_size.y <= parent_size.y - Eps)
            {
                layout_box->setSize(new_size);
            }
        }
        else
            layout_box->setSize(new_size);

        m_prev_pos = local_pos;
    }
    else
        layout_box->setPosition(pos);


    size_t cnt = m_widgets.getSize();
    for (size_t it = 0; it < cnt; it++)
    {
       m_widgets[it]->onParentUpdate(*layout_box);
    }
}

void Frame::moveFrame(const plug::Vec2d &local_pos)
{
    plug::LayoutBox* layout_box = &getLayoutBox();

    plug::Vec2d delta = local_pos - m_hold_pos;
        
    plug::Vec2d new_pos = getLayoutBox().getPosition() + delta;
    
    if (m_parent != nullptr)
    {
        plug::Vec2d parent_size = m_parent->getLayoutBox().getSize();
        plug::Vec2d size = layout_box->getSize();

        if (new_pos.x > Eps && new_pos.x + size.x <= parent_size.x && 
            new_pos.y > Eps && new_pos.y + size.y <= parent_size.y)
        {
            layout_box->setPosition(new_pos);
        }
    }
    else    
        layout_box->setPosition(new_pos);
}

void Frame::onMousePressed(const plug::MousePressedEvent &event, plug::EHC &context)
{
    context.stopped = false;

    context.stopped = context.overlapped = covers(context.stack, event.pos); 

    if (context.stopped)
    {
        if (event.button_id == plug::MouseButton::Left)
        {
            m_hold_pos = m_prev_pos = context.stack.restore(event.pos);
            clickOnBorder();

            if (!m_state) m_state = Borders::TOP;
        }
    }
    
}

void Frame::onMouseReleased(const plug::MouseReleasedEvent &event, plug::EHC &context)
{
    m_state = DecoratorState::DEFAULT;
    context.stopped = false;
}

void Frame::onKeyboardPressed(const plug::KeyboardPressedEvent &event, plug::EHC &context)
{
    context.stopped = false;
}

void Frame::onKeyboardReleased(const plug::KeyboardReleasedEvent &event, plug::EHC &context)
{
    context.stopped = false;
}

void Frame::onTick(const plug::TickEvent &event, plug::EHC &context)
{
    context.stopped = false;
} 

void Frame::addWidget(plug::Widget* widget)
{
    m_widgets.pushBack(widget);
}