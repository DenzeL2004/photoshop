#include "Canvas.h"

Canvas::Canvas(const size_t width, const size_t height, const plug::Color color):
              m_render_texture(nullptr), 
              m_render_target(nullptr),
              m_selection_mask(nullptr),
              m_texture(nullptr)
{
    m_render_texture = new sf::RenderTexture();

    if (!m_render_texture)
    {
        PROCESS_ERROR(ERR_MEMORY_ALLOC, "Failed to create render texture");
        return;
    }

    m_render_texture->create(width, height);
    m_render_texture->clear(getSFMLColor(color));

    m_render_target = new SfmlRenderTarget(*m_render_texture);

    if (!m_render_target)
    {   
        PROCESS_ERROR(ERR_MEMORY_ALLOC, "Failed to create render target");
        return;
    }

    m_selection_mask = new SelectionMask(width, height);
    if (!m_selection_mask)
    {   
        PROCESS_ERROR(ERR_MEMORY_ALLOC, "Failed to create selection mask");
        return;
    }

    m_texture = new plug::Texture(width, height);
    if (!m_selection_mask)
    {   
        PROCESS_ERROR(ERR_MEMORY_ALLOC, "Failed to create texture");
        return;
    }

    m_selection_mask->fill(true);
}

Canvas::Canvas(char const* filename):
              m_render_texture(nullptr), 
              m_render_target(nullptr),
              m_selection_mask(nullptr),
              m_texture(nullptr)
{
    assert(filename != nullptr && "filename is nullptr");

    sf::Image image;
    image.loadFromFile(filename);

    m_render_texture = new sf::RenderTexture();

    if (!m_render_texture)
    {
        PROCESS_ERROR(ERR_MEMORY_ALLOC, "Failed to create render texture");
        return;
    }

    size_t width  = image.getSize().x;
    size_t height = image.getSize().y;

    m_render_texture->create(width, height);
    m_render_texture->clear(sf::Color::White);
    
    sf::Texture tmp_texture;
    tmp_texture.loadFromImage(image);

    sf::Sprite sprite(tmp_texture);
    
    m_render_texture->draw(sprite);
    m_render_texture->display();

    m_render_target = new SfmlRenderTarget(*m_render_texture);

    if (!m_render_target)
    {   
        PROCESS_ERROR(ERR_MEMORY_ALLOC, "Failed to create render target");
        return;
    }

    m_selection_mask = new SelectionMask(width, height);
    if (!m_selection_mask)
    {   
        PROCESS_ERROR(ERR_MEMORY_ALLOC, "Failed to create selection mask");
        return;
    }

    m_texture = new plug::Texture(width, height);
    if (!m_selection_mask)
    {   
        PROCESS_ERROR(ERR_MEMORY_ALLOC, "Failed to create texture");
        return;
    }

    m_selection_mask->fill(true);
}

void Canvas::draw(const plug::VertexArray &vertex_array)
{
    m_render_target->draw(vertex_array);
    m_render_texture->display();
}

void Canvas::draw(const plug::VertexArray &vertex_array, const plug::Texture &texture)
{
    m_render_target->draw(vertex_array, texture);
    m_render_texture->display();
}

plug::Vec2d Canvas::getSize(void) const
{   
    return plug::Vec2d(m_render_texture->getSize().x, m_render_texture->getSize().y);
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
    new_render_texture->clear(sf::Color::White);
    
    sf::Sprite sprite(m_render_texture->getTexture());
    new_render_texture->draw(sprite);
    new_render_texture->display();

    SfmlRenderTarget *new_render_target = new SfmlRenderTarget(*new_render_texture);
    if (!new_render_target)
    {   
        PROCESS_ERROR(ERR_MEMORY_ALLOC, "Failed to create render target");
        return;
    }

    SelectionMask *new_selection_mask = new SelectionMask(size.x, size.y, *m_selection_mask);
    if (!new_selection_mask)
    {   
        PROCESS_ERROR(ERR_MEMORY_ALLOC, "Failed to create selection mask");
        return;
    }   

    plug::Texture *new_texture = new plug::Texture(size.x, size.y);

    delete m_render_texture;
    delete m_render_target;
    delete m_selection_mask;
    delete m_texture;

    m_render_texture    = new_render_texture;
    m_render_target     = new_render_target;
    m_selection_mask    = new_selection_mask;
    m_texture           = new_texture;

    m_selection_mask->fill(true);

    getTexture();
}

plug::SelectionMask& Canvas::getSelectionMask(void)
{
    return *m_selection_mask;
}

plug::Color Canvas::getPixel(size_t x, size_t y) const
{
    return m_texture->getPixel(x, y);
}

void Canvas::setPixel(size_t x, size_t y, const plug::Color &color)
{
    plug::VertexArray vertex_array(plug::PrimitiveType::Points, 1);

    vertex_array[0].position = plug::Vec2d(x, y);
    vertex_array[0].color = color;

    draw(vertex_array);
}

const plug::Texture& Canvas::getTexture(void) const
{
    assert(m_texture != nullptr && "texture is nullptr");

    sf::Image image = m_render_texture->getTexture().copyToImage();

    size_t width  = image.getSize().x;
    size_t height = image.getSize().y;
    
    for (size_t y = 0; y < height; y++)
    {
        for (size_t x = 0; x < width; x++)
        {
            sf::Color color = image.getPixel(x, y);
            m_texture->setPixel(x, y, plug::Color(color.r, color.g, color.b, color.a));
        }
    }

    return *m_texture;
}
