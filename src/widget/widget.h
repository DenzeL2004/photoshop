#ifndef _WIDGET_H_
#define _WIDGET_H_

#include "../generals_func/generals.h"
#include "../log_info/log_errors.h"

#include "../graphic/graphic.h"
#include "../container/container.h"

#include "../app/config.h"
#include "event/event.h"

struct Transform
{
    public:
        Transform():
        offset(0, 0), scale(0, 0){}

        Transform (const Vector offset_, const Vector scale_):
        offset(offset_), scale(scale_){}

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


        bool GetFocuse() const; 
    
        virtual void SetFocus(bool value);

    protected:
        bool is_focused_ = false;
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

        void AddWidget                  (Widget *ptr);
        virtual void SetFocus           (bool value);
       
    private:

        Container<Widget*> widgets_;

        Transform transform_;
};

bool CheckIn(const Dot &mouse_pos);

#endif