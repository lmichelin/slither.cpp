#ifndef _DRAW_H
#define _DRAW_H

#include <SFML/Graphics.hpp>
#include "snake_body.h"

void drawTexture(sf::RenderWindow &, const sf::Vector2f &, const sf::Vector2f &, const sf::Texture &);

void drawSnakeBody(sf::RenderWindow &, const sf::Vector2f &, const sf::Vector2f &, const SnakeBody &);

void drawFoods(sf::RenderWindow &, const sf::Vector2f &, const sf::Vector2f &, const Food &);

#endif