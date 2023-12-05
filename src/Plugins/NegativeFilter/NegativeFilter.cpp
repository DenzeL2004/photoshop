#include "NegativeFilter.h"

#include "Plug/Graphics/VertexArray.h"

void NegativeFilter::applyFilter(plug::Canvas &canvas) const
{
    const plug::SelectionMask &mask = canvas.getSelectionMask();

    const plug::Texture &canvas_texture = canvas.getTexture();

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
            
            canvas.setPixel(x, y, color);
        }
    }
}

plug::Plugin* loadPlugin(void)
{
    return new NegativeFilter();
}
