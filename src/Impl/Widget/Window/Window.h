#ifndef _WINDOW_H_
#define _WINDOW_H_

#include "Impl/Widget/Widget.h"

class Window : public Widget
{
    public:

        Window( plug::Texture texture,
                const plug::LayoutBox& box, 
                const Widget *parent = nullptr):
                Widget(box),
                m_parent(parent),
                m_texture(texture.width, texture.height, texture.data){}
                
        Window(const Window &other) = delete;
        Window& operator= (const Window &other) = delete;

        virtual ~Window(){}
        
        virtual void draw (plug::TransformStack& stack, plug::RenderTarget& target);  

    protected:

        const plug::Widget *m_parent;

        plug::Texture m_texture;
        
    private:

        
};

#endif