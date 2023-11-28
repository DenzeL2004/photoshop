#include "Scrollbar.h"

#include <cstdio>

void Scrollbar::draw(plug::TransformStack &stack, plug::RenderTarget &target)
{
    plug::Transform trf(getLayoutBox().getPosition(), Default_scale);
    stack.enter(trf);

    if (m_update_center_button)
    {
        resizeCenter();
        moveCenter();

        m_update_center_button = false;
    }

    m_top_button->draw(stack, target);
    m_bottom_button->draw(stack, target);
    m_center_button->draw(stack, target);

    stack.leave();
}

void Scrollbar::onMouseMove(const plug::MouseMoveEvent &event, plug::EHC &context)
{
    plug::Transform trf(getLayoutBox().getPosition(), Default_scale);
    context.stack.enter(trf);

    context.stopped = false;

    plug::Vec2d local_pos = context.stack.restore(event.pos);

    if (m_center_button->m_prev_state == Button::ButtonState::PRESSED ||
        m_center_button->m_state == Button::ButtonState::PRESSED)
    {
        plug::Vec2d canvas_pos = m_canvas_view.getCanvasPos();

        plug::Vec2d scrollbar_size = getLayoutBox().getSize() - m_top_button->getLayoutBox().getSize() - m_bottom_button->getLayoutBox().getSize();

        plug::Vec2d offset = local_pos - m_hold_pos;

        if (m_type == Scrollbar::Type::HORIZONTAL)
        {
            m_canvas_view.setCanvasPos(plug::Vec2d(m_prev_canvas_pos.x + offset.x * m_canvas_view.getCanvasSize().x / scrollbar_size.x, canvas_pos.y));
            m_update_center_button = true;
        }

        if (m_type == Scrollbar::Type::VERTICAL)
        {
            m_canvas_view.setCanvasPos(plug::Vec2d(canvas_pos.x, m_prev_canvas_pos.y + offset.y * m_canvas_view.getCanvasSize().y / scrollbar_size.y));
            m_update_center_button = true;
        }
    }

    if (!context.stopped)
    {
        m_top_button->onEvent(event, context);
        m_bottom_button->onEvent(event, context);
        m_center_button->onEvent(event, context);
    }

    context.stack.leave();
}

void Scrollbar::moveCenter(void)
{
    plug::Vec2d canvas_size = m_canvas_view.getCanvasSize();
    plug::Vec2d canvas_pos = m_canvas_view.getCanvasPos();

    double cf_x = canvas_pos.x / canvas_size.x;
    double cf_y = canvas_pos.y / canvas_size.y;

    plug::Vec2d center_button_pos = m_center_button->getLayoutBox().getPosition();

    plug::Vec2d scrollbar_size = getLayoutBox().getSize() - m_top_button->getLayoutBox().getSize() - m_bottom_button->getLayoutBox().getSize();

    if (m_type == Scrollbar::Type::HORIZONTAL)
        center_button_pos = plug::Vec2d(cf_x * scrollbar_size.x + m_top_button->getLayoutBox().getSize().x, center_button_pos.y);

    if (m_type == Scrollbar::Type::VERTICAL)
        center_button_pos = plug::Vec2d(center_button_pos.x, cf_y * scrollbar_size.y + m_top_button->getLayoutBox().getSize().y);

    m_center_button->getLayoutBox().setPosition(center_button_pos);
}

void Scrollbar::resizeCenter(void)
{
    plug::Vec2d canvas_size = m_canvas_view.getCanvasSize();

    double cf_x = std::min(1.0, getLayoutBox().getSize().x / canvas_size.x);
    double cf_y = std::min(1.0, getLayoutBox().getSize().y / canvas_size.y);

    plug::Vec2d center_button_size = m_center_button->getLayoutBox().getSize();

    plug::Vec2d scrollbar_size = getLayoutBox().getSize() - m_top_button->getLayoutBox().getSize() - m_bottom_button->getLayoutBox().getSize();

    if (m_type == Scrollbar::Type::HORIZONTAL)
        center_button_size = plug::Vec2d(cf_x * scrollbar_size.x, center_button_size.y);

    if (m_type == Scrollbar::Type::VERTICAL)
        center_button_size = plug::Vec2d(center_button_size.x, cf_y * scrollbar_size.y);

    m_center_button->getLayoutBox().setSize(center_button_size);
}

void Scrollbar::onMousePressed(const plug::MousePressedEvent &event, plug::EHC &context)
{
    plug::Transform trf(getLayoutBox().getPosition(), Default_scale);
    context.stack.enter(trf);

    m_prev_canvas_pos = m_canvas_view.getCanvasPos();

    context.stopped = covers(context.stack, event.pos);

    if (context.stopped)
    {
        context.stopped = false;
        m_top_button->onEvent(event, context);
        m_bottom_button->onEvent(event, context);
        m_center_button->onEvent(event, context);
        
        plug::Vec2d local_pos = context.stack.restore(event.pos);

        m_hold_pos = local_pos;

        if (!context.stopped)
        {
            plug::Vec2d offset = local_pos - m_center_button->getLayoutBox().getPosition();

            if (m_type == Scrollbar::Type::HORIZONTAL)
                offset.y = 0.0;
            if (m_type == Scrollbar::Type::VERTICAL)
                offset.x = 0.0;

            if (offset.x < -Eps || offset.y < -Eps)
                m_top_button->doAction();

            if (offset.x > Eps || offset.y > Eps)
                m_bottom_button->doAction();

            context.stopped = true;
            m_update_center_button = true;
        }
    }

    context.stack.leave();
}

void Scrollbar::onMouseReleased(const plug::MouseReleasedEvent &event, plug::EHC &context)
{
    plug::Transform trf(getLayoutBox().getPosition(), Default_scale);
    context.stack.enter(trf);

    m_hold_pos = plug::Vec2d(0.0, 0.0);

    m_top_button->onEvent(event, context);
    m_bottom_button->onEvent(event, context);
    m_center_button->onEvent(event, context);

    context.stopped = false;

    context.stack.leave();
}

void Scrollbar::onParentUpdate(const plug::LayoutBox &parent_box)
{
    plug::LayoutBox &box = getLayoutBox();
    plug::Vec2d size = box.getSize();

    box.onParentUpdate(parent_box);

    if (m_type == Scrollbar::Type::VERTICAL)
        box.setSize(plug::Vec2d(size.x, box.getSize().y));

    if (m_type == Scrollbar::Type::HORIZONTAL)
        box.setSize(plug::Vec2d(box.getSize().x, size.y));

    m_top_button->onParentUpdate(box);
    m_bottom_button->onParentUpdate(box);
    m_center_button->onParentUpdate(box);

    m_update_center_button = true;
}

void Scrollbar::onKeyboardPressed(const plug::KeyboardPressedEvent &event, plug::EHC &context)
{
    if (m_type == Scrollbar::Type::VERTICAL)
    {
        if (event.key_id == plug::KeyCode::Up)
        {
            m_top_button->doAction();
            m_update_center_button = true;
        }

        if (event.key_id == plug::KeyCode::Down)
        {
            m_bottom_button->doAction();
            m_update_center_button = true;
        }
    }

    if (m_type == Scrollbar::Type::HORIZONTAL)
    {
        if (event.key_id == plug::KeyCode::Left)
        {
            m_top_button->doAction();
            m_update_center_button = true;
        }

        if (event.key_id == plug::KeyCode::Right)
        {
            m_bottom_button->doAction();
            m_update_center_button = true;
        }
    }
}

void Scrollbar::onKeyboardReleased(const plug::KeyboardReleasedEvent &event, plug::EHC &context)
{}