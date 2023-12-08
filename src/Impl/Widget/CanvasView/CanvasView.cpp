#include <cstdio>

#include "CanvasView.h"
#include "Impl/Graphic/Graphic.h"

void CanvasView::draw(plug::TransformStack &stack, plug::RenderTarget &target)
{
    
    if (m_update_texture)
    {
        updateTexture();
        m_update_texture = false;
    }

    stack.enter(Transform(getLayoutBox().getPosition(), Default_scale));

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

    if (m_focuse && m_tool)
    {
        plug::Widget* preview = m_tool->getWidget();
        if (preview)
        {
            stack.enter(Transform(-m_canvas_pos, Default_scale));
            
            preview->draw(stack, target);

            stack.leave();
        }
    }

    stack.leave();
}

void CanvasView::onEvent(const plug::Event &event, plug::EHC &context)
{
    plug::Transform trf(getLayoutBox().getPosition(), Default_scale);    
    context.stack.enter(trf);
    
    context.stopped = false;

    switch (event.getType())
    {
        case plug::Focuse:
            onFocuse((const plug::FocuseEvent&)event, context);
            break;

        case plug::SaveCanvas:
            onSave((const plug::SaveEvent&)event, context);
            break;

        case plug::FilterApply:
            onFilterApply((const plug::FilterApplyEvent&)event, context);
            break;

        case plug::ToolChoose:
            onToolChoose((const plug::ToolChooseEvent&)event, context);
            break;

        default:
            Widget::onEvent(event, context);
            break;
    } 

   
    context.stack.leave();
}

void CanvasView::updateTexture(void)
{
    size_t width  = static_cast<size_t>(getLayoutBox().getSize().x);
    size_t height = static_cast<size_t>(getLayoutBox().getSize().y);
 
    m_canvas_pos.x = std::max(Eps, std::min(m_canvas.getSize().x - width  + Eps, m_canvas_pos.x));
    m_canvas_pos.y = std::max(Eps, std::min(m_canvas.getSize().y - height + Eps, m_canvas_pos.y));

    const plug::Texture &canvas_texture = m_canvas.getTexture(); 

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
        plug::Vec2d canvas_pos = context.stack.restore(event.pos) + m_canvas_pos;

        if (m_tool)
        {
            m_tool->onMove(canvas_pos);
        }

        m_update_texture = true;
    }

    context.stopped = false;
}

void CanvasView::onMousePressed(const plug::MousePressedEvent &event, plug::EHC &context)
{
    if (!m_focuse)
    {
        context.stopped = covers(context.stack, event.pos);
        return;
    }

    context.stopped = covers(context.stack, event.pos);

    if (context.stopped)
    {
        plug::Vec2d canvas_pos = context.stack.restore(event.pos) + m_canvas_pos;

        if (event.button_id == plug::MouseButton::Left && m_tool)
        {
            m_tool->onMainButton({plug::State::Pressed}, canvas_pos);
        }

        m_update_texture = true;
    }
}

void CanvasView::onMouseReleased(const plug::MouseReleasedEvent &event, plug::EHC &context)
{
    if (!m_focuse)
    {
        context.stopped = false;
        return;
    }

    plug::Vec2d canvas_pos = context.stack.restore(event.pos) + m_canvas_pos;

    if (event.button_id == plug::MouseButton::Left && m_tool)
    {
        m_tool->onMainButton({plug::State::Released}, canvas_pos);
    }

    m_update_texture = true;   
}

void CanvasView::onKeyboardPressed(const plug::KeyboardPressedEvent &event, plug::EHC &context)
{
    if (event.key_id == plug::KeyCode::Escape && m_tool)
    {
        m_tool->onCancel();
    }

    if (event.shift && m_tool)
    {
        m_tool->onModifier1({plug::State::Pressed});
    }

    context.stopped = false;
}

void CanvasView::onKeyboardReleased(const plug::KeyboardReleasedEvent &event, plug::EHC &context)
{
    if (!event.shift && m_tool)
    {
        m_tool->onModifier1({plug::State::Released});
    }

    context.stopped = false;
}

void CanvasView::onTick(const plug::TickEvent &event, plug::EHC &context)
{
    context.stopped = false;
} 

void CanvasView::onFocuse(const plug::FocuseEvent &event, plug::EHC &context)
{
    m_focuse = event.focuse_flag;
    if (m_tool)
    {
        m_tool->setActiveCanvas(m_canvas);
        m_tool->setColorPalette(m_color_palette);
    }
}

void CanvasView::onSave(const plug::SaveEvent &event, plug::EHC &context)
{
    const plug::Texture &canvas_texture = m_canvas.getTexture(); 

    sf::Image img;
    img.create(canvas_texture.width, canvas_texture.height);
    
    for (size_t y = 0; y < canvas_texture.height; y++)
    {
        for (size_t x = 0; x < canvas_texture.width; x++)
        {
            img.setPixel(x, y, getSFMLColor(canvas_texture.getPixel(x, y)));
        }
    }

    if (!img.saveToFile(event.file_path))
    {
        PROCESS_ERROR(ERR_FILE_OPEN, "failed save img by path(%s)", event.file_path);
    }
}

void CanvasView::onToolChoose(const plug::ToolChooseEvent &event, plug::EHC &context)
{
    if (!m_focuse) return;

    if (m_tool)
    {
        m_tool->release();
    }

    m_tool = m_tool_palette.getTool(event.tool_type);

    if (m_tool)
    {
        m_tool->setColorPalette(m_color_palette);
        m_tool->setActiveCanvas(m_canvas);
    }
}

void CanvasView::onFilterApply(const plug::FilterApplyEvent &event, plug::EHC &context)
{
    if (context.stopped) return;

    if (event.filter_type != FilterPalette::FilterType::LAST)
    {
        m_filter_palette.setLastFilter(event.filter_type);
    }

    plug::Filter* filter = m_filter_palette.getLastFilter();

    if (filter)
    {
        filter->applyFilter(m_canvas);
        filter->release();

        m_update_texture = true;

        context.stopped = true;
    }
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
