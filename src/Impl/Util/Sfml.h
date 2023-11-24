#ifndef __IMPL_UTIL_SFML_H
#define __IMPL_UTIL_SFML_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cstdio>

#include "Plug/Graphics.h"

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

#endif
