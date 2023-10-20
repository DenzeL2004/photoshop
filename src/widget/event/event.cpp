#include "event.h"

#include "../widget.h"

static MouseKey     GetMouseKey     (sf::Event &event);
static KeyboardKey  GetKeyboard     (sf::Event &event);

void EventAdapter(Widget &widget, int mouse_x, int mouse_y, sf::Event &event, Container<Transform> &stack_transform)
{
    if (event.type == sf::Event::MouseMoved)
    {
        widget.OnMouseMoved((double)mouse_x, (double)mouse_y, stack_transform);
    }
    else
    {
        if (event.type == sf::Event::MouseButtonPressed || event.type == sf::Event::MouseButtonReleased)
        {
            
            MouseKey mouse_key = GetMouseKey(event);
            if (event.type == sf::Event::MouseButtonPressed)
                widget.OnMousePressed((double)mouse_x, (double)mouse_y, mouse_key, stack_transform);
            
            if (event.type == sf::Event::MouseButtonReleased)
                widget.OnMouseReleased((double)mouse_x, (double)mouse_y, mouse_key, stack_transform);
        }
    }

    KeyboardKey keyboard_key = GetKeyboard(event);

    if (event.type == sf::Event::KeyReleased)
        widget.OnKeyboardReleased(keyboard_key);

    return;
}

static MouseKey GetMouseKey(sf::Event &event)
{
    switch (event.mouseButton.button)
    {
        case sf::Mouse::Left:
            return MouseKey::LEFT;
        
        case sf::Mouse::Right:
            return MouseKey::RIGHT;

        default:
            break;
    }

    return MouseKey::NOTHING;
}


static KeyboardKey GetKeyboard(sf::Event &event)
{
    if (event.key.code == sf::Keyboard::Enter)
            return KeyboardKey::ENTER;

    return KeyboardKey::NOTHING;
}