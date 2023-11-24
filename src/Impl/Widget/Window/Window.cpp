#include "Window.h"

void Window::draw(plug::TransformStack& stack, plug::RenderTarget& target)
{
    Transform trf(getLayoutBox().getPosition(), m_scale);
    stack.enter(trf);
    
    Transform top_trf = stack.top();    

    plug::VertexArray vertex_array(plug::Quads, 4);

    getDrawFormat(vertex_array, top_trf);

    target.draw(vertex_array, m_texture);

    stack.leave();
}

void Window::getDrawFormat(plug::VertexArray &vertex_array, Transform &transform) const
{
    double width  = (double)m_texture.width;
    double height = (double)m_texture.height;

    vertex_array[0].tex_coords = Vec2d(0, 0);
    vertex_array[1].tex_coords = Vec2d(width, 0);
    vertex_array[2].tex_coords = Vec2d(width, height);
    vertex_array[3].tex_coords = Vec2d(0, height);
    
    Dot pos = transform.apply(Vec2d(0, 0));

    Vec2d size = transform.getScale() * getLayoutBox().getSize();

    vertex_array[0].position = Vec2d(pos.x, pos.y);
    vertex_array[1].position = Vec2d(pos.x + size.x, pos.y);
    vertex_array[2].position = Vec2d(pos.x + size.x, pos.y + size.y);
    vertex_array[3].position = Vec2d(pos.x, pos.y + size.y);
}

