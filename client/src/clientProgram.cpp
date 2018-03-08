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

Program::Program() : _window(sf::VideoMode(1200,800), "The IN204 Snake", sf::Style::Close), _communication("localhost", 8001), _has_received_data(false)
{
	_communication.init();
	_is_running = false;
	_window_height = _window.getSize().y; // horizontal dimension
	_window_width = _window.getSize().x; // vertical dimension
	_window_center.x = _window_width / 2;
	_window_center.y = _window_height / 2;

	if (!_texture.loadFromFile("build/static/bg45.jpg")) {
		// error when load file
		exit(1);
	}
}

void Program::init () {
	_window.setVerticalSyncEnabled(true);
	// _window.setFramerateLimit(60);

	// TODO Add server snake
	_snake.getBody().addPart(sf::Vector2f(0.15, 5.0));

	_is_running = true;

	std::cout << "Initialization\n";
	std::srand(std::time(nullptr)); // use current time as seed for random generator
}

void Program::run () {
	while (_window.isOpen() && _is_running) {
		std::cout << "NEW LOOP\n";

		handleEvents();
		
		getServerData();

		sendClientInput();

		update();

		display();
	}

	_window.close();
}

void Program::update () {
	// if (_has_received_data) {
	// 	auto data = _serverData.getData();

	// 	_snake.updateBody(data.my_snake.coordinates);0
		
	// 	for (size_t i = 0; i < data.snakes.size(); i++) {
	// 		// If the user does not already exist ...
	// 		if (_snakes.find(data.snakes[i].id) == _snakes.end())
	// 			_snakes[data.snakes[i].id] = Snake(data.snakes[i].coordinates);

	// 		// The user already exists --> Update his coordinates
	// 		else
	// 			_snakes[data.snakes[i].id] = data.snakes[i].coordinates;
	// 	}

	// 	// Clean the rest of the snakes (who dies or disconnected)
	// 	std::map<unsigned int, Snake>::iterator it_snake;
	// 	for (it_snake = _snakes.begin(); it_snake != _snakes.end(); it_snake++) {
	// 		bool flag = false;
	// 		for (size_t i = 0; i < data.snakes.size(); i++) {
	// 			if (it_snake->first == data.snakes[i].id) {
	// 				flag = true;
	// 				break;
	// 			}
	// 		}
	// 		if (!flag)
	// 			_snakes.erase(it_snake);
	// 	}
	// }
}

void Program::display () {
	sf::Vector2f origin = _snake.getBody().getHead();

	_window.clear();
	
	// Draw Background
	drawTexture(_window, origin, _window_center, _texture);

	// Draw the foods
	for (std::list<Food>::iterator it = _foods.begin(); it != _foods.end(); it++) {
		drawFoods(_window, origin, _window_center, *it);
	}

	// Draw my snake
	drawSnakeBody(_window, origin, _window_center, _snake.getBody());

	// Draw all the other snakes
	for (std::map<unsigned int, Snake>::iterator it = _snakes.begin(); it != _snakes.end(); it++) {
		drawSnakeBody(_window, origin, _window_center, it->second.getBody());
	}

	// Display Result
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
}

void Program::getServerData() {
	// Receive Data from server
	sf::Packet data;
	int header;
	_communication.receivePacket(header, data);
	std::cout << "HEADER: " << header << "\n";
	_has_received_data = true;
	switch (header) {

	case END: 
		_snake.die();
		break;

	case OK:
		_serverData.extract(data);
		break;

	default:
		break;
	}
}

void Program::sendClientInput() {
	if (_has_received_data) {
		_communication.send(OK, _controller.getInput());
		_has_received_data = false;
	}
}