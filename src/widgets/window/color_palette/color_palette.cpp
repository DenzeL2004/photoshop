
#include "color_palatte.h"

ColorPalette::ColorPalette( const Vec2d &size, const Vec2d &pos, 
                            const Widget *parent, const Vec2d &parent_size,
                            const Vec2d &origin, const Vec2d &scale):
                            Widget(size, pos, parent, parent_size, origin, scale),
                            colors_(new sf::Color[Color_limit * 6]), active_color_(sf::Color::White), texture_()
{
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

    sf::Image img;
    img.create(Color_limit * 6, 1);

    for (size_t it = 0; it < Color_limit * 6; it++)
        img.setPixel(it, 0, colors_[it]);

    texture_.loadFromImage(img);
}


void ColorPalette::draw(sf::RenderTarget &target, Container<Transform> &stack_transform)
{   
    Transform trf(getLayoutBox().getPosition(), scale_);
    stack_transform.pushBack(trf.combine(stack_transform.getBack()));
    
    Transform last_trf = stack_transform.getBack();
   
    sf::VertexArray vertex_array(sf::Quads, 4);
    getDrawFormat(vertex_array, last_trf);

    target.draw(vertex_array, &texture_);

    stack_transform.popBack();
}


void ColorPalette::getDrawFormat(sf::VertexArray &vertex_array, Transform &trf) const
{
    sf::Vector2u texture_size = texture_.getSize();

    vertex_array[0].texCoords = sf::Vector2f(0, 0);
    vertex_array[1].texCoords = sf::Vector2f(texture_size.x, 0);
    vertex_array[2].texCoords = sf::Vector2f(texture_size.x, texture_size.y);
    vertex_array[3].texCoords = sf::Vector2f(0, texture_size.y);
    
    Dot pos = trf.apply(Dot(0, 0));
    Vec2d size = trf.getScale() * getLayoutBox().getSize();

    vertex_array[0].position = sf::Vector2f(pos.x, pos.y);
    vertex_array[1].position = sf::Vector2f(pos.x + size.x, pos.y);
    vertex_array[2].position = sf::Vector2f(pos.x + size.x, pos.y + size.y);
    vertex_array[3].position = sf::Vector2f(pos.x, pos.y + size.y);
}

//================================================================================

bool ColorPalette::onMousePressed(const Vec2d &pos, const MouseKey key, Container<Transform> &stack_transform)
{
    LayoutBox *layout_box = &getLayoutBox();

    Transform trf(layout_box->getPosition(), scale_);

    stack_transform.pushBack(trf.combine(stack_transform.getBack()));
    Transform last_trf = stack_transform.getBack();
    
    Dot local_pos = last_trf.restore(pos);

    bool flag = checkIn(local_pos);

    if (flag)
    {
        Vec2d size = last_trf.getScale() * getLayoutBox().getSize();

        sf::RenderTexture tmp;
        tmp.create(size.x, size.y);

        sf::VertexArray vertex_array(sf::Quads, 4);
        sf::Vector2u texture_size = texture_.getSize();

        vertex_array[0].texCoords = sf::Vector2f(0, 0);
        vertex_array[1].texCoords = sf::Vector2f(texture_size.x, 0);
        vertex_array[2].texCoords = sf::Vector2f(texture_size.x, texture_size.y);
        vertex_array[3].texCoords = sf::Vector2f(0, texture_size.y);

        vertex_array[0].position = sf::Vector2f(0, 0);
        vertex_array[1].position = sf::Vector2f(size.x, 0);
        vertex_array[2].position = sf::Vector2f(size.x, size.y);
        vertex_array[3].position = sf::Vector2f(0, size.y);

        tmp.draw(vertex_array, &texture_);

        sf::Texture palete_texture = tmp.getTexture();
        sf::Image palette_img = palete_texture.copyToImage();

        active_color_ = palette_img.getPixel(local_pos.x, local_pos.y);  
    }


    stack_transform.popBack();

    return flag;
}

//================================================================================

bool ColorPalette::onMouseReleased(const Vec2d &pos, const MouseKey key, Container<Transform> &stack_transform)
{
    bool flag = false;

    fprintf(stderr, "color palette: onMouseReleased\n");

    return flag;
}

//================================================================================

bool ColorPalette::onMouseMoved(const Vec2d &pos, Container<Transform> &stack_transform)
{
    bool flag = false;

    fprintf(stderr, "color palette: onMouseMove\n");

    return flag;
}

//================================================================================