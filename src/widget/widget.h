#ifndef _WIDGET_H_
#define _WIDGET_H_

#include <SFML/System/Vector2.hpp>

#include "../generals_func/generals.h"
#include "../log_info/log_errors.h"

#include "event.h"

#include "../graphic/graphic.h"
#include "../container/container.h"

#include "../app/config.h"


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

        Transform       ApplyPrev         (const Transform &prev) const;
        Vector          ApplyTransform    (const Dot &pos)        const;
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
        virtual bool OnMousePressed     (const double x, const double y, const MouseKey key, Container<Transform> &stack_transform) = 0;
        virtual bool OnMouseMoved       (const double x, const double y, Container<Transform> &stack_transform) = 0;
        virtual bool OnMouseReleased    (const double x, const double y, const MouseKey key, Container<Transform> &stack_transform) = 0;

        virtual bool OnKeyboardPressed  (const KeyboardKey) = 0;
        virtual bool OnKeyboardReleased (const KeyboardKey) = 0;

        virtual void Draw               (sf::RenderTarget &target, Container<Transform> &stack_transform) = 0;  

        virtual void PassTime           (const time_t delta_time) = 0;
};

class WidgetContainer: public Widget
{

    public:
        WidgetContainer(const Dot &offset, const Vector &scale):
                        widgets_(), transform_({offset, scale}){}
        ~WidgetContainer()
        {
            size_t size = widgets_.GetSize();
            for (size_t it = 0; it < size; it++)
                delete widgets_[it];
        }

        virtual bool OnMousePressed     (const double x, const double y, const MouseKey key, Container<Transform> &stack_transform);
        virtual bool OnMouseMoved       (const double x, const double y, Container<Transform> &stack_transform);
        virtual bool OnMouseReleased    (const double x, const double y, const MouseKey key, Container<Transform> &stack_transform);

        
        virtual void Draw               (sf::RenderTarget &target, Container<Transform> &stack_transform);  

        virtual bool OnKeyboardPressed  (const KeyboardKey);
        virtual bool OnKeyboardReleased (const KeyboardKey);

        virtual void PassTime           (const time_t delta_time);

        void AddWidget(Widget *ptr);
       

    private:

        Container<Widget*> widgets_;

        Transform transform_;
};


void EventAdapter (Widget &widget, int mouse_x, int mouse_y, sf::Event &event, Container<Transform> &stack_transform);


bool CheckIn(const Dot &mouse_pos);

#endif