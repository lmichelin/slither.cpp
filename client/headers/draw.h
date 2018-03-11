#ifndef _DRAW_H
#define _DRAW_H

#include <SFML/Graphics.hpp>
#include "snake_body.h"
#include "parts.h"

void drawShapePart(sf::RenderWindow*, const sf::Vector2f&, const ShapePart&);

void drawTexture(sf::RenderWindow* , const sf::Vector2f &, const sf::Texture &);

void drawSnakeBody(sf::RenderWindow* , const sf::Vector2f &, const SnakeBody &);

void drawFoods(sf::RenderWindow* , const sf::Vector2f &, const Food &);

void drawMinimap(sf::RenderWindow* window);

void drawSnakeBodyMinimap(sf::RenderWindow* window, const SnakeBody &snake_body, bool is_my_snake=false);

void drawCurrentScore(sf::RenderWindow* window, const sf::Font& _font, int score);

void drawHomeMessage(sf::RenderWindow* _window, const sf::Font& _font, std::string message);

#endif