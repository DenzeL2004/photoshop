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
                m_parent(parent),
                m_scale(scale),
                m_texture(texture.width, texture.height, texture.data){}
                

        Window(const Window &other) = delete;
        Window& operator= (const Window &other) = delete;

        virtual ~Window()
        {
            delete[] m_texture.data;
        }
        
        virtual void draw (plug::TransformStack& stack, plug::RenderTarget& target);  

    protected:

        void getDrawFormat(plug::VertexArray &vertex_array, Transform &transform) const;       
        
        const plug::Widget *m_parent;

        plug::Vec2d m_scale;

        plug::Texture m_texture;
        
    private:

        
};

#endif