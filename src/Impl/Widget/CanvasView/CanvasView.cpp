#include "CanvasView.h"
#include "Impl/Graphic/Graphic.h"

#include <cstdio>



void CanvasView::draw(plug::TransformStack &stack, plug::RenderTarget &target)
{
    updateTexture();
    if (m_update_texture)
    {
        m_update_texture = false;
    }

    plug::Transform trf(getLayoutBox().getPosition(), Default_scale);
    stack.enter(trf);

    plug::VertexArray vertex_array(plug::PrimitiveType::Quads, 4);
    
    plug::Transform top_transform = stack.top();

    plug::Vec2d size = top_transform.getScale() * getLayoutBox().getSize();
    plug::Vec2d pos = top_transform.apply(plug::Vec2d(0, 0));

    vertex_array[0].tex_coords = plug::Vec2d(0, 0);
    vertex_array[1].tex_coords = plug::Vec2d(size.x, 0);
    vertex_array[2].tex_coords = plug::Vec2d(size.x, size.y);
    vertex_array[3].tex_coords = plug::Vec2d(0, size.y);

    vertex_array[0].position = plug::Vec2d(pos.x, pos.y);
    vertex_array[1].position = plug::Vec2d(pos.x + size.x, pos.y);
    vertex_array[2].position = plug::Vec2d(pos.x + size.x, pos.y + size.y);
    vertex_array[3].position = plug::Vec2d(pos.x, pos.y + size.y);
    
    target.draw(vertex_array, *m_texture);

    stack.leave();
}

void CanvasView::onEvent(const plug::Event &event, plug::EHC &context)
{
    plug::Transform trf(getLayoutBox().getPosition(), Default_scale);    
    context.stack.enter(trf);
    
    context.stopped = false;

    if (event.getType() == plug::Focuse)
    {
        CanvasView::onFocuse((const plug::FocuseEvent&)event, context);
    }

    Widget::onEvent(event, context);

    context.stack.leave();
}

void CanvasView::updateTexture(void)
{
    size_t width  = static_cast<size_t>(getLayoutBox().getSize().x);
    size_t height = static_cast<size_t>(getLayoutBox().getSize().y);
 
    m_canvas_pos.x = std::max(Eps, std::min(m_canvas.getSize().x - width  + Eps, m_canvas_pos.x));
    m_canvas_pos.y = std::max(Eps, std::min(m_canvas.getSize().y - height + Eps, m_canvas_pos.y));

    plug::Texture canvas_texture = m_canvas.getTexture(); 

    size_t offset_x = static_cast<size_t>(m_canvas_pos.x);
    size_t offset_y = static_cast<size_t>(m_canvas_pos.y);

    if (m_texture)
    {
        delete m_texture;
    }

    m_texture = new plug::Texture(width, height);

    for (size_t jt = 0; jt < height; jt++)
    {
        for (size_t it = 0; it < width; it++)
        {
            m_texture->data[jt * width + it] = canvas_texture.data[(jt + offset_y) * canvas_texture.width + (it + offset_x)];
        }
    }
}

void CanvasView::onMouseMove(const plug::MouseMoveEvent &event, plug::EHC &context)
{
    if (!m_focuse)
    {
        context.stopped = false;
        return;
    }

    context.stopped = covers(context.stack, event.pos);

    if (context.stopped)
    {
        plug::Vec2d center = context.stack.restore(event.pos) + m_canvas_pos;

        brush->onMove(center);

        m_update_texture = true;
    }

    context.stopped = false;
}

void CanvasView::onMousePressed(const plug::MousePressedEvent &event, plug::EHC &context)
{
    if (!m_focuse)
    {
        context.stopped = false;
        return;
    }

    context.stopped = covers(context.stack, event.pos);

    if (context.stopped)
    {
        plug::Vec2d center = context.stack.restore(event.pos) + m_canvas_pos;
        
        brush->onMainButton({plug::State::Pressed}, center);

        m_update_texture = true;
    }
}

void CanvasView::onMouseReleased(const plug::MouseReleasedEvent &event, plug::EHC &context)
{
    context.stopped = false;
    if (!m_focuse)
    {
        brush->onCancel();
        return;
    }

    plug::Vec2d center = context.stack.restore(event.pos) + m_canvas_pos;
    
    brush->onConfirm();

    m_update_texture = true;
    
}

void CanvasView::onKeyboardPressed(const plug::KeyboardPressedEvent &event, plug::EHC &context)
{
    context.stopped = false;
}

void CanvasView::onKeyboardReleased(const plug::KeyboardReleasedEvent &event, plug::EHC &context)
{
    context.stopped = false;
}

void CanvasView::onTick(const plug::TickEvent &event, plug::EHC &context)
{
    context.stopped = false;
} 

void CanvasView::onFocuse(const plug::FocuseEvent &event, plug::EHC &context)
{
    m_focuse = event.focuse_flag;

    brush->setActiveCanvas(m_canvas);
    brush->setColorPalette(m_color_palette);
}

void CanvasView::onParentUpdate(const plug::LayoutBox &parent_box)
{
    Widget::onParentUpdate(parent_box);

    plug::Vec2d size = getLayoutBox().getSize();
    plug::Vec2d canvas_size = m_canvas.getSize();

    bool resize_canvas = false;

    if (m_canvas_pos.x + size.x >= canvas_size.x)
    {
        canvas_size.x =  m_canvas_pos.x + size.x * 1.5;
        resize_canvas = true;
    }

    if (m_canvas_pos.y + size.y >= canvas_size.y)
    {
        canvas_size.y =  m_canvas_pos.y + size.y * 1.5;
        resize_canvas = true;
    }
    
    if (resize_canvas)
    {
        m_canvas.setSize(canvas_size);
    }

    m_update_texture = true;
}
