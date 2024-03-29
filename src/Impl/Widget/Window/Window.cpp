#include "Window.h"
#include "Impl/Graphic/Graphic.h"

void Window::draw(plug::TransformStack& stack, plug::RenderTarget& target)
{
    Transform trf(getLayoutBox().getPosition(), Default_scale);
    stack.enter(trf);
    
    Transform top_trf = stack.top();    

    plug::VertexArray vertex_array(plug::Quads, 4);

    vertex_array[0].tex_coords = Vec2d(0, 0);
    vertex_array[1].tex_coords = Vec2d(m_texture.width, 0);
    vertex_array[2].tex_coords = Vec2d(m_texture.width, m_texture.height);
    vertex_array[3].tex_coords = Vec2d(0, m_texture.height);
    
    Dot pos = top_trf.apply(Vec2d(0, 0));

    Vec2d size = top_trf.getScale() * getLayoutBox().getSize();

    vertex_array[0].position = Vec2d(pos.x, pos.y);
    vertex_array[1].position = Vec2d(pos.x + size.x, pos.y);
    vertex_array[2].position = Vec2d(pos.x + size.x, pos.y + size.y);
    vertex_array[3].position = Vec2d(pos.x, pos.y + size.y);

    target.draw(vertex_array, m_texture);

    plug::Vec2d abs_pos = stack.apply(plug::Vec2d(0.0, 0.0)) + m_title.pos;

    writeText(target, abs_pos, m_title.msg, m_title.width, m_title.color);

    stack.leave();
}

void Window::onMousePressed(const plug::MousePressedEvent &event, plug::EHC &context)
{
    context.stopped = context.overlapped = covers(context.stack, event.pos); 
}