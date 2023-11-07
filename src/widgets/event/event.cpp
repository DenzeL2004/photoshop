#include "event.h"

#include "../widget/widget.h"


void EventAdapter::adapt(Widget &widget, int mouse_x, int mouse_y, sf::Event &event, Container<Transform> &stack_transform)
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

    KeyboardKey keyboard_key = getKeyboarKey(event);

    if (event.type == sf::Event::KeyReleased)
        widget.onKeyboardReleased(keyboard_key);

    if (event.type == sf::Event::KeyPressed)
        widget.onKeyboardPressed(keyboard_key);

    return;
}

MouseKey EventAdapter::getMouseKey(sf::Event &event)
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


KeyboardKey EventAdapter::getKeyboarKey(sf::Event &event)
{
   
    if (event.key.code == sf::Keyboard::RShift || event.key.code == sf::Keyboard::LShift)
    {
        Shift_pressed = (event.type == sf::Event::KeyPressed);
    }
    
    if (event.key.code == sf::Keyboard::RControl || event.key.code == sf::Keyboard::LControl)
    {
        Ctrl_pressed = (event.type == sf::Event::KeyPressed);
    }

    if (event.key.code == sf::Keyboard::RAlt || event.key.code == sf::Keyboard::LAlt)
    {
        Alt_pressed = (event.type == sf::Event::KeyPressed);
    }  

    KeyboardKey key = event.key.code;

    key |= Shift_pressed << Shift_mask_pos;
    key |= Ctrl_pressed  << Ctrl_mask_pos;
    key |= Alt_pressed   << Alt_mask_pos;

    return key;
}

bool isShiftPressed(const KeyboardKey key)
{
    return (key & (1 << Shift_mask_pos)) != 0;
}

bool isCtrlPressed(const KeyboardKey key)
{
    return (key & (1 << Ctrl_mask_pos)) != 0;
}

bool isAltPressed(const KeyboardKey key)
{
    return (key & (1 << Alt_mask_pos)) != 0;
}

KeyCode getKeyCode(const KeyboardKey key)
{
    return KeyCode(key & Key_code_mask);
}
