#ifndef __IMPL_UTIL_SFML_H
#define __IMPL_UTIL_SFML_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cstdio>

#include "Plug/Graphics.h"

static const char Error_texture[] = "src/img/ErrorTexture.png";

sf::Color getSFMLColor(const plug::Color &plug_color);
sf::Vector2f getSFMLVector2f(const plug::Vec2d &plug_vector);

plug::Color getPlugColor(const sf::Color &sf_color);
plug::Vec2d getPlugVector(const sf::Vector2f &sf_vector);
plug::Vec2d getPlugVector(const sf::Vector2u &sf_vector);
plug::Vec2d getPlugVector(const sf::Vector2i &sf_vector);

void copyToSFMLVertex(sf::Vertex &sf_vertex, const plug::Vertex &plug_vertex);
void copyToSFMLVertexArray(sf::VertexArray &sf_array,
                           const plug::VertexArray &plug_array);
void copyToSFMLTexture(sf::Texture &sf_texture,
                       const plug::Texture &plug_texture);

plug::Texture getPlugTexture(const char *texture_path);

plug::Texture getPlugTexture(const sf::Texture &texture);

plug::Color HSV2RGB(size_t i_hue, size_t sat, size_t val);


#endif
