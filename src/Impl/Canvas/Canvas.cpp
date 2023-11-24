#include "Canvas.h"

Canvas::Canvas(const size_t width, const size_t height):
              render_texture_(nullptr), 
              render_target_(nullptr),
              selection_mask_(nullptr)
{
    render_texture_ = new sf::RenderTexture();

    if (!render_texture_)
    {
        PROCESS_ERROR(ERR_MEMORY_ALLOC, "Failed to create render texture");
        return;
    }

    render_texture_->create(width, height);
    render_texture_->clear(sf::Color::White);

    render_target_ = new SfmlRenderTarget(*render_texture_);

    if (!render_target_)
    {   
        PROCESS_ERROR(ERR_MEMORY_ALLOC, "Failed to create render target");
        return;
    }

    selection_mask_ = new SelectionMask(width, height);
    if (!selection_mask_)
    {   
        PROCESS_ERROR(ERR_MEMORY_ALLOC, "Failed to create selection mask");
        return;
    }
}


Canvas::Canvas(char const* filename):
              render_texture_(nullptr), 
              render_target_(nullptr),
              selection_mask_(nullptr)
{
    assert(filename != nullptr && "filename is nullptr");

    sf::Image image;
    image.loadFromFile(filename);

    render_texture_ = new sf::RenderTexture();

    if (!render_texture_)
    {
        PROCESS_ERROR(ERR_MEMORY_ALLOC, "Failed to create render texture");
        return;
    }

    render_texture_->create(image.getSize().x, image.getSize().y);
    
    sf::Texture tmp_texture;
    tmp_texture.loadFromImage(image);

    sf::Sprite sprite(tmp_texture);
    
    render_texture_->draw(sprite);
    render_texture_->display();

    render_target_ = new SfmlRenderTarget(*render_texture_);

    if (!render_target_)
    {   
        PROCESS_ERROR(ERR_MEMORY_ALLOC, "Failed to create render target");
        return;
    }

    selection_mask_ = new SelectionMask(image.getSize().x, image.getSize().y);
    if (!selection_mask_)
    {   
        PROCESS_ERROR(ERR_MEMORY_ALLOC, "Failed to create selection mask");
        return;
    }
}


void Canvas::draw(const plug::VertexArray &vertex_array)
{
    render_target_->draw(vertex_array);
}

void Canvas::draw(const plug::VertexArray &vertex_array, const plug::Texture &texture)
{
    render_target_->draw(vertex_array, texture);
}

plug::Vec2d Canvas::getSize(void) const
{   
    return plug::Vec2d(render_texture_->getSize().x, render_texture_->getSize().y);
}

void Canvas::setSize(const plug::Vec2d &size)
{   
    sf::RenderTexture *new_render_texture = new sf::RenderTexture();

    if (!new_render_texture)
    {
        PROCESS_ERROR(ERR_MEMORY_ALLOC, "Failed to create render texture");
        return;
    }

    new_render_texture->create(size.x, size.y);

    sf::Sprite sprite(render_texture_->getTexture());
    new_render_texture->draw(sprite);
    new_render_texture->display();

    SfmlRenderTarget *new_render_target = new SfmlRenderTarget(*new_render_texture);

    if (!new_render_target)
    {   
        PROCESS_ERROR(ERR_MEMORY_ALLOC, "Failed to create render target");
        return;
    }

    SelectionMask *new_selection_mask = new SelectionMask(size.x, size.y, *selection_mask_);
    if (!new_selection_mask)
    {   
        PROCESS_ERROR(ERR_MEMORY_ALLOC, "Failed to create selection mask");
        return;
    }    

    delete render_texture_;
    delete render_target_;
    delete selection_mask_;

    render_texture_ = new_render_texture;
    render_target_ = new_render_target;
    selection_mask_ = new_selection_mask;
}

plug::SelectionMask& Canvas::getSelectionMask(void)
{
    return *selection_mask_;
}

plug::Color Canvas::getPixel(size_t x, size_t y) const
{
    sf::Image image = render_texture_->getTexture().copyToImage();
    sf::Color color = image.getPixel(x, y);

    return plug::Color(color.r, color.g, color.b, color.a);
}

void Canvas::setPixel(size_t x, size_t y, const plug::Color &color)
{
    plug::VertexArray vertex_array(plug::PrimitiveType::Points, 1);

    vertex_array[0].position = plug::Vec2d(x, y);
    vertex_array[0].color = color;

    render_target_->draw(vertex_array);
}

const plug::Texture& Canvas::getTexture(void) const
{
    sf::Image image = render_texture_->getTexture().copyToImage();

    size_t width  = image.getSize().x;
    size_t height = image.getSize().y;

    plug::Color *pixels = new plug::Color[width * height];

    for (size_t jt = 0; jt < height; jt++)
    {
        for (size_t it = 0; it < width; it++)
        {
            sf::Color color = image.getPixel(it, jt);
            pixels[jt * width + it] = plug::Color(color.r, color.g, color.b, color.a);
        }
    }

    return *(new plug::Texture(width, height, pixels));
}

