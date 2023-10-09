#ifndef _WIDGET_H_
#define _WIDGET_H_

#include <SFML/System/Vector2.hpp>

#include "../generals_func/generals.h"
#include "../log_info/log_errors.h"

#include "event.h"

#include "../graphic/graphic.h"
#include "../container/container.h"


struct Transform
{
    public:
        Transform():
        offset(0, 0), scale(0, 0){}

        Transform (const Vector offset, const Vector scale):
        offset(offset), scale(scale){}

        ~Transform(){}

        Transform (const Transform &other) = default;
        Transform& operator= (const Transform &other) = default;

        Transform   ApplyPrev         (const Transform &prev) const;
        Vector      ApplyTransform    (const Dot &pos)        const;
        sf::Vector2f    RollbackTransform (const Vector &vec)     const;

        Vector offset;
        Vector scale;

};

enum Widget_Err
{
    LOAD_TEXTURE_ERR,
};

class Widget
{

    public:
        virtual bool OnMousePressed     (const MouseKey key, Container<Transform> &stack_transform) = 0;
        virtual bool OnMouseMoved       (const int x, const int y, Container<Transform> &stack_transform) = 0;
        virtual bool OnMouseReleased    (const MouseKey key, Container<Transform> &stack_transform) = 0;

        virtual bool OnKeyboardPressed  (const KeyboardKey) = 0;
        virtual bool OnKeyboardReleased (const KeyboardKey) = 0;

        virtual void Draw               (sf::RenderTarget &target, Container<Transform> &stack_transform) const = 0;  

        virtual void PassTime           (const time_t delta_time) = 0;
};






#endif