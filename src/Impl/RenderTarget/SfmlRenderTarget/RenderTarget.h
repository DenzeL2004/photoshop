#ifndef __IMPL_SFML_RENDER_TARGET_H
#define __IMPL_SFML_RENDER_TARGET_H

#include "Impl/Util/Sfml.h"
#include "Plug/Graphics.h"

class SfmlRenderTarget : public plug::RenderTarget {
public:
  SfmlRenderTarget(sf::RenderTarget &target) : m_target(target) {}

  ~SfmlRenderTarget() = default;

  virtual void draw(const plug::VertexArray &array) override;

  virtual void draw(const plug::VertexArray &array,
                    const plug::Texture &texture) override;

  virtual void clear(plug::Color color) override;

  virtual void setActive(bool active) override;

private:
  sf::RenderTarget &m_target;
};

#endif