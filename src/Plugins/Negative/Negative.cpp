#include "Negative.h"

#include "Plug/Graphics/VertexArray.h"

void NegativeFilter::applyFilter(plug::Canvas &canvas) const
{
    const plug::SelectionMask &mask = canvas.getSelectionMask();

    const plug::Texture &canvas_texture = canvas.getTexture();
    plug::Texture new_texture(canvas_texture.width, canvas_texture.height);

    for (size_t y = 0; y < canvas_texture.height; y++)
    {
        for (size_t x = 0; x < canvas_texture.width; x++)
        {
            plug::Color color = canvas_texture.getPixel(x, y);
            if (mask.getPixel(x, y))
            {
                color.r = 255u - color.r;
                color.g = 255u - color.g;
                color.b = 255u - color.b;   
            }
            
            new_texture.setPixel(x, y, color);
        }
    }

    plug::VertexArray vertex_array(plug::Quads, 4);

    vertex_array[0].tex_coords = Vec2d(0, 0);
    vertex_array[1].tex_coords = Vec2d(new_texture.width, 0);
    vertex_array[2].tex_coords = Vec2d(new_texture.width, new_texture.height);
    vertex_array[3].tex_coords = Vec2d(0, new_texture.height);
    
    vertex_array[0].position = Vec2d(0, 0);
    vertex_array[1].position = Vec2d(new_texture.width, 0);
    vertex_array[2].position = Vec2d(new_texture.width, new_texture.height);
    vertex_array[3].position = Vec2d(0, new_texture.height);
    
    canvas.draw(vertex_array, new_texture);
}

plug::Plugin* loadPlugin(void)
{
    return new NegativeFilter();
}
