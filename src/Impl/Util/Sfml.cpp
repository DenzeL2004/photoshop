#include "Sfml.h"

sf::Color getSFMLColor(const plug::Color &plug_color) {
  return sf::Color(plug_color.r, plug_color.g, plug_color.b, plug_color.a);
}

sf::Vector2f getSFMLVector2f(const plug::Vec2d &plug_vector) {
  return sf::Vector2f((float)plug_vector.x, (float)plug_vector.y);
}

plug::Color getPlugColor(const sf::Color &sf_color) {
  return plug::Color(sf_color.r, sf_color.g, sf_color.b, sf_color.a);
}

plug::Vec2d getPlugVector(const sf::Vector2f &sf_vector) {
  return plug::Vec2d(sf_vector.x, sf_vector.y);
}

plug::Vec2d getPlugVector(const sf::Vector2u &sf_vector) {
  return plug::Vec2d(sf_vector.x, sf_vector.y);
}

plug::Vec2d getPlugVector(const sf::Vector2i &sf_vector) {
  return plug::Vec2d(sf_vector.x, sf_vector.y);
}

void copyToSFMLVertex(sf::Vertex &sf_vertex, const plug::Vertex &plug_vertex) {
  sf_vertex.color = getSFMLColor(plug_vertex.color);
  sf_vertex.position = getSFMLVector2f(plug_vertex.position);
  sf_vertex.texCoords = getSFMLVector2f(plug_vertex.tex_coords);
}

void copyToSFMLVertexArray(sf::VertexArray &sf_array,
                           const plug::VertexArray &plug_array) {
  size_t size = plug_array.getSize();

  sf_array.resize(size);
  sf_array.setPrimitiveType(
      static_cast<sf::PrimitiveType>(plug_array.getPrimitive()));

  for (size_t it = 0; it < size; it++) {
    copyToSFMLVertex(sf_array[it], plug_array[it]);
  }
}

void copyToSFMLTexture(sf::Texture &sf_texture,
                       const plug::Texture &plug_texture) {
  sf::Image img;
  img.create(plug_texture.width, plug_texture.height);

  for (size_t it = 0; it < plug_texture.height; it++) {
    for (size_t jt = 0; jt < plug_texture.width; jt++) {
      img.setPixel(
          jt, it,
          getSFMLColor(plug_texture.data[it * plug_texture.width + jt]));
    }
  }

  sf_texture.loadFromImage(img);
}

plug::Texture getPlugTexture(const char *texture_path)
{
    sf::Image img;
    if (texture_path == nullptr)
    {
      img.loadFromFile(Error_texture);
    }
    else if (!img.loadFromFile(texture_path))
    {
        fprintf(stderr, "open file(\'%s\') to coppy sf::Image is failed!\n", texture_path);
        img.loadFromFile(Error_texture);
    }

    size_t width  = img.getSize().x;
    size_t height = img.getSize().y;

    plug::Color *data = new plug::Color[width * height];

    for (size_t it = 0; it < height; it++)
    {
        for (size_t jt = 0; jt < width; jt++)
        {
            data[it * width + jt] = getPlugColor(img.getPixel(jt, it));
        }
    }

    plug::Texture plug_texture(width, height, data);
    delete[] data;

    return plug_texture;
}

plug::Texture getPlugTexture(const sf::Texture &texture)
{
    sf::Image img = texture.copyToImage();

    size_t width  = img.getSize().x;
    size_t height = img.getSize().y;

    plug::Color *data = new plug::Color[width * height];

    for (size_t it = 0; it < height; it++)
    {
        for (size_t jt = 0; jt < width; jt++)
        {
            data[it * width + jt] = getPlugColor(img.getPixel(jt, it));
        }
    }

    plug::Texture plug_texture(width, height, data);
    delete[] data;
    
    return plug_texture;
}

plug::Color HSV2RGB(size_t i_hue, size_t sat, size_t val)
{
    if (!sat) return plug::Color(val, val, val);

    i_hue %= 360;

    double hue = (double)i_hue;
    int indicator = (int)(hue /= 60.0);
    
    double fr = hue - (double)indicator;

    uint8_t c1 = (val * (255 - sat)) / 255;
    uint8_t c2 = (val * (255 - sat * fr)) / 255;
    uint8_t c3 = (val * (255 - sat * (1.0 - fr))) / 255;

    uint8_t r = 0, g = 0, b = 0;
    switch (indicator)
    {
        case 0: r = val; g = c3; b = c1; break;
        case 1: r = c2; g = val; b = c1; break;
        case 2: r = c1; g = val; b = c3; break;
        case 3: r = c1; g = c2; b = val; break;
        case 4: r = c3; g = c1; b = val; break;
        case 5: r = val; g = c1; b = c2; break;
    }

    return plug::Color(r, g, b);          
}

bool checkColors(plug::Color rhs, plug::Color lhs)
{
    return (rhs.r == lhs.r && rhs.g == lhs.g && rhs.b == lhs.b);
}