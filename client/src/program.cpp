#include <SFML/Graphics.hpp>
// #include <SFML/Network.hpp>
#include <iostream>
#include <cstdlib>
#include "program.h"
#include "parameters.h"
#include "snake_body.h"
// #include "communication.h"

Program::Program () : _window(sf::VideoMode(WINDOW_SIZE_X, WINDOW_SIZE_Y), "The IN204 Snake", sf::Style::Close) {
	_is_running = false;
}

void Program::init () {
	_window.setVerticalSyncEnabled(true);
	_is_running = true;
	sf::Vector2f init_pos(200,200);
	Snake my_snake(init_pos);
	_snakes.push_back(my_snake);

	std::srand(std::time(nullptr)); // use current time as seed for random generator
}

void Program::run () {
	while (_window.isOpen() && _is_running) {
		handleEvents();

		update();

		display();
	}

	_window.close();
}

void Program::update () {
	// Refresh snake position
	sf::Vector2f head_aim = _controller.getAim();
	_snakes[0].interpolate(head_aim, _controller.getSpeed());
	if (std::rand()/(float)RAND_MAX < FOOD_PROBA) {
		sf::Vector2f new_food_position(std::rand()*(float)WINDOW_SIZE_X/RAND_MAX,std::rand()*(float)WINDOW_SIZE_Y/RAND_MAX);
		Food new_food(new_food_position);
		_foods.push_back(new_food);
	}

	for (std::list<Food>::iterator it = _foods.begin(); it != _foods.end(); it++) {
		if (_snakes[0].checkFoodIntersection(*it)) {
			it = _foods.erase(it);
			_snakes[0].addTail(ADD_TAIL);
		}
	}

	// End game test
	// if (position.x < SNAKE_CIRCLE_RADIUS || position.x > WINDOW_SIZE_X - SNAKE_CIRCLE_RADIUS || position.y < SNAKE_CIRCLE_RADIUS || position.y > WINDOW_SIZE_Y - SNAKE_CIRCLE_RADIUS) {
	// 	_is_running = false;
	// }
}

void Program::display () {
	_window.clear();

	for (std::list<Food>::iterator it = _foods.begin(); it != _foods.end(); it++) {
		drawFoods(_window, *it);
	}

	for (std::vector<Snake>::iterator it = _snakes.begin(); it != _snakes.end(); it++) {
		SnakeBody snake_body = it->getBody();

		drawSnakeBody(_window, snake_body);
	}

	_window.display();
}

void Program::handleEvents () {
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

	// Update controller
	// Create Packet and send
	// sf::Packet packet;
	// packet << _controller;
	// _communication.send(packet);
	_controller.updateAim(); // For client refresh
}
