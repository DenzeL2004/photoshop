#include "Frame.h"
#include "Impl/Graphic/Graphic.h"

const Vec2d Offset_Title = Vec2d(0.45, 0.0);
const double Tittle_size  = 1.9;

const double Border_width = 10.0;

//=================================================================================================

void Frame::draw(plug::TransformStack &stack, plug::RenderTarget &target)
{
    Window::draw(stack, target);
    
    Transform trf(getLayoutBox().getPosition(), m_scale);
    stack.enter(trf);

    Vec2d abs_pos = stack.apply(Vec2d(0.0, 0.0)) + m_title.pos;

    writeText(target, abs_pos, m_title.msg, m_title.width, m_title.color);

    size_t cnt = m_widgets.getSize();
    for (size_t it = 0; it < cnt; it++)
    {
        m_widgets[it]->draw(stack, target);
    }

    stack.leave();
}

void Frame::onParentUpdate(const plug::LayoutBox &parent_box)
{
    plug::LayoutBox *layout_box =  &getLayoutBox();
    layout_box->onParentUpdate(parent_box);
    
    size_t cnt = m_widgets.getSize();
    for (size_t it = 0; it < cnt; it++)
        m_widgets[it]->onParentUpdate(*layout_box);
}

//=================================================================================================

void Frame::onMouseMove(const plug::MouseMoveEvent &event, plug::EHC &context)
{
    Transform trf(getLayoutBox().getPosition(), m_scale);    
    context.stack.enter(trf);

    Vec2d local_pos = context.stack.restore(event.pos);

    if(state_)
    {
        if (state_ == Borders::TOP)
            moveFrame(local_pos);
        else
            resizeFrame(local_pos);
    }  
    else
    {
        size_t cnt = m_widgets.getSize();
        for (size_t it = 0; it < cnt; it++)
        {
            m_widgets[it]->onEvent(event, context);
        }
    }

    context.stack.leave();
}

//================================================================================
void Frame::clickOnBorder()
{
    Vec2d size = getLayoutBox().getSize();

    state_ = 0;

    if (m_hold_pos.x > Eps && m_hold_pos.x < Border_width - Eps)
        state_ |= Frame::Borders::LEFT;

    if (m_hold_pos.x > size.x - Border_width + Eps && m_hold_pos.x < size.x - Eps)
        state_ |= Frame::Borders::RIGHT;

    if (m_hold_pos.y > size.y - Border_width + Eps && m_hold_pos.y < size.y - Eps)
        state_ |= Frame::Borders::BOTTOM;
}


void Frame::resizeFrame(const Vec2d &local_pos)
{
    plug::LayoutBox* layout_box = &getLayoutBox();

    Vec2d size = layout_box->getSize();

    Vec2d pos = layout_box->getPosition();

    Vec2d delta = local_pos - m_prev_pos;
   
    if (state_ & Frame::Borders::LEFT) 
    {
        if (size.x <= Size_min_limit.x + Eps) return;
            moveFrame(Vec2d(local_pos.x, m_hold_pos.y));
        
        delta.x = pos.x - layout_box->getPosition().x;
    }    

    Vec2d new_size = size;

    if (state_ & Frame::Borders::LEFT || state_ & Frame::Borders::RIGHT)
        new_size += Vec2d(delta.x, 0.0);

    if (state_ & Frame::Borders::BOTTOM)
        new_size += Vec2d(0.0, delta.y);

    if (new_size.x >= Size_min_limit.x + Eps && new_size.y >= Size_min_limit.y + Eps)
    {
        if (m_parent != nullptr)
        {
            Vec2d parent_size = m_parent->getLayoutBox().getSize();
            Vec2d new_pos = layout_box->getPosition();
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


void Frame::moveFrame(const Vec2d &local_pos)
{
    plug::LayoutBox* layout_box = &getLayoutBox();

    Vec2d delta = local_pos - m_hold_pos;
        
    Vec2d new_pos = getLayoutBox().getPosition() + delta;
    
    if (m_parent != nullptr)
    {
        Vec2d parent_size = m_parent->getLayoutBox().getSize();
        Vec2d size = layout_box->getSize();

        if (new_pos.x > Eps && new_pos.x + size.x <= parent_size.x && 
            new_pos.y > Eps && new_pos.y + size.y <= parent_size.y)
        {
            layout_box->setPosition(new_pos);
        }
    }
    else    
        layout_box->setPosition(new_pos);
}

//================================================================================

void Frame::onMousePressed(const plug::MousePressedEvent &event, plug::EHC &context)
{
    Transform trf(getLayoutBox().getPosition(), m_scale);    
    context.stack.enter(trf);

    context.stopped = false;

    size_t cnt = m_widgets.getSize();
    for (size_t it = 0; it < cnt; it++)
    {
        if (!context.stopped) m_widgets[it]->onEvent(event, context);
    }

    if (!context.stopped)
    {
        context.stopped = context.overlapped = covers(context.stack, event.pos); 

        if (context.stopped)
        {
            if (event.button_id == plug::MouseButton::Left)
            {
                m_hold_pos = m_prev_pos = context.stack.restore(event.pos);
                clickOnBorder();

                if (!state_) state_ = Borders::TOP;

                context.stopped = true;
            }
        }
    }

    context.stack.leave();
}

//================================================================================

void Frame::onMouseReleased(const plug::MouseReleasedEvent &event, plug::EHC &context)
{
    Transform trf(getLayoutBox().getPosition(), m_scale);    
    context.stack.enter(trf);

    size_t cnt = m_widgets.getSize();
    for (size_t it = 0; it < cnt; it++)
        m_widgets[it]->onEvent(event, context);

    state_ = DecoratorState::DEFAULT;

    context.stopped = false;

    context.stack.leave();
}

//================================================================================

void Frame::onKeyboardPressed(const plug::KeyboardPressedEvent &event, plug::EHC &context)
{
    Transform trf(getLayoutBox().getPosition(), m_scale);    
    context.stack.enter(trf);

    size_t cnt = m_widgets.getSize();
    for (size_t it = 0; it < cnt; it++)
        m_widgets[it]->onEvent(event, context);

    context.stopped = false;

    context.stack.leave();
}

//================================================================================

void Frame::onKeyboardReleased(const plug::KeyboardReleasedEvent &event, plug::EHC &context)
{
    Transform trf(getLayoutBox().getPosition(), m_scale);    
    context.stack.enter(trf);

    size_t cnt = m_widgets.getSize();
    for (size_t it = 0; it < cnt; it++)
        m_widgets[it]->onEvent(event, context);

    context.stopped = false;

    context.stack.leave();
}

//================================================================================

void Frame::onTick(const plug::TickEvent &event, plug::EHC &context)
{
    Transform trf(getLayoutBox().getPosition(), m_scale);    
    context.stack.enter(trf);

    size_t cnt = m_widgets.getSize();
    for (size_t it = 0; it < cnt; it++)
        m_widgets[it]->onEvent(event, context);

    context.stopped = false;

    context.stack.leave();
} 

//================================================================================

void Frame::addWidget(Widget* widget_ptr)
{
    m_widgets.pushBack(widget_ptr);
}