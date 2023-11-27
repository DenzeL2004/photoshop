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
    if (m_state ==  Button::ButtonState::DISABLED)
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

void Button::onMousePressed(const plug::MousePressedEvent &event,plug::EHC &context)
{
    if (m_state == Button::ButtonState::DISABLED)
        return;

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
    
    context.stopped = true;
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

// void ButtonList::draw(sf::RenderTarget &target, Container<Transform> &stack_transform)
// {
//     Button::draw(target, stack_transform);
    
//     size_t size = buttons_.getSize();
//     for (size_t it = 0; it < size; it++)
//     {
//         if (buttons_[it]->m_state != Button::ButtonState::DISABLED)
//             buttons_[it]->draw(target, stack_transform); 
//     }
// }

//================================================================================

// bool ButtonList::onMouseMoved(const Vec2d &pos, Container<Transform> &stack_transform)
// {
//     if (m_state ==  Button::ButtonState::DISABLED)
//         return false;

//     Transform trf(getLayoutBox().getPosition(), Default_scale);
//     stack_transform.pushBack(trf.combine(stack_transform.getBack()));
    
//     Transform last_trf = stack_transform.getBack();
//     Dot local_pos = last_trf.restore(pos);

//     stack_transform.popBack();

//     bool flag = checkIn(local_pos);

//     if (!flag)
//     { 
//         m_covering_time = 0;
//         m_state = m_prev_state;
//     }
//     else
//     {
//         if (m_state !=  Button::ButtonState::COVERED)
//         {
//             m_prev_state = m_state;
//             m_state =  Button::ButtonState::COVERED;
//         }
//     }

//     size_t size = buttons_.getSize();
//     for (size_t it = 0; it < size; it++)
//     {
//         if (m_prev_state == Button::ButtonState::PRESSED)
//         {
//             buttons_[it]->m_state = buttons_[it]->m_prev_state;
//             buttons_[it]->onMouseMoved(pos, stack_transform);
//         }
//         else
//             buttons_[it]->m_state = Button::ButtonState::DISABLED;
//     }
    
//     return flag;
// }

// //================================================================================

// bool ButtonList::onMousePressed(const Vec2d &pos, const MouseKey key, Container<Transform> &stack_transform)
// {
//     if (m_state == Button::ButtonState::DISABLED)
//         return false;
    
//     bool flag = false;
    
//     if (m_state == Button::ButtonState::PRESSED)
//     {
//         size_t size = buttons_.getSize();

//         int last_presed = -1;
//         for (size_t it = 0; it < size; it++)
//         {
//             if (buttons_[it]->m_state == Button::ButtonState::PRESSED) last_presed = it;
//             flag |= buttons_[it]->onMousePressed(pos, key, stack_transform);
            

//             buttons_[it]->m_prev_state = buttons_[it]->m_state;
//             buttons_[it]->m_state = Button::ButtonState::DISABLED;
//         }

//         if (!flag && last_presed != -1)
//             buttons_[last_presed]->m_prev_state = Button::ButtonState::PRESSED;


//         m_state      = Button::ButtonState::RELEASED;
//         m_prev_state = Button::ButtonState::RELEASED;
        
//     }
   
//     if (flag) return true;

//     Transform trf(getLayoutBox().getPosition(), Default_scale);
//     stack_transform.pushBack(trf.combine(stack_transform.getBack()));
    
//     Transform last_trf = stack_transform.getBack();
//     Dot local_pos = last_trf.restore(pos);

//     flag = checkIn(local_pos);
//     stack_transform.popBack();

//     if (flag && m_state != Button::ButtonState::PRESSED)
//     {
//         if (key == MouseKey::LEFT)
//         {
//             if (m_action != nullptr) (*m_action)();
//             m_state =  Button::ButtonState::PRESSED;
//         }
//     }
//     else
//         m_state =  Button::ButtonState::RELEASED;
    
//     return flag;
// }

// //================================================================================


// bool ButtonList::onMouseReleased(const Vec2d &pos, const MouseKey key, Container<Transform> &stack_transform)
// {
//     if (m_state == Button::ButtonState::DISABLED)
//         return false;

//     return true;
// }

// //================================================================================

// bool ButtonList::onKeyboardPressed(const KeyboardKey key)
// {
//     printf("ButtonList: mouse keyboard kye pressed\n");
//     return false;
// }

// //================================================================================

// bool ButtonList::onKeyboardReleased(const KeyboardKey key)
// {
//     printf("ButtonList: mouse keyboard kye released\n");
//     return false;
// }

// //================================================================================

// bool ButtonList::onTick(const time_t delta_time)
// {
//     m_covering_time += delta_time;

//     size_t size = buttons_.getSize();
//     for (size_t it = 0; it < size; it++)
//     {
//         buttons_[it]->onTick(delta_time);
//     }

//     return false;
// }

// //================================================================================

// void ButtonList::addButton(Button *button)
// {
//     buttons_.pushBack(button);
// }