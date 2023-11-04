#ifndef _EVENT_H_
#define _EVENT_H_

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Widget;
class Transform;

template< class ItemType> class Container;

enum class MouseKey
{
    NOTHING,
    LEFT,
    RIGHT,   
};


enum class KeyboardKey
{
    NOTHING,
    ENTER,
    ESC, 
    CTRL, 
    L, 
    F, 
};

void eventAdapter (Widget &widget, int mouse_x, int mouse_y, sf::Event &event, Container<Transform> &stack_transform);


#endif