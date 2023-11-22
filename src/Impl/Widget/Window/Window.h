#ifndef _WINDOW_H_
#define _WINDOW_H_

#include "Impl/Widget/Widget.h"

class Window : public Widget
{
    public:

        Window( plug::Texture texture,
                const plug::LayoutBox& box, 
                const Widget *parent = nullptr, 
                const plug::Vec2d &scale = Vec2d(1.0, 1.0)):
                Widget(box),
                parent_(parent),
                scale_(scale),
                texture_(texture.width, texture.height, texture.data){}
                

        Window(const Window &other) = delete;
        Window& operator= (const Window &other) = delete;

        virtual ~Window()
        {
            delete[] texture_.data;
        }
        
        virtual void draw (plug::TransformStack& stack, plug::RenderTarget& target);  

    protected:

        bool covers(plug::TransformStack &stack, const plug::Vec2d &position) const;

        void getDrawFormat(plug::VertexArray &vertex_array, Transform &transform) const;       
        
        const plug::Widget *parent_;

        plug::Vec2d scale_;

        plug::Texture texture_;
        
    private:

        
};



#endif