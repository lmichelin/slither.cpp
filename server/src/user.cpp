#include "user.h"
#include "serverData.h"
#include "input.h"
#include <iostream>
#include <list>
#include <cmath>

void User::processPlayerInput() {
	sf::Packet input_packet;
	sf::Socket::Status status;
	int header;
	_communication.receivePacket(header, input_packet, status);

	if (status == sf::Socket::Done) {
		// Reset disconnect timer
		_disconnectTimeHandler.reset();

		switch (header) {
		
		case OK:
			_client_input.extract(input_packet);
			_input = _client_input.getData();
			_has_received_data = true;	
			break;
		
		case DISCONNECT:
			endGame();
			break;
		
		default:
			break;
		}

	// If no messages have been received ...
	} else if (status == sf::Socket::Disconnected || (status == sf::Socket::NotReady && _is_running)) {

		// Update disconnect time
		_disconnectTimeHandler.updateElapsedTime();

		// Check if disconnection time is too great and disconnect the client if it is the case
		if (_disconnectTimeHandler.getElapsedTime().count() > INACTIVITY_TIMEOUT)
			endGame();
	}
}

void User::processOutput() {
	if (_has_received_data) {
		packageServerData();
		_communication.send(OK, _serverData.getData());
		_has_received_data = false;
	}
}

void User::packageServerData() {
	data send_data;

	snake_data my_snake;
	my_snake.id = _id;
	my_snake.parts = _snake.getBody().getParts();

	send_data.my_snake = my_snake;

	std::list<Player*>::iterator it_player;
	for (it_player = getPlayers().begin(); it_player != getPlayers().end(); it_player++) {
		if (*it_player != this && (*it_player)->isRunning() && (*it_player)->isPlaying()) {
			snake_data snake_element;
			snake_element.id = (*it_player)->getId();
			snake_element.parts = (*it_player)->getSnake().getBody().getParts();
			send_data.snakes.push_back(snake_element);	
		}
	}

	// ADD FOODS
	std::list<Food>::iterator it_food;
	for (it_food = getFoods().begin(); it_food != getFoods().end(); it_food++) {
		send_data.food_vector.push_back(it_food->getPart());
	}

	// Package
	_serverData.setData(send_data);
}

void User::disconnect() {
	_is_connected = false;
	std::cout << "The client has disconnected\n";
}

void User::endGame() {
	_communication.send(500);
	_is_running = false;
}