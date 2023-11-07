
#include "color_palatte.h"

const size_t Color_limit = 256;

void ColorPalette::draw(sf::RenderTarget &target, Container<Transform> &stack_transform)
{
    LayoutBox *layout_box = &getLayoutBox();
    
    Transform trf(layout_box->getPosition(), scale_);
    stack_transform.pushBack(trf.applyPrev(stack_transform.getBack()));
    
    size_t offset = 0;

    for (size_t ray = 0; ray < Color_limit; ray++)
    {
        colors_[0 * Color_limit + ray] = sf::Color(Color_limit - 1, ray, 0);
        colors_[1 * Color_limit + ray] = sf::Color(Color_limit - ray - 1, Color_limit - 1, 0);
        colors_[2 * Color_limit + ray] = sf::Color(0, Color_limit - 1, ray);
        colors_[3 * Color_limit + ray] = sf::Color(0, Color_limit - ray - 1, Color_limit - 1);
        colors_[4 * Color_limit + ray] = sf::Color(ray, 0, Color_limit - 1);   
        colors_[5 * Color_limit + ray] = sf::Color(Color_limit - 1, 0, Color_limit - ray - 1);
    }

    Transform last_trf = stack_transform.getBack();

    sf::Image img;
    img.create(Color_limit * 6, 1);

    for (size_t it = 0; it < Color_limit * 6; it++)
        img.setPixel(it, 0, colors_[it]);

    sf::Texture texture;
    texture.loadFromImage(img);
   
    sf::VertexArray vertex_array(sf::Quads, 4);

    getDrawFormat(texture, vertex_array, last_trf);

    target.draw(vertex_array, &texture);

    stack_transform.popBack();
}


void ColorPalette::getDrawFormat(const sf::Texture &texture, sf::VertexArray &vertex_array, const Transform &trf) const
{
    sf::Vector2u texture_size = texture.getSize();

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

bool ColorPalette::onMousePressed(const Vector &pos, const MouseKey key, Container<Transform> &stack_transform)
{
    Transform trf(getLayoutBox().getPosition(), scale_);

    stack_transform.pushBack(trf.applyPrev(stack_transform.getBack()));
    Transform last_trf = stack_transform.getBack();
    
    Dot local_pos = last_trf.applyTransform(pos);

    printf("%lg %lg\n");

    bool flag = checkIn(local_pos, getLayoutBox().getPosition());

    stack_transform.popBack();

    return flag;
}

//================================================================================

bool ColorPalette::onMouseReleased(const Vector &pos, const MouseKey key, Container<Transform> &stack_transform)
{
    bool flag = false;

    fprintf(stderr, "color palette: onMouseReleased\n");

    return flag;
}

//================================================================================

bool ColorPalette::onMouseMoved(const Vector &pos, Container<Transform> &stack_transform)
{
    bool flag = false;

    fprintf(stderr, "color palette: onMouseMove\n");

    return flag;
}

//================================================================================