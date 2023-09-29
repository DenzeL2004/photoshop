#ifndef _WIDGET_H_
#define _WIDGET_H_

#include "../generals_func/generals.h"
#include "../log_info/log_errors.h"

#include "event.h"
#include "../graphic/graphic.h"



class Widget
{

    public:
        Widget(){};
        virtual ~Widget(){};

        virtual bool OnMousePressed     (const MouseKey key) = 0;
        virtual bool OnMouseMoved       (const int x, const int y) = 0;
        virtual bool OnMouseReleased    (const MouseKey key) = 0;

        virtual bool OnKeyboardPressed  (const KeyboardKey) = 0;
        virtual bool OnKeyboardReleased (const KeyboardKey) = 0;

        virtual void Draw(sf::RenderTarget &target) const = 0;  
};

enum Widget_err
{
    LOAD_TEXTURE_ERR,
};


#endif