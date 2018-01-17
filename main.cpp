#include <unistd.h>
#include <SFML/Graphics.hpp>
#include "parameters.h"
#include <math.h>

int main()
{
	sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE_X, WINDOW_SIZE_Y), "The IN204 Snake", sf::Style::Close);
	window.setVerticalSyncEnabled(true);
	sf::CircleShape shape(SNAKE_CIRCLE_RADIUS);
	shape.setFillColor(sf::Color::Red);
	shape.setOrigin(SNAKE_CIRCLE_RADIUS,SNAKE_CIRCLE_RADIUS);

	sf::Vector2f position(SNAKE_CIRCLE_RADIUS,SNAKE_CIRCLE_RADIUS);
	float angular = M_PI/4;

	float speed = 2;
	bool movingRight = 0;
	bool movingLeft = 0;

	while (window.isOpen())
	{

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			window.close();

			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Space || event.key.code == sf::Keyboard::Up) {
					speed = 4;
				}
				if (event.key.code == sf::Keyboard::Right) {
					movingRight = 1;
				}
				if (event.key.code == sf::Keyboard::Left) {
					movingLeft = 1;
				}
			}
			if (event.type == sf::Event::KeyReleased) {
				if (event.key.code == sf::Keyboard::Space || event.key.code == sf::Keyboard::Up) {
					speed = 2;
				}
				if (event.key.code == sf::Keyboard::Right) {
					movingRight = 0;
				}
				if (event.key.code == sf::Keyboard::Left) {
					movingLeft = 0;
				}
			}
		}
		angular += movingLeft*0.02*M_PI + movingRight*-0.02*M_PI;

		position.x += speed * sin(angular);
		position.y += speed * cos(angular);

		shape.setPosition(position);
		window.clear();
		window.draw(shape);
		window.display();

		if (position.x < SNAKE_CIRCLE_RADIUS || position.x > WINDOW_SIZE_X - SNAKE_CIRCLE_RADIUS || position.y < SNAKE_CIRCLE_RADIUS || position.y > WINDOW_SIZE_Y - SNAKE_CIRCLE_RADIUS) {
			window.close();
		}
	}

	return 0;
}
