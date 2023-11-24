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
