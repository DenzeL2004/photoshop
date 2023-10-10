#ifndef _WINDOW_H_
#define _WINDOW_H_

#include "../widget.h"
#include "../../vector/vector.h"

#include "../../container/container.h"

class Window : public Widget
{

    public:
        Window  (const char *path_texture,
                 const Dot &offset, const Vector &scale);
        virtual ~Window(){}

        virtual bool OnMousePressed     (const double x, const double y, const MouseKey key, Container<Transform> &stack_transform);
        virtual bool OnMouseMoved       (const double x, const double y, Container<Transform> &stack_transform);
        virtual bool OnMouseReleased    (const double x, const double y, const MouseKey key, Container<Transform> &stack_transform);

        virtual bool OnKeyboardPressed  (const KeyboardKey);
        virtual bool OnKeyboardReleased (const KeyboardKey);

        virtual void Draw               (sf::RenderTarget &targert, Container<Transform> &stack_transform) const override;  

        virtual void PassTime           (const time_t delta_time);

        void Move       (const Dot &offset) {transform_.offset += offset;};

        Transform GetTransform() const {return transform_;}

    protected:
        void GetNewSize(sf::VertexArray &vertex_array, const Transform &transform) const;
       
        Transform transform_;

        double width_, hieght_;
        
        sf::Texture background_;

};

class Tool
{
    public:
        enum Type
        {
            Pen, 
            Brash,
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

class Canvase : public Widget
{

    public:
        
        Canvase (const double width, const double hieght, Tool *tool,  
                 const Dot &offset, const Vector &scale);
        
        virtual ~Canvase(){}

        virtual bool OnMousePressed     (const double x, const double y, const MouseKey key, Container<Transform> &stack_transform);
        virtual bool OnMouseMoved       (const double x, const double y, Container<Transform> &stack_transform);
        virtual bool OnMouseReleased    (const double x, const double y, const MouseKey key, Container<Transform> &stack_transform);

        virtual bool OnKeyboardPressed  (const KeyboardKey);
        virtual bool OnKeyboardReleased (const KeyboardKey);

        virtual void Draw               (sf::RenderTarget &targert, Container<Transform> &stack_transform) const override;  

        virtual void PassTime           (const time_t delta_time);

    private:
        void GetNewSize(sf::VertexArray &vertex_array, const Transform &transform) const;
        Dot GetCanvaseCoord(double x, double y, const Transform &transform) const;
        
        Transform transform_;
        double width_, hieght_;
        sf::RenderTexture background_;

        Tool *tool_;

        Dot real_pos_;

};

class CanvaseManager : public Window
{

    public:

        CanvaseManager (const char *path_texture,
                        const Dot offset, const Vector scale):Window(path_texture, offset, scale), 
                        canvases_(), delte_canvase_(false){}
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


        virtual void Draw               (sf::RenderTarget &target, Container<Transform> &stack_transform) const;

    private:
        Container<Widget*> canvases_;
        bool delte_canvase_;
               

}; 

#endif