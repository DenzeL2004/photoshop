#include "widget.h"

static MouseKey     GetMouseKey     (sf::Event &event);

//=======================================================================================

Transform Transform::ApplyPrev(const Transform &prev) const
{
    Dot new_pos = prev.offset + Vector(prev.scale.x * offset.x, prev.scale.y * offset.y);
    Transform res(new_pos, {scale.x * prev.scale.x, scale.y * prev.scale.y});

    return res;
}

Dot Transform::ApplyTransform(const Dot &pos) const
{
    Dot res = pos - offset;
    
    res.x /= scale.x;
    res.y /= scale.y;

    return res;
}

sf::Vector2f Transform::RollbackTransform (const Vector &vec) const
{
    return sf::Vector2f(vec.x * scale.x + offset.x, vec.y * scale.y + offset.y);
}

//================================================================================

void EventAdapter(Widget &widget, int mouse_x, int mouse_y, sf::Event &event, Container<Transform> &stack_transform)
{
    if (event.type == sf::Event::MouseMoved)
    {
        widget.OnMouseMoved(mouse_x, mouse_y, stack_transform);
    }
    else
    {
        if (event.type == sf::Event::MouseButtonPressed || event.type == sf::Event::MouseButtonReleased)
        {
            
            MouseKey mouse_key = GetMouseKey(event);
            if (event.type == sf::Event::MouseButtonPressed)
                widget.OnMousePressed(mouse_x, mouse_y, mouse_key, stack_transform);
            
            if (event.type == sf::Event::MouseButtonReleased)
                widget.OnMouseReleased(mouse_x, mouse_y, mouse_key, stack_transform);
        }
    }

    return;
}

static MouseKey GetMouseKey(sf::Event &event)
{
    switch (event.mouseButton.button)
    {
        case sf::Mouse::Left:
            return MouseKey::Left;
        
        case sf::Mouse::Right:
            return MouseKey::Right;

        default:
            break;
    }

    return MouseKey::Nothing;
}
