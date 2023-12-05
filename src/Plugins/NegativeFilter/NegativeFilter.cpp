#include "NegativeFilter.h"

#include "Plug/Graphics/VertexArray.h"

void NegativeFilter::applyFilter(plug::Canvas &canvas) const
{
    const plug::SelectionMask &mask = canvas.getSelectionMask();

    size_t width  = static_cast<size_t>(canvas.getSize().x);
    size_t height = static_cast<size_t>(canvas.getSize().y);

    for (size_t y = 0; y < height; y++)
    {
        for (size_t x = 0; x < width; x++)
        {
            plug::Color color = canvas.getPixel(x, y);
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
