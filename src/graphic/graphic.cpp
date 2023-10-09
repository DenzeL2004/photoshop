#include "graphic.h"


//================================================================================

void DrawLine(sf::RenderTarget &window, 
              const Dot &dot_begin, const Dot &dot_end, const sf::Color color_line)
{
    sf::Vertex line[] =
    {
        sf::Vertex(sf::Vector2f((float)dot_begin.GetX(), (float)dot_begin.GetY()), color_line),
        sf::Vertex(sf::Vector2f((float)dot_end.GetX(), (float)dot_end.GetY()), color_line)
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

    circle.setPosition((float)pos.GetX(), (float)pos.GetY());

    window.draw(circle);

    return;
   
}

//================================================================================


void DrawRectangle(sf::RenderTarget &window, 
                   const Dot &left_up, const Dot &right_down, const sf::Color color)
{

    float hieght = (float)(right_down.GetY() - left_up.GetY());
    float width  = (float)(right_down.GetX() - left_up.GetX());

    sf::RectangleShape rectangle;
    rectangle.setSize({ width, hieght});
    rectangle.setFillColor(color);

    rectangle.setPosition((float)left_up.GetX(), (float)left_up.GetY());

    window.draw(rectangle);

    return;
   
}

//================================================================================


void DrawPixel(sf::RenderTarget &window, const Dot &pos, const sf::Color color)
{

    sf::RectangleShape pixel;
    pixel.setSize({ 1.f, 1.f });
    pixel.setFillColor(color);


    pixel.setPosition((float)pos.GetX(), (float)pos.GetY());

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

    text.setPosition((float)pos.GetX(), (float)pos.GetY());
    
    window.draw(text);
    
    return;
}
