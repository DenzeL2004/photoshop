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
        pos_(), scale_x_(1.0), scale_y_(1.0){}

        Transform (const Dot pos, 
                   const double scale_x, const double scale_y):
        pos_(pos), scale_x_(scale_x), scale_y_(scale_y){}

        ~Transform(){}

        Dot pos_;
        double scale_x_, scale_y_;

};

class StackTransform
{
    public:
        StackTransform(): data_(){}
        ~StackTransform(){};

        void AddTransform   (const Transform &transform);
        void EraseTransform ();

        Transform GetTransformation () const;

        size_t GetSize() const;
    private:
        Container<Transform> data_;
};



class Widget
{

    public:
        Widget(){};
        ~Widget(){};

        virtual bool OnMousePressed     (const MouseKey key, StackTransform &stack_transform) = 0;
        virtual bool OnMouseMoved       (const int x, const int y, StackTransform &stack_transform) = 0;
        virtual bool OnMouseReleased    (const MouseKey key, StackTransform &stack_transform) = 0;

        virtual bool OnKeyboardPressed  (const KeyboardKey) = 0;
        virtual bool OnKeyboardReleased (const KeyboardKey) = 0;

        virtual void Draw(sf::RenderTarget &target, StackTransform &stack_transform) const = 0;  
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