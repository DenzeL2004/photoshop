#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <cstring>

#include "Impl/Widget/Widget.h"

class Window : public Widget
{
    public:

        Window( const plug::Texture &texture,
                const Title &title,
                const plug::LayoutBox& box, 
                const Widget *parent = nullptr):
                Widget(box),
                m_texture(texture.width, texture.height, texture.data),
                m_title(title),
                m_parent(parent){}
                
                
        Window(const Window &other) = delete;
        Window& operator= (const Window &other) = delete;

        virtual ~Window(){}
        
        virtual void draw (plug::TransformStack& stack, plug::RenderTarget& target);  

    protected:

        void onMousePressed(const plug::MousePressedEvent &event, plug::EHC &context);
        
        plug::Texture m_texture;

        Title m_title;
        
        const plug::Widget *m_parent;
};

#endif