#ifndef _EVENT_H_
#define _EVENT_H_

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>


enum class MouseKey
{
    NOTHING,
    LEFT,
    RIGHT,   
};


using KeyboardKey = uint32_t;
using KeyCode = int;

const uint8_t Shift_mask_pos = 16;
const uint8_t Ctrl_mask_pos  = 17;
const uint8_t Alt_mask_pos   = 18;

const uint8_t Key_code_mask  = (1 << 8) - 1;

const KeyCode Hot_key_brush    = sf::Keyboard::B;
const KeyCode Hot_key_line     = sf::Keyboard::L;
const KeyCode Hot_key_circle   = sf::Keyboard::C;
const KeyCode Hot_key_square   = sf::Keyboard::S;
const KeyCode Hot_key_pen      = sf::Keyboard::P;
const KeyCode Hot_key_eraser   = sf::Keyboard::E;
const KeyCode Hot_key_polyline = sf::Keyboard::N;
const KeyCode Hot_key_text     = sf::Keyboard::T;



const KeyCode Key_use_light_filter      = sf::Keyboard::L;
const KeyCode Key_use_blackwhite_filter = sf::Keyboard::B;
const KeyCode Key_use_last_filter       = sf::Keyboard::F;
const KeyCode Key_use_invert_filter     = sf::Keyboard::I;

const KeyCode Key_conferm_tool = sf::Keyboard::Enter;
const KeyCode Key_cancel_tool  = sf::Keyboard::Escape;

const MouseKey Key_use_tool = MouseKey::LEFT;


class Widget;
class Transform;

template< class ItemType> class Container;

class EventAdapter
{
    public:
        EventAdapter(){}
        ~EventAdapter() = default;

        void adapt(Widget &widget, int mouse_x, int mouse_y, sf::Event &event, Container<Transform> &stack_transform);

    private:
        bool Shift_pressed  = false;
        bool Ctrl_pressed   = false;
        bool Alt_pressed    = false;

        MouseKey    getMouseKey(sf::Event &event);
        KeyboardKey getKeyboarKey(sf::Event &event);

};


bool isShiftPressed(const KeyboardKey key);
bool isCtrlPressed(const KeyboardKey key);
bool isAltPressed(const KeyboardKey key);

KeyCode getKeyCode(const KeyboardKey key);

#endif