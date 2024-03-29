#include "ContrastFilter.h"

#include "Plug/Graphics/VertexArray.h"

void ContrastFilter::applyFilter(plug::Canvas &canvas) const
{
    size_t width  = static_cast<size_t>(canvas.getSize().x);
    size_t height = static_cast<size_t>(canvas.getSize().y);

    int lab = 0;

    for (size_t y = 0; y < height; y++)
    {
        for (size_t x = 0; x < width; x++)
        {
            plug::Color color = canvas.getPixel(x, y);

            lab += static_cast<int>(color.r * Cf_r + color.g * Cf_g + color.b * Cf_b);
        }
    }

    lab /= height * width;   

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

    const plug::SelectionMask &mask = canvas.getSelectionMask();
    for (size_t y = 0; y < height; y++)
    {
        for (size_t x = 0; x < width; x++)
        {
            if (mask.getPixel(x, y))
            {
                plug::Color color = canvas.getPixel(x, y);
                canvas.setPixel(x, y, plug::Color(color_palette[color.r], color_palette[color.g], color_palette[color.b]));
            }
        }
    }
}

plug::Plugin* loadPlugin(void)
{
    return new ContrastFilter(20);
}
