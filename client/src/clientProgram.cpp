#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <cstdlib>
#include "clientProgram.h"
#include "parameters.h"
#include "snake_body.h"
#include "communication.h"
#include "serverData.h"
#include "draw.h"

Program::Program() : _window(sf::VideoMode(WINDOW_SIZE_X, WINDOW_SIZE_Y), "The IN204 Snake", sf::Style::Close), _communication("localhost", 8001)
{
	_communication.init();
	_is_running = false;

	if (!_texture.loadFromFile("build/static/bg45.jpg")) {
		// error when load file
		exit(1);
	}
}

void Program::init () {
	_window.setVerticalSyncEnabled(true);
	// _window.setFramerateLimit(60);
	_is_running = true;
	sf::Vector2f init_pos(0,0);
	sf::Vector2f aim(1, 0);
	Snake my_snake(init_pos, aim);
	_snakes.push_back(my_snake);

	std::cout << "INitialization\n";
	std::srand(std::time(nullptr)); // use current time as seed for random generator
}

void Program::run () {
	while (_window.isOpen() && _is_running) {
		getServerData();
		
		handleEvents();

		update();

		display();
	}

	_window.close();
}

void Program::update () {
	// Refresh snake position
	std::cout << "UPDATING\n";
	_snakes[0].interpolate(_controller.getSpeed());
	std::cout << "INTERPOLATE FINISHED\n";
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
	sf::Vector2f origin = _snakes[0].getBody().getHead();

	_window.clear();

	drawTexture(_window, origin, _texture);

	drawMinimap(_window);

		for (std::list<Food>::iterator it = _foods.begin(); it != _foods.end(); it++)
	{
		drawFoods(_window, origin, *it);
	}

	for (std::vector<Snake>::iterator it = _snakes.begin(); it != _snakes.end(); it++) {
		SnakeBody snake_body = it->getBody();

		drawSnakeBody(_window, origin, snake_body);
		drawSnakeBodyMinimap(_window, snake_body);
	}
	_window.display();
}

void Program::disconnect() {
	sf::Packet dummy;
	std::cout << "Disconnect\n";
	_communication.send(DISCONNECT, dummy);
}

void Program::handleEvents () {
	sf::Event event;
	while (_window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			// Disconnect from server
			disconnect();
			// Close window
			_window.close();
		}

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
	sf::Packet packet;
	int header = 200;
	packet << _controller;
	_communication.send(header, packet);

	_controller.updateAim(); // For client refresh
}

void Program::getServerData() {
	// Receive Data from server
	sf::Packet data;
	int header;
	serverData server_data;
	_communication.receive(header, data);
	switch (header) {

	case END: 
		_snake.die();
		break;

	case OK:
		std::cout << "HEADER: " << header << "\n";
		server_data.extract(data);
		break;

	default:
		break;
	}
}
