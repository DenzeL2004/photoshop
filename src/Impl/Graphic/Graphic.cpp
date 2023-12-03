#include "Impl/Graphic/Graphic.h"

#include <cmath>

static void getSymbolColorData(plug::Color *data, const char symbol, const plug::Color color);

void drawLine(plug::RenderTarget &target, 
              const plug::Vec2d &begin, const plug::Vec2d &end, const plug::Color color)
                             
{
    plug::VertexArray line(plug::PrimitiveType::Lines, 2);

    line[0] = {begin, Vec2d(0, 0), color};
    line[1] = {end, Vec2d(0, 0), color};

    target.draw(line);
}

void drawCircle(plug::RenderTarget &target, const plug::Vec2d &pos, 
                const float radius, const plug::Color color)
{
    plug::VertexArray circle(plug::PrimitiveType::LineStrip, 0);
    
    const size_t cnt = 360;
    double step = 2.0 * M_PI / static_cast<double>(cnt);

    double alpha = 0;
    for (size_t it = 0; it <= cnt; it++)
    {
        circle.appendVertex({plug::Vec2d(cos(alpha) * radius + pos.x, sin(alpha) * radius + pos.y), Vec2d(0, 0), color});
        alpha += step;
    }

    target.draw(circle);  
}


void drawRectangle(plug::RenderTarget &target, 
                   const plug::Vec2d &left_up, const plug::Vec2d &right_down, const plug::Color color)
{
    plug::VertexArray rectangle(plug::PrimitiveType::LineStrip, 5);

    rectangle[0] = rectangle[4] = {left_up, Vec2d(0, 0), color};
    rectangle[1] = {plug::Vec2d(right_down.x, left_up.y), Vec2d(0, 0), color};
    rectangle[2] = {right_down, Vec2d(0, 0), color};
    rectangle[3] = {plug::Vec2d(left_up.x, right_down.y), Vec2d(0, 0), color};

    target.draw(rectangle);
}

void writeText(plug::RenderTarget &target, const plug::Vec2d &pos, 
               const std::string &text, const double thikness,
               const plug::Color color)
{
    size_t len = text.size();

    if (len == 0) return;

    plug::VertexArray vertex_array(plug::Quads, 4);
    vertex_array[0].tex_coords = Vec2d(0, 0);
    vertex_array[1].tex_coords = Vec2d(plug::Symbol_width, 0);
    vertex_array[2].tex_coords = Vec2d(plug::Symbol_width, plug::Symbol_height);
    vertex_array[3].tex_coords = Vec2d(0, plug::Symbol_height);

    plug::Color *data = new plug::Color[plug::Symbol_width * plug::Symbol_height];

    double offset = plug::Symbol_width * thikness;

    for (size_t it = 0; it < len; it++)
    {
        getSymbolColorData(data, text[it], color);

        plug::Texture texture(plug::Symbol_width, plug::Symbol_height, data);

        plug::Vec2d size = Vec2d(thikness * plug::Symbol_width, thikness * plug::Symbol_height);

        vertex_array[0].position = Vec2d(pos.x + it * offset, pos.y);
        vertex_array[1].position = Vec2d(pos.x + it * offset + size.x, pos.y);
        vertex_array[2].position = Vec2d(pos.x + it * offset + size.x, pos.y + size.y);
        vertex_array[3].position = Vec2d(pos.x + it * offset, pos.y + size.y);
    
        target.draw(vertex_array, texture);
    }

    delete[] data;
}

static void getSymbolColorData(plug::Color *data, const char symbol, const plug::Color color)
{
    const bool *mask = plug::Unknown;

    switch (symbol)
    {
        case '.':
            mask = plug::Dot;
            break;

        case '!':
            mask = plug::Exclamation_mark;
            break;
        
        case '?':
            mask = plug::Question_mark;
            break;

        case '/':
            mask = plug::Slash;
            break;
        
        case ' ':
            mask = plug::Space;
            break;
        
        default:
            {
                if (symbol >= '0' && symbol <= '9')
                {
                    mask = plug::Numbers[symbol - '0'];
                }

                if (symbol >= 'a' && symbol <= 'z')
                {
                    mask = plug::Letters[symbol - 'a'];
                }

                if (symbol >= 'A' && symbol <= 'Z')
                {
                    mask = plug::Letters[symbol - 'A'];
                }
            }
            break;
    }

    for (size_t it = 0; it < plug::Symbol_width * plug::Symbol_height; it++)
    {
        if (mask[it])
        {
            data[it] = color;
        }
        else
        {
            data[it] = plug::Transparent;
        }
    }
}