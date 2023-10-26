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

    if (event.type == sf::Event::KeyPressed)
        widget.OnKeyboardPressed(keyboard_key);

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

    switch (event.key.code)
    {
        case sf::Keyboard::Enter:
            return KeyboardKey::ENTER;
        
        case sf::Keyboard::Escape:
            return KeyboardKey::ESC;

        case sf::Keyboard::LControl: case sf::Keyboard::RControl:
            return KeyboardKey::CTRL;

        case sf::Keyboard::F:
            return KeyboardKey::F;

        case sf::Keyboard::L:
            return KeyboardKey::L;

        default:
            break;
    }

    return KeyboardKey::NOTHING;
}