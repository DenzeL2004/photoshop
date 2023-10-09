#include "graphic.h"


//================================================================================

void DrawLine(sf::RenderTarget &window, 
              const Dot &dot_begin, const Dot &dot_end, const sf::Color color_line)
{
    sf::Vertex line[] =
    {
        sf::Vertex(sf::Vector2f((float)dot_begin.x, (float)dot_begin.y), color_line),
        sf::Vertex(sf::Vector2f((float)dot_end.x, (float)dot_end.y), color_line)
    };

    window.draw(line, 2, sf::Lines);

    return;
   
}

//================================================================================


void DrawCircle(sf::RenderTarget &window, const Dot &pos, 
                const float radius, const sf::Color color)
{

    sf::CircleShape circle(radius);
    circle.setFillColor(color);

    circle.setPosition((float)pos.x, (float)pos.y);

    window.draw(circle);

    return;
   
}

//================================================================================


void DrawRectangle(sf::RenderTarget &window, 
                   const Dot &left_up, const Dot &right_down, const sf::Color color)
{

    float hieght = (float)(right_down.y - left_up.y);
    float width  = (float)(right_down.x - left_up.x);

    sf::RectangleShape rectangle;
    rectangle.setSize({ width, hieght});
    rectangle.setFillColor(color);

    rectangle.setPosition((float)left_up.x, (float)left_up.y);

    window.draw(rectangle);

    return;
   
}

//================================================================================


void DrawPixel(sf::RenderTarget &window, const Dot &pos, const sf::Color color)
{

    sf::RectangleShape pixel;
    pixel.setSize({ 1.f, 1.f });
    pixel.setFillColor(color);


    pixel.setPosition((float)pos.x, (float)pos.y);

    window.draw(pixel);
    
    return;
   
}

//================================================================================

void WriteText (sf::RenderTarget &window, const Dot &pos, 
                const char *msg, const char *font_path, const uint32_t text_size, 
                const sf::Color color)
{
    assert(msg       != nullptr && "msg is nullptr");
    assert(font_path != nullptr && "font_path is nullptr");

    sf::Font font;

    if (!font.loadFromFile(font_path))
    {
        PROCESS_ERROR(ERR_FILE_OPEN, "load font from file failed\n");
        return;
    }    

    sf::Text text(msg, font, text_size);
    text.setFillColor(color);

    text.setPosition((float)pos.x, (float)pos.y);
    
    window.draw(text);
    
    return;
}
