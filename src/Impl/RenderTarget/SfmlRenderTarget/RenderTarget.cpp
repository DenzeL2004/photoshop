#include "RenderTarget.h"

static sf::Color getSFMLColor(const plug::Color &plug_color);
static sf::Vector2f getSFMLVector2f(const plug::Vec2d &plug_vector);

static void copyToSFMLVertex(sf::Vertex &sf_vertex,
                             const plug::Vertex &plug_vertex);
static void copyToSFMLVertexArray(sf::VertexArray &sf_array,
                                  const plug::VertexArray &plug_array);
static void copyToSFMLTexture(sf::Texture &sf_texture,
                              const plug::Texture &plug_texture);

//=======================================================================

void SfmlRenderTarget::draw(const plug::VertexArray &array) {
  sf::VertexArray sf_array;
  copyToSFMLVertexArray(sf_array, array);

  m_target.draw(sf_array);
}

void SfmlRenderTarget::draw(const plug::VertexArray &array,
                            const plug::Texture &texture) {
  sf::VertexArray sf_array;
  copyToSFMLVertexArray(sf_array, array);

  sf::Texture sf_texture;
  copyToSFMLTexture(sf_texture, texture);

  m_target.draw(sf_array, &sf_texture);
}

void SfmlRenderTarget::clear(plug::Color color) {
  m_target.clear(getSFMLColor(color));
}

void SfmlRenderTarget::setActive(bool active) { m_target.setActive(active); }

//=======================================================================

static sf::Color getSFMLColor(const plug::Color &plug_color) {
  return sf::Color(plug_color.r, plug_color.g, plug_color.b, plug_color.a);
}

static sf::Vector2f getSFMLVector2f(const plug::Vec2d &plug_vector) {
  return sf::Vector2f((float)plug_vector.x, (float)plug_vector.y);
}

static void copyToSFMLVertex(sf::Vertex &sf_vertex,
                             const plug::Vertex &plug_vertex) {
  sf_vertex.color = getSFMLColor(plug_vertex.color);
  sf_vertex.position = getSFMLVector2f(plug_vertex.position);
  sf_vertex.texCoords = getSFMLVector2f(plug_vertex.tex_coords);
}

static void copyToSFMLVertexArray(sf::VertexArray &sf_array,
                                  const plug::VertexArray &plug_array) {
  size_t size = plug_array.getSize();

  sf_array.resize(size);
  sf_array.setPrimitiveType(
      static_cast<sf::PrimitiveType>(plug_array.getPrimitive()));

  for (size_t it = 0; it < size; it++) {
    copyToSFMLVertex(sf_array[it], plug_array[it]);
  }
}

static void copyToSFMLTexture(sf::Texture &sf_texture,
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