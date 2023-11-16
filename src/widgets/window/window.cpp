#include "window.h"

Window::Window( const char *path_texture,
                const Vec2d &size, const Vec2d &pos, 
                const Widget *parent, const Vec2d &parent_size, 
                const Vec2d &origin, const Vec2d& scale):
                Widget(size, pos, parent, (parent != nullptr) ? parent->getLayoutBox().getSize() : parent_size, origin, scale),
                texture_()
{
    if (!texture_.loadFromFile(path_texture))   
    {
        PROCESS_ERROR(LOAD_TEXTURE_ERR, "failed load tetxure from %s\n", path_texture);
        return;
    }
}

//================================================================================

void Window::draw(sf::RenderTarget &target, Container<Transform> &stack_transform)
{
    Transform trf(getLayoutBox().getPosition(), scale_);
    stack_transform.pushBack(trf.combine(stack_transform.getBack()));
    
    Transform last_trf = stack_transform.getBack();    

    sf::VertexArray vertex_array(sf::Quads, 4);

    getDrawFormat(vertex_array, last_trf);

    target.draw(vertex_array, &texture_);

    stack_transform.popBack();
}

void Window::getDrawFormat(sf::VertexArray &vertex_array, Transform &trf) const
{
    sf::Vector2u texture_size = texture_.getSize();

    vertex_array[0].texCoords = sf::Vector2f(0, 0);
    vertex_array[1].texCoords = sf::Vector2f(texture_size.x, 0);
    vertex_array[2].texCoords = sf::Vector2f(texture_size.x, texture_size.y);
    vertex_array[3].texCoords = sf::Vector2f(0, texture_size.y);
    
    Dot pos = trf.apply(Vec2d(0, 0));

    Vec2d size = trf.getScale() * getLayoutBox().getSize();

    vertex_array[0].position = sf::Vector2f(pos.x, pos.y);
    vertex_array[1].position = sf::Vector2f(pos.x + size.x, pos.y);
    vertex_array[2].position = sf::Vector2f(pos.x + size.x, pos.y + size.y);
    vertex_array[3].position = sf::Vector2f(pos.x, pos.y + size.y);
}

//================================================================================