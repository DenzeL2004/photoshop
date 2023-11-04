#ifndef _GRAPHIC_H_
#define _GRAPHIC_H_

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>


#include <unistd.h>

#include "../vector/vector.h"
        
#include "../graphic/graphic_config.h"


class EllipseShape : public sf::Shape
{
public :
 
    explicit EllipseShape(const sf::Vector2f& radius = sf::Vector2f(0, 0)) :
    m_radius(radius)
    {
        update();
    }
 
    void setRadius(const sf::Vector2f& radius)
    {
        m_radius = radius;
        update();
    }
 
    const sf::Vector2f& getRadius() const
    {
        return m_radius;
    }
 
    virtual size_t getPointCount() const
    {
        return 30; // fixed, but could be an attribute of the class if needed
    }
 
    virtual sf::Vector2f getPoint(unsigned int index) const
    {
        static const float pi = 3.141592654f;
 
        float angle = index * 2 * pi / getPointCount() - pi / 2;
        float x = std::cos(angle) * m_radius.x;
        float y = std::sin(angle) * m_radius.y;
 
        return sf::Vector2f(m_radius.x + x, m_radius.y + y);
    }
 
private :
 
    sf::Vector2f m_radius;
};

void    drawLine        (sf::RenderTarget &window, 
                         const Dot &dot_begin, const Dot &dot_end, const sf::Color color = sf::Color::White);

void    drawLine        (sf::RenderTarget &window, 
                            const sf::Vector2f &dot_begin, const sf::Vector2f &dot_end, const sf::Color color = sf::Color::White);

void    drawCircle      (sf::RenderTarget &window, const Dot &pos, 
                         const float radius, const sf::Color color = sf::Color::White);

void    drawRectangle   (sf::RenderTarget &window, 
                         const Dot &left_up, const Dot &right_down, const sf::Color color = sf::Color::White);

void    drawPixel       (sf::RenderTarget &window, const Dot &pos, const sf::Color color = sf::Color::White);

void    writeText       (sf::RenderTarget &window, const Dot &pos, 
                         const char *text, const char *font_path, const uint32_t text_size = 30u,
                         const sf::Color color = sf::Color::White);


const sf::Color Brown  = sf::Color(128, 64, 48);

const sf::Color Orange = sf::Color(255, 165, 48);

static const char *Oldtimer_font_path = "src/graphic/font/ofont.ru_Oldtimer.ttf";


#endif //#endif _GRAPHIC_H_