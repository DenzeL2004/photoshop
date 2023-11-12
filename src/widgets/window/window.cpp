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
    stack_transform.pushBack(trf.applyPrev(stack_transform.getBack()));
    
    Transform last_trf = stack_transform.getBack();    

    sf::VertexArray vertex_array(sf::Quads, 4);

    getDrawFormat(vertex_array, last_trf);

    target.draw(vertex_array, &texture_);

    stack_transform.popBack();
}

void Window::getDrawFormat(sf::VertexArray &vertex_array, const Transform &trf) const
{
    sf::Vector2u texture_size = texture_.getSize();

    vertex_array[0].texCoords = sf::Vector2f(0, 0);
    vertex_array[1].texCoords = sf::Vector2f((float)texture_size.x, 0);
    vertex_array[2].texCoords = sf::Vector2f((float)texture_size.x, (float)texture_size.y);
    vertex_array[3].texCoords = sf::Vector2f(0, (float)texture_size.y);
    
    sf::Vector2f pos = trf.rollbackTransform(Dot(0, 0));

    const LayoutBox* layout_box = &getLayoutBox();

    float abs_width  = (float)(trf.scale.x * layout_box->getSize().x);
    float abs_height = (float)(trf.scale.y * layout_box->getSize().y);

    vertex_array[0].position = pos;
    vertex_array[1].position = sf::Vector2f(pos.x + abs_width, pos.y);
    vertex_array[2].position = sf::Vector2f(pos.x + abs_width, pos.y + abs_height);
    vertex_array[3].position = sf::Vector2f(pos.x, pos.y + abs_height);
}

//================================================================================