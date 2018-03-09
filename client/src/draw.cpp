#include <SFML/Graphics.hpp>
#include "snake_body.h"
#include "food.h"

void drawSnakeBody(sf::RenderWindow &window, const sf::Vector2f &origin, const SnakeBody &snake_body)
{
	auto parts = snake_body.getParts();
	for (coord_vect::const_iterator it = parts.begin(); it != parts.end(); it++) {
		sf::CircleShape shape(SNAKE_CIRCLE_RADIUS);
		shape.setFillColor(sf::Color::Red);
		shape.setOrigin(SNAKE_CIRCLE_RADIUS + origin.x - WINDOW_SIZE_X / 2, SNAKE_CIRCLE_RADIUS + origin.y - WINDOW_SIZE_Y / 2);
		shape.setPosition(*it);
		window.draw(shape);
	}
}

void drawFoods(sf::RenderWindow &window, const sf::Vector2f &origin, const Food &food)
{
	sf::CircleShape shape(FOOD_CIRCLE_RADIUS);
	shape.setFillColor(sf::Color::White);
	shape.setOrigin(FOOD_CIRCLE_RADIUS + origin.x - WINDOW_SIZE_X / 2, FOOD_CIRCLE_RADIUS + origin.y - WINDOW_SIZE_Y / 2);
	shape.setPosition(food.getPosition());
	window.draw(shape);
}

void drawTexture(sf::RenderWindow &window, const sf::Vector2f &origin, const sf::Texture &texture)
{
	sf::Sprite background(texture);

	for (int i = 0; i <= GAME_SIZE_X; i++)
	{
		for (int j = 0; j <= GAME_SIZE_Y; j++)
		{
			background.setOrigin(origin.x - texture.getSize().x * i - (float)WINDOW_SIZE_X / 2, origin.y - texture.getSize().y * j - (float)WINDOW_SIZE_Y / 2);
			window.draw(background);
		}
	}
}

void drawMinimap(sf::RenderWindow &window)
{
	float minimap_width = (float)MINIMAP_HEIGHT * GAME_SIZE_X / GAME_SIZE_Y + 4 * SNAKE_CIRCLE_RADIUS_MINIMAP;
	float minimap_height = MINIMAP_HEIGHT + 4 * SNAKE_CIRCLE_RADIUS_MINIMAP;
	sf::RectangleShape rectangle(sf::Vector2f(minimap_width, minimap_height));
	rectangle.setFillColor(sf::Color(0,0,0,150));
	rectangle.setPosition(WINDOW_SIZE_X - minimap_width - 10, WINDOW_SIZE_Y - minimap_height - 10);
	window.draw(rectangle);
}

void drawSnakeBodyMinimap(sf::RenderWindow &window, const SnakeBody &snake_body)
{
	float minimap_width = (float)MINIMAP_HEIGHT * GAME_SIZE_X / GAME_SIZE_Y;
	sf::Vector2f minimap_origin(4 * SNAKE_CIRCLE_RADIUS_MINIMAP - WINDOW_SIZE_X + 10 + minimap_width, 4 * SNAKE_CIRCLE_RADIUS_MINIMAP - WINDOW_SIZE_Y + 10 + MINIMAP_HEIGHT);

	float factor = (float)MINIMAP_HEIGHT / WINDOW_SIZE_Y / GAME_SIZE_Y;

	auto parts = snake_body.getParts();
	for (coord_vect::const_iterator it = parts.begin(); it != parts.end(); it++)
	{
		sf::CircleShape shape(SNAKE_CIRCLE_RADIUS_MINIMAP);
		shape.setFillColor(sf::Color::Red);
		shape.setOrigin(minimap_origin);
		shape.setPosition(it->x * factor, it->y * factor);
		window.draw(shape);
	}
}
