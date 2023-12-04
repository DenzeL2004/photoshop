#include "Contrast.h"

#include "Plug/Graphics/VertexArray.h"

void ContrastFilter::applyFilter(plug::Canvas &canvas) const
{
    const plug::SelectionMask &mask = canvas.getSelectionMask();

    const plug::Texture &canvas_texture = canvas.getTexture();

    int lab = 0;

    for (size_t y = 0; y < canvas_texture.height; y++)
    {
        for (size_t x = 0; x < canvas_texture.width; x++)
        {
            plug::Color color = canvas_texture.getPixel(x, y);

            lab += static_cast<int>(color.r * Cf_r + color.g * Cf_g + color.b * Cf_b);
        }
    }

    lab /= canvas_texture.height * canvas_texture.width;   

    const int Color_limit = 256;
    uint8_t color_palette[Color_limit];

    double correction_cf = 1.0 + static_cast<double>(m_correction) / 100.0;

    for (int i = 0; i < Color_limit; i++)
    {
        int delta = i - lab;
        int new_color = lab + correction_cf * delta;

        if (new_color < 0) new_color = 0;
        if (new_color >= Color_limit) new_color = Color_limit - 1;
    
        color_palette[i] = static_cast<uint8_t>(new_color);
    }

    plug::Texture new_texture(canvas_texture.width, canvas_texture.height);

    for (size_t y = 0; y < canvas_texture.height; y++)
    {
        for (size_t x = 0; x < canvas_texture.width; x++)
        {
            plug::Color color = canvas_texture.getPixel(x, y);
            new_texture.setPixel(x, y, plug::Color(color_palette[color.r], color_palette[color.g], color_palette[color.b]));
            
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
    return new ContrastFilter(5);
}
