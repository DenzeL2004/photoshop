#ifndef _CANVAS_H_
#define _CANVAS_H_

#include "window.h"
#include "../button/button.h"
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
                const Vector &size, const Vector &pos, 
                const Widget *parent, const Vector &parent_size = Vector(1.0, 1.0),  
                const Vector &origin = Vector(0.0, 0.0), const Vector &scale = Vector(1.0, 1.0));
        
        virtual ~Canvas(){}

        virtual bool onMousePressed     (const Vector& pos, const MouseKey key, Container<Transform> &stack_transform);
        virtual bool onMouseMoved       (const Vector& pos, Container<Transform> &stack_transform);
        virtual bool onMouseReleased    (const Vector& pos, const MouseKey key, Container<Transform> &stack_transform);

        virtual bool onKeyboardPressed  (const KeyboardKey);
        virtual bool onKeyboardReleased (const KeyboardKey);

        virtual void draw               (sf::RenderTarget &targert, Container<Transform> &stack_transform);  

        Vector  getRealPos      () const;
        void    setRealPos      (const Vector &new_pos);   
        Vector  getCanvasSize   () const;

        void correctCanvasRealPos(const Vector &abs_size);
        
    private:
        void getDrawFormat(sf::VertexArray &vertex_array, const Transform &trf) const;
        Dot getCanvaseCoord(const Vector &pos) const;

        sf::RenderTexture background_;

        Tool *tool_;

        Vector canvas_size_;
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
            canvas_->setRealPos(delta_ + canvas_->getRealPos());
        }

    private:
        Dot delta_;
        Canvas *canvas_;
};

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

class Scrollbar: public Widget
{

    public:
        enum Type
        {
            HORIZONTAL,
            VERTICAL,
        };

        Scrollbar(  Canvas *canvas, const Type type,
                    const Vector &size, const Vector &pos, 
                    const Widget *parent, const Vector &parent_size = Vector(1.0, 1.0),  
                    const Vector &origin = Vector(0.0, 0.0), const Vector &scale = Vector(1.0, 1.0));

        virtual ~Scrollbar()
        {
            delete top_button_;
            delete bottom_button_;
            delete center_button_;
        }

        virtual bool onMousePressed     (const Vector& pos, const MouseKey key, Container<Transform> &stack_transform);
        virtual bool onMouseMoved       (const Vector& pos, Container<Transform> &stack_transform);
        virtual bool onMouseReleased    (const Vector& pos, const MouseKey key, Container<Transform> &stack_transform);

        virtual void draw               (sf::RenderTarget &targert, Container<Transform> &stack_transform);  

        virtual bool onKeyboardPressed  (const KeyboardKey);
        virtual bool onKeyboardReleased (const KeyboardKey);

        virtual void onUpdate           (const LayoutBox &parent_layout);

        void addButtons(Button *top_button, Button *bottom_button, Button *center_button);

    private:

        void moveCenter();
        void resizeCenter();
        

        Button *top_button_, *bottom_button_, *center_button_;
        Canvas *canvas_;

        Vector hold_pos_;
        Vector prev_canvas_real_pos_;
        
        Type type_;
};

#endif