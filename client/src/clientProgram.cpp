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

Program::Program() : _window(sf::VideoMode(WINDOW_SIZE_X,WINDOW_SIZE_Y), "The IN204 Snake", sf::Style::Close), _communication(SERVER_ADDRESS, SERVER_PORT), _state_manager(StateManager(&_window, &_communication)) {
	_is_running = false;
}

void Program::init () {
	_window.setVerticalSyncEnabled(true);
	// _window.setFramerateLimit(60);

	_is_running = true;

	std::cout << "Initialization\n";
	std::srand(std::time(nullptr)); // use current time as seed for random generator
}

void Program::run () {
	while (_window.isOpen() && _is_running) {
		// std::cout << "NEW LOOP\n";

		_state_manager.run();
	}

	_window.close();
}

void Program::disconnect() {
	sf::Packet dummy;
	std::cout << "Disconnect\n";
	_communication.send(DISCONNECT, dummy);
}
