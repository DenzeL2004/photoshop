#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <cstring>

#include "Impl/Widget/Widget.h"

struct Title
{
    Title(  const plug::Vec2d pos_, const char *msg_, const double width_, const plug::Color color_):
            pos(pos_),
            msg(new char[strlen(msg_) + 1]), 
            width(width_),
            color(color_)
    {
        size_t size = strlen(msg_);
        for (size_t it = 0; it < size; it++)
        {
            msg[it] = msg_[it];
        }

        msg[size] = '\0';
    }

    Title():Title(plug::Vec2d(0, 0), "", 1, plug::Color(128, 0, 128)){}

    ~Title()
    {
       delete[] msg;
    } 

    Title(  const Title &other):
            pos(other.pos),
            msg(new char[strlen(other.msg) + 1]), 
            width(other.width),
            color(other.color)
    {
        size_t size = strlen(other.msg);
        for (size_t it = 0; it < size; it++)
        {
            msg[it] = other.msg[it];
        }
        
        msg[size] = '\0';
    }

    Title &operator= (const Title &other) = delete;

    plug::Vec2d pos;

    char* const msg;
    double width;

    const plug::Color color;
};


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
        
        plug::Texture m_texture;

        Title m_title;
        
        const plug::Widget *m_parent;
        

        
        
    private:

        
};

#endif