#ifndef _CANVAS_H_
#define _CANVAS_H_

#include "window.h"
#include "../decorator/decorator.h"

#include "../../app/config.h"



class Tool
{
    public:
        enum Type
        {
            Pen, 
            Brash,
            Nothing,
        };

        enum State
        {
            Default,
            Hold, 
        };

        Tool(const Tool::Type type, const sf::Color color, const float thickness):
            type_(type), state_(Default), color_(color), thickness_(thickness), 
            hold_pos_(0.0, 0.0){}

        ~Tool(){}

        void Draw(sf::RenderTarget &target, const Dot &pos);

        Tool::Type type_;
        Tool::State state_;

        sf::Color color_;

        float thickness_;

        Dot hold_pos_;
        
};

class Canvas : public Window
{

    public:
        
        Canvas( Tool *tool, const Vector &canvas_size,
                const Vector &size, const Vector &parent_size,
                const Vector &pos, const Widget *parent,  
                const Vector &origin = Vector(0.0, 0.0), const Vector &scale = Vector(1.0, 1.0));
        
        virtual ~Canvas(){}

        virtual bool onMousePressed     (const Vector& pos, const MouseKey key, Container<Transform> &stack_transform);
        virtual bool onMouseMoved       (const Vector& pos, Container<Transform> &stack_transform);
        virtual bool onMouseReleased    (const Vector& pos, const MouseKey key, Container<Transform> &stack_transform);

        virtual bool onKeyboardPressed  (const KeyboardKey);
        virtual bool onKeyboardReleased (const KeyboardKey);

        virtual void draw               (sf::RenderTarget &targert, Container<Transform> &stack_transform);  

       
    private:
        void getDrawFormat(sf::VertexArray &vertex_array, const Transform &trf) const;
        Dot getCanvaseCoord(const Vector &pos) const;

        sf::RenderTexture background_;

        Tool *tool_;

        Vector canvas_size_;
        Dot real_pos_;
};

// class ScrollCanvas : public Action
// {
//     public:
//         ScrollCanvas(const Vector &delta, Canvas *ptr): 
//                 delta_(delta), canvas_(ptr){};
//         ~ScrollCanvas(){};

//         void operator() () const
//         {
//             Dot size = canvas_->GetSize();
//             canvas_->Move(Dot(delta_.x * size.x, delta_.y * size.y));
//             return;
//         }

//     private:
//         Dot delta_;
//         Canvas *canvas_;
// };

// class CanvaseManager : public Window
// {

//     public:

//         CanvaseManager (const char *path_texture,
//                         const Dot offset, const Vector scale):Window(path_texture, offset, scale), 
//                         canvases_(), delte_canvase_(false), cnt_(0){}
//         ~CanvaseManager()
//         {
//             size_t size = canvases_.getSize();
//             for (size_t it = 0; it < size; it++)
//                 delete canvases_[it];
//         };

//         virtual bool onMousePressed     (const Vector& pos, const MouseKey key, Container<Transform> &stack_transform);
//         virtual bool onMouseMoved       (const Vector& pos, Container<Transform> &stack_transform);
//         virtual bool onMouseReleased    (const Vector& pos, const MouseKey key, Container<Transform> &stack_transform);

//         virtual bool onKeyboardPressed  (const KeyboardKey);
//         virtual bool onKeyboardReleased (const KeyboardKey);

//         virtual void Draw               (sf::RenderTarget &target, Container<Transform> &stack_transform);


//         void CreateCanvase(Tool *tool);
//     private:
//         Container<Widget*> canvases_;
//         bool delte_canvase_;

//         size_t cnt_;
// }; 

// class Scrollbar: public Widget
// {

//     public:
//         enum Scroll_Type
//         {
//             Horizontal,
//             Vertical,
//         };

//         Scrollbar(Button *top_button, Button *bottom_button, Button *center_button, 
//                      Canvas *canvas, Scroll_Type type, const Dot &offset, const Vector &scale):
//                      top_button_(top_button), bottom_button_(bottom_button), center_button_(center_button),
//                      canvas_(canvas), transform_({offset, scale}), press_area_(), pos_press_(offset), type_(type)
//         {
//             press_area_ = top_button->GetTransform();
//             if (type == Scrollbar::Scroll_Type::Horizontal)
//                 press_area_.scale.x = 1.0;

//             if (type == Scrollbar::Scroll_Type::Vertical)
//                 press_area_.scale.y = 1.0;

//         }

//         virtual ~Scrollbar()
//         {
//             delete top_button_;
//             delete bottom_button_;
//             delete center_button_;
//         }

//         virtual bool onMousePressed     (const Vector& pos, const MouseKey key, Container<Transform> &stack_transform);
//         virtual bool onMouseMoved       (const Vector& pos, Container<Transform> &stack_transform);
//         virtual bool onMouseReleased    (const Vector& pos, const MouseKey key, Container<Transform> &stack_transform);

//         virtual void Draw               (sf::RenderTarget &targert, Container<Transform> &stack_transform) override;  

//         virtual bool onKeyboardPressed  (const KeyboardKey);
//         virtual bool onKeyboardReleased (const KeyboardKey);

//         virtual void PassTime           (const time_t delta_time);

//     private:

//         void MoveCenter         (Dot &new_coord);
//         void ResizeCenterButton (const Transform &canvas_trf);

//         Button *top_button_, *bottom_button_, *center_button_;
//         Canvas *canvas_;

//         Transform transform_;
//         Transform press_area_;

//         Vector pos_press_;

//         Scroll_Type type_;
// };

#endif