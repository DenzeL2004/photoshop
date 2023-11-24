#include "CanvasView.h"
#include "Impl/Graphic/Graphic.h"

const Vec2d Offset_Title = Vec2d(0.45, 0.0);
const double Tittle_size  = 1.9;

const double Border_width = 10.0;

//=================================================================================================

void CanvasView::draw(plug::TransformStack &stack, plug::RenderTarget &target)
{
    plug::Transform trf(getLayoutBox().getPosition(), m_scale);
    stack.enter(trf);

    plug::Texture canvas_texture = m_canvas->getTexture();

    plug::VertexArray vertex_array(plug::PrimitiveType::Quads, 4);
    
    plug::Transform top_transform = stack.top();

    plug::Vec2d size = top_transform.getScale() * getLayoutBox().getSize();
    plug::Vec2d pos = top_transform.apply(plug::Vec2d(0, 0));

    vertex_array[0].tex_coords = plug::Vec2d(m_canvas_pos.x, m_canvas_pos.y);
    vertex_array[1].tex_coords = plug::Vec2d(m_canvas_pos.x + size.x, m_canvas_pos.y);
    vertex_array[2].tex_coords = plug::Vec2d(m_canvas_pos.x + size.x, m_canvas_pos.y + size.y);
    vertex_array[3].tex_coords = plug::Vec2d(m_canvas_pos.x, m_canvas_pos.y + size.y);

    vertex_array[0].position = plug::Vec2d(pos.x, pos.y);
    vertex_array[1].position = plug::Vec2d(pos.x + size.x, pos.y);
    vertex_array[2].position = plug::Vec2d(pos.x + size.x, pos.y + size.y);
    vertex_array[3].position = plug::Vec2d(pos.x, pos.y + size.y);
    
    m_canvas->draw(vertex_array, canvas_texture);

    delete &canvas_texture;

    stack.leave();
}

void CanvasView::onMouseMove(const plug::MouseMoveEvent &event, plug::EHC &context)
{
    plug::Transform trf(getLayoutBox().getPosition(), m_scale);    
    context.stack.enter(trf);

    
    context.stack.leave();
}

void CanvasView::onMousePressed(const plug::MousePressedEvent &event, plug::EHC &context)
{
    plug::Transform trf(getLayoutBox().getPosition(), m_scale);    
    context.stack.enter(trf);

    plug::Vec2d pos = context.stack.restore(event.pos);

    plug::VertexArray circle(plug::PrimitiveType::LineStrip, 0);
    
    const size_t cnt = 360;
    double step = 2.0 * M_PI / static_cast<double>(cnt);

    double alpha = 0;
    for (size_t it = 0; it <= cnt; it++)
    {
        circle.appendVertex({plug::Vec2d(cos(alpha) * 10 + pos.x, sin(alpha) * 10 + pos.y), Vec2d(0, 0), plug::Red});
        alpha += step;
    }

    m_canvas->draw(circle);  

    context.stack.leave();
}

//================================================================================

void CanvasView::onMouseReleased(const plug::MouseReleasedEvent &event, plug::EHC &context)
{
    plug::Transform trf(getLayoutBox().getPosition(), m_scale);    
    context.stack.enter(trf);

    

    context.stack.leave();
}

//================================================================================

void CanvasView::onKeyboardPressed(const plug::KeyboardPressedEvent &event, plug::EHC &context)
{
    plug::Transform trf(getLayoutBox().getPosition(), m_scale);    
    context.stack.enter(trf);

    

    context.stopped = false;

    context.stack.leave();
}

//================================================================================

void CanvasView::onKeyboardReleased(const plug::KeyboardReleasedEvent &event, plug::EHC &context)
{
    plug::Transform trf(getLayoutBox().getPosition(), m_scale);    
    context.stack.enter(trf);

    context.stopped = false;

    context.stack.leave();
}

//================================================================================

void CanvasView::onTick(const plug::TickEvent &event, plug::EHC &context)
{
    plug::Transform trf(getLayoutBox().getPosition(), m_scale);    
    context.stack.enter(trf);

    context.stopped = false;

    context.stack.leave();
} 

//================================================================================
