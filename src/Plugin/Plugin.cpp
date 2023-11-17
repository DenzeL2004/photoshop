#include "Plugin.h"

void FilterBlackWhite::applyFilter(Canvas &canvas)
{
    
    sf::Image image = canvas.getBackground().getTexture().copyToImage();

    size_t width  = canvas.getCanvasSize().x;
    size_t height = canvas.getCanvasSize().y;

    for (size_t it = 0; it < width; it++)
    {
        for (size_t jt = 0; jt < height; jt++)
        {
                sf::Color color = image.getPixel(it, jt);
                
                size_t new_tone = (color.r + color.g + color.b);

                color.r = new_tone * 0.3;
                color.g = new_tone * 0.6;
                color.b = new_tone * 0.1;
                    
                image.setPixel(it, jt, color);   
        }
    }
    
    canvas.getBackground().clear();

    sf::Texture texture;
    texture.loadFromImage(image);
    
    sf::Sprite sprite(texture);
    canvas.getBackground().draw(sprite);

    canvas.getBackground().display();
}

extern "C" Filter* loadPlugin()
{
    return new FilterBlackWhite();
}  