#ifndef _WIDGET_H_
#define _WIDGET_H_

#include "../generals_func/generals.h"
#include "../log_info/log_errors.h"

#include "event.h"

#include "../graphic/graphic.h"
#include "../container/container.h"


struct Transform
{
    public:
        Transform():
        offset_(), scale_(){}

        Transform (const Vector offset, const Vector scale):
        offset_(offset), scale_(scale){}

        ~Transform(){}

        Transform (const Transform &other) = default;
        Transform& operator= (const Transform &other) = default;

        Transform   ApplyPrev       (const Transform &prev) const;
        Vector      ApplyTransform  (const Dot &pos)        const;

        Vector offset_;
        Vector scale_;

};

class Widget
{

    public:
        Widget(){};
        ~Widget(){};

        virtual bool OnMousePressed     (const MouseKey key, Container<Transform> &stack_transform) = 0;
        virtual bool OnMouseMoved       (const int x, const int y, Container<Transform> &stack_transform) = 0;
        virtual bool OnMouseReleased    (const MouseKey key, Container<Transform> &stack_transform) = 0;

        virtual bool OnKeyboardPressed  (const KeyboardKey) = 0;
        virtual bool OnKeyboardReleased (const KeyboardKey) = 0;

        virtual void Draw               (sf::RenderTarget &target, Container<Transform> &stack_transform) const = 0;  

        virtual void PassTime           (const time_t delta_time) = 0;
};



// class WidgetManager: public Widget
// {
//     public:
//         WidgetManager(): widgets_(){}
//         virtual ~WidgetManager(){};

//         virtual bool OnMousePressed     (const MouseKey key);
//         virtual bool OnMouseMoved       (const int x, const int y);
//         virtual bool OnMouseReleased    (const MouseKey key);

//         virtual bool OnKeyboardPressed  (const KeyboardKey);
//         virtual bool OnKeyboardReleased (const KeyboardKey);

//         virtual void Draw(sf::RenderTarget &target) const;  

        
//         Container<Widget*> widgets_;
// };

enum Widget_err
{
    LOAD_TEXTURE_ERR,
};


#endif