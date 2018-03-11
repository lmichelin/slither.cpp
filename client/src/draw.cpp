#include <SFML/Graphics.hpp>
#include "snake_body.h"
#include "food.h"

void drawShapePart(sf::RenderWindow* window, const sf::Vector2f& origin, const ShapePart& part) {
	sf::CircleShape shape(part.getRadius());
	shape.setFillColor(part.getColor());
	shape.setOrigin(part.getRadius() + origin.x - WINDOW_SIZE_X / 2, SNAKE_CIRCLE_RADIUS + origin.y - WINDOW_SIZE_Y / 2);
	shape.setPosition(part.getCoordinates());
	window->draw(shape);
}

void drawSnakeBody(sf::RenderWindow* window, const sf::Vector2f &origin, const SnakeBody &snake_body)
{
	auto parts = snake_body.getParts();
	for (snake_part_vect::const_iterator it = parts.begin(); it != parts.end(); it++) {
		drawShapePart(window, origin, *it);
	}
}

void drawFoods(sf::RenderWindow* window, const sf::Vector2f &origin, const Food &food)
{
	drawShapePart(window, origin, food.getPart());
}

void drawTexture(sf::RenderWindow* window, const sf::Vector2f &origin, const sf::Texture &texture)
{
	sf::Sprite background(texture);

	for (int i = 0; i < GAME_SIZE_X; i++)
	{
		for (int j = 0; j < GAME_SIZE_Y; j++)
		{
			background.setOrigin(origin.x - texture.getSize().x * i - (float)WINDOW_SIZE_X / 2, origin.y - texture.getSize().y * j - (float)WINDOW_SIZE_Y / 2);
			window->draw(background);
		}
	}
}

void drawMinimap(sf::RenderWindow* window)
{
	float minimap_width = (float)MINIMAP_HEIGHT * GAME_SIZE_X * BACKGROUND_SIZE_X / GAME_SIZE_Y / BACKGROUND_SIZE_Y + 2 * SNAKE_CIRCLE_RADIUS_MINIMAP;
	float minimap_height = MINIMAP_HEIGHT + 2 * SNAKE_CIRCLE_RADIUS_MINIMAP;
	sf::RectangleShape rectangle(sf::Vector2f(minimap_width, minimap_height));
	rectangle.setFillColor(sf::Color(0,0,0,150));
	rectangle.setOutlineThickness(1);
	rectangle.setOutlineColor(sf::Color(255,255,255,150));
	rectangle.setPosition(WINDOW_SIZE_X - minimap_width - 10, WINDOW_SIZE_Y - minimap_height - 10);
	window->draw(rectangle);
}

void drawSnakeBodyMinimap(sf::RenderWindow* window, const SnakeBody &snake_body, bool is_my_snake)
{
	float minimap_width = (float)MINIMAP_HEIGHT * GAME_SIZE_X * BACKGROUND_SIZE_X / GAME_SIZE_Y / BACKGROUND_SIZE_Y + 2 * SNAKE_CIRCLE_RADIUS_MINIMAP;
	sf::Vector2f minimap_origin(-WINDOW_SIZE_X + 10 + minimap_width, -WINDOW_SIZE_Y + 10 + MINIMAP_HEIGHT + 2 * SNAKE_CIRCLE_RADIUS_MINIMAP);

	float factor = (float)MINIMAP_HEIGHT / BACKGROUND_SIZE_Y / GAME_SIZE_Y;

	auto parts = snake_body.getParts();
	for (snake_part_vect::const_iterator it = parts.begin(); it != parts.end(); it++)
	{
		sf::CircleShape shape(SNAKE_CIRCLE_RADIUS_MINIMAP);
		shape.setFillColor(it->getColor());
		shape.setOrigin(minimap_origin);
		shape.setPosition(it->getCoordinates().x * factor, it->getCoordinates().y * factor);
		window->draw(shape);
	}
	if (is_my_snake) {
		sf::CircleShape shape(SNAKE_CIRCLE_RADIUS_MINIMAP);
		shape.setFillColor(sf::Color::Red);
		shape.setOrigin(minimap_origin);
		shape.setPosition(parts.begin()->getCoordinates().x * factor, parts.begin()->getCoordinates().y * factor);
		window->draw(shape);
	}
}

void drawCurrentScore(sf::RenderWindow* _window, const sf::Font& _font, int score)
{
	sf::Text text;

	text.setPosition(10,10);

	text.setFont(_font);

	text.setString(std::to_string(score));

	text.setCharacterSize(30);

	text.setColor(sf::Color::Yellow);

	text.setStyle(sf::Text::Bold);

	_window->draw(text);
}

void drawHomeMessage(sf::RenderWindow* _window, const sf::Font& _font, std::string message)
{
	sf::Text text;

	text.setFont(_font);

	text.setString(message);

	text.setCharacterSize(40);

	text.setColor(sf::Color::White);

	text.setStyle(sf::Text::Bold);

	//center text
	sf::FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
	text.setPosition(sf::Vector2f(WINDOW_SIZE_X/2.0f,WINDOW_SIZE_Y/2.0f));

	_window->draw(text);
}