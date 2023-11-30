#include "ToolBrush.h"

#include <cassert>
#include <cstdio>

void ToolBrush::setColorPalette(plug::ColorPalette &palette)
{
    m_color_palette = &palette;
}



void ToolBrush::setActiveCanvas(plug::Canvas &canvas)
{
    m_canvas = &canvas;
    onCancel();
}

void ToolBrush::onMainButton(const plug::ControlState &state, const plug::Vec2d &pos)
{
    assert(m_canvas != nullptr && "canvas is nullptr");
    assert(m_color_palette != nullptr && "color_palette is nullptr");

    if (state.state != plug::State::Pressed) return;

    if (!m_active) m_active = true;
    plug::VertexArray vertex(plug::PrimitiveType::Points, 1);

    printf("vertex start\n");

    vertex[0].position = pos;

    printf("vertex midle\n");

    vertex[0].color = m_color_palette->getFGColor();

    printf("vertex finish\n");

    m_canvas->draw(vertex);
}

void ToolBrush::onMove(const plug::Vec2d &pos)
{
    assert(m_canvas != nullptr && "canvas is nullptr");
    assert(m_color_palette != nullptr && "color_palette is nullptr");

    if (!m_active) return;

    plug::VertexArray vertex(plug::PrimitiveType::Points, 1);

    //printf("vertex start\n");

    vertex[0].position = pos;

    //printf("vertex midle\n");

    vertex[0].color = m_color_palette->getFGColor();

    //printf("vertex finish\n");

    m_canvas->draw(vertex);
}

// void ToolBrush::drawForm(const plug::Vec2d &pos)
// {
//     assert(m_canvas != nullptr && "canvas is nullptr");
//     assert(m_color_palette != nullptr && "color_palette is nullptr");

//     plug::VertexArray circle(plug::PrimitiveType::TriangleFan, 0);
    
//     const size_t cnt = 360;
//     double radius = 10.0;
//     double step = 2.0 * M_PI / static_cast<double>(cnt);

//     plug::Color color = m_color_palette->getFGColor();

//     circle.appendVertex({pos, Vec2d(0, 0), color});

//     double alpha = 0;
//     for (size_t it = 0; it <= cnt; it++)
//     {
//         circle.appendVertex({plug::Vec2d(cos(alpha) * radius + pos.x, sin(alpha) * radius + pos.y), Vec2d(0, 0), color});
//         alpha += step;
//     }

//     plug::Texture texture(1, 1);
//     texture.setPixel(0, 0, color);

//     m_canvas->draw(circle, texture);
// }

plug::Plugin* loadPlugin(void)
{
    return new ToolBrush();
}