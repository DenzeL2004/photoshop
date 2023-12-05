#include "Button.h"

#include <cstdio>

void Button::draw(plug::TransformStack &stack, plug::RenderTarget &target)
{
    Transform trf(getLayoutBox().getPosition(), Default_scale);
    stack.enter(trf);
    
    Transform top_trf = stack.top();    

    const plug::Texture *texture = defineTexture();

    if (texture)
    {
        plug::VertexArray vertex_array(plug::Quads, 4);

        vertex_array[0].tex_coords = Vec2d(0, 0);
        vertex_array[1].tex_coords = Vec2d(texture->width, 0);
        vertex_array[2].tex_coords = Vec2d(texture->width, texture->height);
        vertex_array[3].tex_coords = Vec2d(0, texture->height);
        
        Dot pos = top_trf.apply(Vec2d(0, 0));

        Vec2d size = top_trf.getScale() * getLayoutBox().getSize();

        vertex_array[0].position = Vec2d(pos.x, pos.y);
        vertex_array[1].position = Vec2d(pos.x + size.x, pos.y);
        vertex_array[2].position = Vec2d(pos.x + size.x, pos.y + size.y);
        vertex_array[3].position = Vec2d(pos.x, pos.y + size.y);

        target.draw(vertex_array, *texture);
    }

    stack.leave();
}

const plug::Texture* Button::defineTexture() const
{
    switch (m_state)
    {
        case  Button::ButtonState::RELEASED:
            return &m_texture_released;

        case  Button::ButtonState::PRESSED:
            return &m_texture_pressed;
    
        case  Button::ButtonState::DISABLED:
            return &m_texture_disabled;

        case  Button::ButtonState::COVERED:
            return &m_texture_covered;

        default:
            break;
    }

    return nullptr;
}

void Button::onMouseMove(const plug::MouseMoveEvent &event, plug::EHC &context)
{
    if (m_state ==  Button::ButtonState::DISABLED || context.stopped)
        return;

    Transform trf(getLayoutBox().getPosition(), Default_scale);    
    context.stack.enter(trf);

    context.stopped = covers(context.stack, event.pos);

    context.stack.leave();

    if (!context.stopped)
    { 
        m_covering_time = 0;
        m_state = m_prev_state;
    }
    else
    {
        if (m_state !=  Button::ButtonState::COVERED)
        {
            m_prev_state = m_state;
            m_state =  Button::ButtonState::COVERED;
        }
    }
}

void Button::onMousePressed(const plug::MousePressedEvent &event, plug::EHC &context)
{
    if (m_state == Button::ButtonState::DISABLED || context.stopped) return;

    Transform trf(getLayoutBox().getPosition(), Default_scale);    
    context.stack.enter(trf);

    context.stopped = covers(context.stack, event.pos);

    context.stack.leave();
    
    if (context.stopped && event.button_id == plug::MouseButton::Left)
    {    
        doAction();
        m_state = Button::ButtonState::PRESSED;
    }
    else
    {
        context.stopped = false;

        m_state = Button::ButtonState::RELEASED;
        m_prev_state = Button::ButtonState::RELEASED;
    }
}

void Button::onMouseReleased(const plug::MouseReleasedEvent &event, plug::EHC &context)
{
    if (m_state == Button::ButtonState::DISABLED)
        return;

    m_state = Button::ButtonState::RELEASED;
    m_prev_state = Button::ButtonState::RELEASED;
    
    context.stopped = false;
}

void Button::onTick(const plug::TickEvent &event, plug::EHC &context)
{
    m_covering_time += event.delta_time;
}

void Button::doAction(void)
{
    if (m_action) 
        (*m_action)();
}

//================================================================================

void TextButton::draw(plug::TransformStack &stack, plug::RenderTarget &target)
{
    Button::draw(stack, target);

    Transform trf(getLayoutBox().getPosition(), Default_scale);
    stack.enter(trf);


    if (m_state != Button::ButtonState::DISABLED)
    {
        Title &title = m_title_released;
        if (m_state == Button::ButtonState::PRESSED || m_state == Button::ButtonState::COVERED)
        {
            title = m_title_pressed;
        }

        plug::Vec2d abs_pos = stack.apply(plug::Vec2d(0.0, 0.0)) + title.pos;
        writeText(target, abs_pos, title.msg, title.width, title.color);   

    }

    stack.leave();
}

//================================================================================

