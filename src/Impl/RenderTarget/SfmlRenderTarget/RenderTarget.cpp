#include "RenderTarget.h"

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
