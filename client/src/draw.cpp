#include <SFML/Graphics.hpp>
#include "snake_body.h"
#include "food.h"

void drawSnakeBody (sf::RenderWindow& window, const SnakeBody& snake_body) {
	for (coord_vect::const_iterator it = snake_body._parts.begin(); it != snake_body._parts.end(); it++) {
		sf::CircleShape shape(SNAKE_CIRCLE_RADIUS);
		shape.setFillColor(sf::Color::Red);
		shape.setOrigin(SNAKE_CIRCLE_RADIUS,SNAKE_CIRCLE_RADIUS);
		shape.setPosition(*it);
		window.draw(shape);
	}
}

void drawFoods (sf::RenderWindow& window, const Food& food) {
	sf::CircleShape shape(FOOD_CIRCLE_RADIUS);
	shape.setFillColor(sf::Color::White);
	shape.setOrigin(FOOD_CIRCLE_RADIUS,FOOD_CIRCLE_RADIUS);
	shape.setPosition(food._position);
	window.draw(shape);
}