#include "ColorField.h"
#include "Impl/Graphic/Graphic.h"


void ColorField::draw(plug::TransformStack &stack, plug::RenderTarget &target)
{   
    if (!checkColors(m_texture.getPixel(Color_field_size - 1, Color_field_size - 1), 
                    HSV2RGB(m_hue, Color_field_size - 1, Color_field_size - 1)))
    {
        defineTexture();
        m_color_palette.setFGColor(m_texture.getPixel(m_x, m_y));
    }

    plug::Transform trf(getLayoutBox().getPosition(), m_scale);
    stack.enter(trf);

    selection_hue.draw(stack, target);

    plug::Transform top_trf = stack.top();

    plug::VertexArray vertex_array(plug::Quads, 4);

    vertex_array[0].tex_coords = Vec2d(0, 0);
    vertex_array[1].tex_coords = Vec2d(m_texture.width, 0);
    vertex_array[2].tex_coords = Vec2d(m_texture.width, m_texture.height);
    vertex_array[3].tex_coords = Vec2d(0, m_texture.height);

    plug::Vec2d pos = top_trf.apply(Vec2d(0, 0));
    plug::Vec2d size = getLayoutBox().getSize() * top_trf.getScale();

    vertex_array[0].position = Vec2d(pos.x, pos.y);
    vertex_array[1].position = Vec2d(pos.x + size.x, pos.y);
    vertex_array[2].position = Vec2d(pos.x + size.x, pos.y + size.y);
    vertex_array[3].position = Vec2d(pos.x, pos.y + size.y);

    target.draw(vertex_array, m_texture);

    stack.leave();
}

void ColorField::onMousePressed(const plug::MousePressedEvent &event, plug::EHC &context)
{
    plug::Transform trf(getLayoutBox().getPosition(), m_scale);
    context.stack.enter(trf);

    selection_hue.onEvent(event, context);

    context.stopped = covers(context.stack, event.pos);
    plug::Vec2d local_pos = context.stack.restore(event.pos);
    
    if (context.stopped)
    {
        plug::Vec2d local_pos = context.stack.restore(event.pos);

        m_x = static_cast<size_t>(local_pos.x);
        m_y = static_cast<size_t>(local_pos.y);

        m_color_palette.setFGColor(m_texture.getPixel(m_x, m_y));
    }

    context.stack.leave();
}

void ColorField::defineTexture(void)
{
    for (size_t value = 0; value < Color_field_size; value++)
    {
        for (size_t saturation = 0; saturation < Color_field_size; saturation++)
        {   
            m_texture.setPixel(saturation, value, HSV2RGB(m_hue, saturation, value));
        }    
    }
}

void SelectionHue::draw(plug::TransformStack &stack, plug::RenderTarget &target)
{   
    plug::Transform trf(getLayoutBox().getPosition(), m_scale);
    stack.enter(trf);

    plug::Transform top_trf = stack.top();

    plug::VertexArray vertex_array(plug::Quads, 4);

    vertex_array[0].tex_coords = Vec2d(0, 0);
    vertex_array[1].tex_coords = Vec2d(m_texture.width, 0);
    vertex_array[2].tex_coords = Vec2d(m_texture.width, m_texture.height);
    vertex_array[3].tex_coords = Vec2d(0, m_texture.height);

    plug::Vec2d pos = top_trf.apply(Vec2d(0, 0));
    plug::Vec2d size = getLayoutBox().getSize() * top_trf.getScale();

    vertex_array[0].position = Vec2d(pos.x, pos.y);
    vertex_array[1].position = Vec2d(pos.x + size.x, pos.y);
    vertex_array[2].position = Vec2d(pos.x + size.x, pos.y + size.y);
    vertex_array[3].position = Vec2d(pos.x, pos.y + size.y);

    target.draw(vertex_array, m_texture);

    stack.leave();
}


void SelectionHue::onMousePressed(const plug::MousePressedEvent &event, plug::EHC &context)
{
    plug::Transform trf(getLayoutBox().getPosition(), m_scale);
    context.stack.enter(trf);

    context.stopped = covers(context.stack, event.pos);
    plug::Vec2d local_pos = context.stack.restore(event.pos);
    
    if (context.stopped)
    {
        plug::Vec2d local_pos = context.stack.restore(event.pos);

        m_hue = static_cast<size_t>(local_pos.x);
    }

    context.stack.leave();
}
