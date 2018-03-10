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

Program::Program() : _window(sf::VideoMode(WINDOW_SIZE_X,WINDOW_SIZE_Y), "The IN204 Snake", sf::Style::Close), _communication(SERVER_ADDRESS, SERVER_PORT) {
	_is_running = false;
}

void Program::init () {
	std::cout << "Initialization\n";

	_window.setVerticalSyncEnabled(true);
	// _window.setFramerateLimit(60);

	std::unique_ptr<State> home(new HomeState(&_window, &_communication));
	std::unique_ptr<State> game(new GameState(&_window, &_communication));

	_state_manager.addState("home", home);
	_state_manager.addState("game", game);

	_is_running = true;

	// set first state
	_state_manager.initFirstState("game");

	std::srand(std::time(nullptr)); // use current time as seed for random generator
}

void Program::run () {
	while (_window.isOpen() && _is_running) {
		// std::cout << "NEW LOOP\n";

		_state_manager.getServerData();
		_state_manager.handleEvents();
		_state_manager.update();
		_state_manager.sendClientInput();
		_state_manager.display();

		_state_manager.switchState();

	}

	_window.close();
}

void Program::disconnect() {
	sf::Packet dummy;
	std::cout << "Disconnect\n";
	_communication.send(DISCONNECT, dummy);
}
