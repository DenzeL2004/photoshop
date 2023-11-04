#include "event.h"

#include "../widget/widget.h"

static MouseKey     getMouseKey     (sf::Event &event);
static KeyboardKey  getKeyboard     (sf::Event &event);

void eventAdapter(Widget &widget, int mouse_x, int mouse_y, sf::Event &event, Container<Transform> &stack_transform)
{
    Vector mouse_pos((double)mouse_x, (double)mouse_y);

    if (event.type == sf::Event::MouseMoved)
    {
        widget.onMouseMoved(mouse_pos, stack_transform);
    }
    else
    {
        if (event.type == sf::Event::MouseButtonPressed || event.type == sf::Event::MouseButtonReleased)
        {
            
            MouseKey mouse_key = getMouseKey(event);
            if (event.type == sf::Event::MouseButtonPressed)
                widget.onMousePressed(mouse_pos, mouse_key, stack_transform);
            
            if (event.type == sf::Event::MouseButtonReleased)
                widget.onMouseReleased(mouse_pos, mouse_key, stack_transform);
        }
    }

    KeyboardKey keyboard_key = getKeyboard(event);

    if (event.type == sf::Event::KeyReleased)
        widget.onKeyboardReleased(keyboard_key);

    if (event.type == sf::Event::KeyPressed)
        widget.onKeyboardPressed(keyboard_key);

    return;
}

static MouseKey getMouseKey(sf::Event &event)
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


static KeyboardKey getKeyboard(sf::Event &event)
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