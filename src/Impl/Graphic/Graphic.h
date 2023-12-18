#ifndef _GRAPHIC_H_
#define _GRAPHIC_H_

#include <cassert>
#include <cstring>
#include <string>

#include "Plug/Math.h"
#include "Plug/Graphics.h"

#include "Plug/Color.h"

#include "GraphicConfig.h"

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

    Title &operator= (const Title &other)
    {
        delete[] msg;

        pos = other.pos;

        size_t size = strlen(other.msg);
        msg = new char[size + 1]; 

        width = other.width;
        color = other.color;

        for (size_t it = 0; it < size; it++)
        {
            msg[it] = other.msg[it];
        }
        
        msg[size] = '\0';   

        return *this;
    }

    plug::Vec2d pos;

    char* msg;
    double width;

    plug::Color color;
};


void    drawLine        (plug::RenderTarget &target, 
                         const plug::Vec2d &begin, const plug::Vec2d &end, const plug::Color color = plug::White);
   
void    drawRectangle   (plug::RenderTarget &target, 
                         const plug::Vec2d &left_up, const plug::Vec2d &right_down, const plug::Color color = plug::White);

void    writeText       (plug::RenderTarget &target, const plug::Vec2d &pos, 
                         const char *text, const double thicknesses,
                         const plug::Color color = plug::White);

bool checkColors(plug::Color rhs, plug::Color lhs);

#endif 