void ButtonList::draw(plug::TransformStack &stack, plug::RenderTarget &target)
{
    Button::draw(stack, target);

    Transform trf(getLayoutBox().getPosition(), Default_scale);
    stack.enter(trf);
    
    size_t size = m_buttons.getSize();
    for (size_t it = 0; it < size; it++)
    {
        m_buttons[it]->draw(stack, target);
    }

    stack.leave();
}

void ButtonList::onMouseMove(const plug::MouseMoveEvent &event, plug::EHC &context)
{
    if (m_state ==  Button::ButtonState::DISABLED || context.stopped) return;

    plug::Transform trf(getLayoutBox().getPosition(), Default_scale);    
    context.stack.enter(trf);

    context.stopped = covers(context.stack, event.pos);

    if (!context.stopped)
    { 
        m_covering_time = 0;
        m_state = m_prev_state;
    }
    else
    {
        if (m_state !=  Button::ButtonState::COVERED)
        {
            m_prev_state = m_state;
            m_state =  Button::ButtonState::COVERED;
        }
    }

    size_t size = m_buttons.getSize();
    for (size_t it = 0; it < size; it++)
    {
        if (m_prev_state == Button::ButtonState::PRESSED || 
            m_state == Button::ButtonState::COVERED)
        {
            m_buttons[it]->m_state = m_buttons[it]->m_prev_state;
            m_buttons[it]->onEvent(event, context);
        }
        else
        {
            m_buttons[it]->m_state = Button::ButtonState::DISABLED;
        }
    }
    
    context.stack.leave();
}

void ButtonList::onMousePressed(const plug::MousePressedEvent &event,plug::EHC &context)
{
    if (m_state == Button::ButtonState::DISABLED) return;

    if (context.stopped)
    {
        m_state      = Button::ButtonState::RELEASED;
        m_prev_state = Button::ButtonState::RELEASED;
        return;
    }

    context.stopped = false;

    plug::Transform trf(getLayoutBox().getPosition(), Default_scale);    
    context.stack.enter(trf);
   
    if (m_prev_state == Button::ButtonState::PRESSED || m_state == Button::ButtonState::PRESSED)
    {
        size_t size = static_cast<int>(m_buttons.getSize());

        int last_presed = -1;
        int current_pressed = -1;
        for (int it = 0; it < size; it++)
        {
            context.stopped = false;
            if (m_buttons[it]->m_prev_state == Button::ButtonState::PRESSED) 
            {
                last_presed = it;
            }

            m_buttons[it]->onEvent(event, context);
            if (context.stopped) 
            {
                current_pressed = it;
            }
            
            m_buttons[it]->m_prev_state = m_buttons[it]->m_state;
            m_buttons[it]->m_state = Button::ButtonState::DISABLED;
        }

        if (current_pressed == -1 && last_presed >= 0)
        {
            m_buttons[last_presed]->m_prev_state = Button::ButtonState::PRESSED;
        }

        if (current_pressed >= 0)
        {
            m_buttons[current_pressed]->m_prev_state = Button::ButtonState::PRESSED;
        }

        context.stopped = (current_pressed != -1);

        m_state      = Button::ButtonState::RELEASED;
        m_prev_state = Button::ButtonState::RELEASED;
    }
    else
    {
        context.stopped = covers(context.stack, event.pos);

        if (context.stopped)
        {
            size_t size = m_buttons.getSize();
            for (size_t it = 0; it < size; it++)
            {
                m_buttons[it]->m_state = m_buttons[it]->m_prev_state;
            }

            m_state      = Button::ButtonState::PRESSED;
            m_prev_state = Button::ButtonState::PRESSED;
        }
    }

    context.stack.leave();
}

void ButtonList::onMouseReleased(const plug::MouseReleasedEvent &event, plug::EHC &context)
{
    if (m_state == Button::ButtonState::DISABLED)
        return;
        
    context.stopped = false;
}

void ButtonList::onTick(const plug::TickEvent &event, plug::EHC &context)
{
    Button::onTick(event, context);

    size_t size = m_buttons.getSize();
    for (size_t it = 0; it < size; it++)
    {
        m_buttons[it]->onEvent(event, context);
    }
}

void ButtonList::onParentUpdate(const plug::LayoutBox &parent_box)
{
    plug::LayoutBox &layout_box = getLayoutBox();
    layout_box.onParentUpdate(parent_box);
    
    size_t size = m_buttons.getSize();
    for (size_t it = 0; it < size; it++)
    {
        m_buttons[it]->onParentUpdate(layout_box);
    }
}


void ButtonList::addButton(Button *button)
{
    button->m_state      = Button::DISABLED;
    button->m_prev_state = Button::RELEASED;
    m_buttons.pushBack(button);
}