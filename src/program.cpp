#include <iostream>
#include "program.h"
#include "parameters.h"
#include <SFML/Graphics.hpp>

Program::Program () {
	_is_running = true;
}

void Program::run () {
	sf::RenderWindow _window(sf::VideoMode(WINDOW_SIZE_X, WINDOW_SIZE_Y), "The IN204 Snake", sf::Style::Close);
	_window.setVerticalSyncEnabled(true);
	while (_window.isOpen() && _is_running) {
		// handleEvents();

		update();

		// display();
		sf::Event event;
		while (_window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
			_window.close();

			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Space || event.key.code == sf::Keyboard::Up) {
					_controller.setSpeed(HIGH_SPEED);
				}
				if (event.key.code == sf::Keyboard::Right) {
					_controller.rotateRight(true);
				}
				if (event.key.code == sf::Keyboard::Left) {
					_controller.rotateLeft(true);
				}
			}
			if (event.type == sf::Event::KeyReleased) {
				if (event.key.code == sf::Keyboard::Space || event.key.code == sf::Keyboard::Up) {
					_controller.setSpeed(LOW_SPEED);
				}
				if (event.key.code == sf::Keyboard::Right) {
					_controller.rotateRight(false);
				}
				if (event.key.code == sf::Keyboard::Left) {
					_controller.rotateLeft(false);
				}
			}
		}
		sf::CircleShape shape(SNAKE_CIRCLE_RADIUS);
		shape.setFillColor(sf::Color::Red);
		shape.setOrigin(SNAKE_CIRCLE_RADIUS,SNAKE_CIRCLE_RADIUS);

		sf::Vector2f position(SNAKE_CIRCLE_RADIUS,SNAKE_CIRCLE_RADIUS);

		shape.setPosition(position);

		_window.clear();
		_window.draw(shape);
		_window.display();

	}

	_window.close();
}

void Program::update () {
	// Refresh snake position
	_controller.updateAim();
	// End game test
	// if (position.x < SNAKE_CIRCLE_RADIUS || position.x > WINDOW_SIZE_X - SNAKE_CIRCLE_RADIUS || position.y < SNAKE_CIRCLE_RADIUS || position.y > WINDOW_SIZE_Y - SNAKE_CIRCLE_RADIUS) {
	// 	_is_running = false;
	// }
}

void Program::display () {
}

void Program::handleEvents() {

}
