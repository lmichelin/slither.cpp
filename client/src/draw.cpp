#include <SFML/Graphics.hpp>
#include "snake_body.h"
#include "food.h"

void drawSnakeBody(sf::RenderWindow &window, const sf::Vector2f &origin, const sf::Vector2f &center, const SnakeBody &snake_body)
{
	auto parts = snake_body.getParts();
	for (coord_vect::const_iterator it = parts.begin(); it != parts.end(); it++) {
		sf::CircleShape shape(SNAKE_CIRCLE_RADIUS);
		shape.setFillColor(sf::Color::Red);
		shape.setOrigin(SNAKE_CIRCLE_RADIUS + origin.x - center.x, SNAKE_CIRCLE_RADIUS + origin.y - center.y);
		shape.setPosition(*it);
		window.draw(shape);
	}
}

void drawFoods(sf::RenderWindow &window, const sf::Vector2f &origin, const sf::Vector2f &center, const Food &food)
{
	sf::CircleShape shape(FOOD_CIRCLE_RADIUS);
	shape.setFillColor(sf::Color::White);
	shape.setOrigin(FOOD_CIRCLE_RADIUS + origin.x - center.x, FOOD_CIRCLE_RADIUS + origin.y - center.y);
	shape.setPosition(food.getPosition());
	window.draw(shape);
}

void drawTexture(sf::RenderWindow &window, const sf::Vector2f &origin, const sf::Vector2f &center, const sf::Texture &texture)
{
	sf::Sprite background(texture);

	int bg_init_x = ((GAME_SIZE_X - 1) / (float)texture.getSize().x + 1) / 2;
	int bg_init_y = ((GAME_SIZE_Y - 1) / (float)texture.getSize().y + 1) / 2;

	for (int i = -bg_init_x; i <= bg_init_x; i++)
	{
		for (int j = -bg_init_y; j <= bg_init_y; j++)
		{
			background.setOrigin((float)(texture.getSize().x) * i + texture.getSize().x / 2 + origin.x - center.x, (float)(texture.getSize().y) * j + texture.getSize().y / 2 + origin.y - center.y);
			window.draw(background);
		}
	}
}