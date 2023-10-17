#ifndef _CANVAS_H_
#define _CANVAS_H_

#include "window.h"
#include "../decorator/decorator.h"

#include "canvas_config.h"


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

class Canvas : public Widget
{

    public:
        
        Canvas (const double width, const double hieght, Tool *tool,  
                 const Dot &offset, const Vector &scale);
        
        virtual ~Canvas(){}

        virtual bool OnMousePressed     (const double x, const double y, const MouseKey key, Container<Transform> &stack_transform);
        virtual bool OnMouseMoved       (const double x, const double y, Container<Transform> &stack_transform);
        virtual bool OnMouseReleased    (const double x, const double y, const MouseKey key, Container<Transform> &stack_transform);

        virtual bool OnKeyboardPressed  (const KeyboardKey);
        virtual bool OnKeyboardReleased (const KeyboardKey);

        virtual void Draw               (sf::RenderTarget &targert, Container<Transform> &stack_transform) override;  

        virtual void PassTime           (const time_t delta_time);

        Dot         GetSize             () const;
        Dot         GetRealPos          () const;
        Transform   GetTransform        () const;

        void Move               (const Dot &offset);
        void CorrectRealCoord   (const Transform &transform);

    private:
        void GetNewSize(sf::VertexArray &vertex_array, const Transform &transform) const;
        Dot GetCanvaseCoord(double x, double y, const Transform &transform) const;
        
        Transform transform_;
        double width_, hieght_;
        sf::RenderTexture background_;

        Tool *tool_;
        Dot real_pos_;
};

class ScrollCanvas : public Action
{
    public:
        ScrollCanvas(const Vector &delta, Canvas *ptr): 
                delta_(delta), canvas_(ptr){};
        ~ScrollCanvas(){};

        void operator() () const
        {
            Dot size = canvas_->GetSize();
            canvas_->Move(Dot(delta_.x * size.x, delta_.y * size.y));
            return;
        }

    private:
        Dot delta_;
        Canvas *canvas_;
};

class CanvaseManager : public Window
{

    public:

        CanvaseManager (const char *path_texture,
                        const Dot offset, const Vector scale):Window(path_texture, offset, scale), 
                        canvases_(), delte_canvase_(false), cnt_(0){}
        ~CanvaseManager()
        {
            size_t size = canvases_.GetSize();
            for (size_t it = 0; it < size; it++)
                delete canvases_[it];
        };

        virtual bool OnMousePressed     (const double x, const double y, const MouseKey key, Container<Transform> &stack_transform);
        virtual bool OnMouseMoved       (const double x, const double y, Container<Transform> &stack_transform);
        virtual bool OnMouseReleased    (const double x, const double y, const MouseKey key, Container<Transform> &stack_transform);

        virtual bool OnKeyboardPressed  (const KeyboardKey);
        virtual bool OnKeyboardReleased (const KeyboardKey);

        virtual void Draw               (sf::RenderTarget &target, Container<Transform> &stack_transform);


        void CreateCanvase(Tool *tool);
    private:
        Container<Widget*> canvases_;
        bool delte_canvase_;

        size_t cnt_;
}; 

class Scrollbar: public Widget
{

    public:
        enum Scroll_Type
        {
            Horizontal,
            Vertical,
        };

        Scrollbar(Button *top_button, Button *bottom_button, Button *center_button, 
                     Canvas *canvas, Scroll_Type type, const Dot &offset, const Vector &scale):
                     top_button_(top_button), bottom_button_(bottom_button), center_button_(center_button),
                     canvas_(canvas), transform_({offset, scale}), press_area_(), pos_press_(offset), type_(type)
        {
            press_area_ = top_button->GetTransform();
            if (type == Scrollbar::Scroll_Type::Horizontal)
                press_area_.scale.x = 1.0;

            if (type == Scrollbar::Scroll_Type::Vertical)
                press_area_.scale.y = 1.0;

        }

        virtual ~Scrollbar()
        {
            delete top_button_;
            delete bottom_button_;
            delete center_button_;
        }

        virtual bool OnMousePressed     (const double x, const double y, const MouseKey key, Container<Transform> &stack_transform);
        virtual bool OnMouseMoved       (const double x, const double y, Container<Transform> &stack_transform);
        virtual bool OnMouseReleased    (const double x, const double y, const MouseKey key, Container<Transform> &stack_transform);

        virtual void Draw               (sf::RenderTarget &targert, Container<Transform> &stack_transform) override;  

        virtual bool OnKeyboardPressed  (const KeyboardKey);
        virtual bool OnKeyboardReleased (const KeyboardKey);

        virtual void PassTime           (const time_t delta_time);

    private:

        void MoveCenter         (Dot &new_coord);
        void ResizeCenterButton (const Transform &canvas_trf);

        Button *top_button_, *bottom_button_, *center_button_;
        Canvas *canvas_;

        Transform transform_;
        Transform press_area_;

        Vector pos_press_;

        Scroll_Type type_;
};

#endif