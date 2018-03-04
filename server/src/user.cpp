#include "user.h"
#include "clientData.h"
#include <iostream>
#include <list>

void User::run() {
	std::cout << "User with socket " << _socket->getRemoteAddress() << " now running" << std::endl;

	while (_is_connected) {

		/////////////////////////////
		// HANDLE SOCKET RECEPTION //
		/////////////////////////////

		processClientInput();

		///////////////////////////////////////
		// POSITIONS AND INTERSECTIONS AWAIT //
		///////////////////////////////////////

		std::unique_lock<std::mutex> lk_compute(m_compute);
		// std::cout << "User waiting\n"; // THREAD DEBUGGING
		cv_compute.wait(lk_compute);
		play();

		computeIntersection();
		computePosition();
		
		done_users_count++;
		if (done_users_count >= getUserPlayingCount()) { // IMPORTANT SO THAT NO USER CAN DODGE WITH DISCONNECTION
			// std::cout << "User notifying\n"; // THREAD DEBUGGING
			cv_ready_compute.notify_one();
		}

		/////////////////////////////
		// SEND NEW DATA TO CLIENT //
		/////////////////////////////

		sendClientData();
	}
	std::cout << "Not playing anymore\n";
	_is_playing = false;
	addToUserPlayingCount(-1);
}

void User::send(int header, sf::Packet packet) {
	Server::send(*_socket, header, packet);
}

void User::receive(int& header, sf::Packet& packet) {
	Server::receive(*_socket, header, packet);
}

void User::computePosition() {
	std::cout << "POSITION\n";

	// Refresh snake position and put it into data to be sent to client
	updateUserPosition();

	// Refresh other user positions and put it into data to be sent to client
	updateOtherUserPositions();
}

void User::computeIntersection() {
	std::cout << "INTERSECTION\n";
}

void User::processClientInput() {
	sf::Packet input;
	int header;
	receive(header, input);

	switch (header) {
	
	case OK:
		input >> _input;
		break;
	
	case DISCONNECT:
		_is_connected = false;
		std::cout << "The client has disconnected normally\n";
		break;
	
	default:
		break;
	}
}

void User::updateOtherUserPositions() {
	std::vector<std::vector<sf::Vector2f> > result;
	std::list<User>::iterator it_user;
	for (it_user = _users->begin(); it_user != _users->end(); it_user++) {
		if (&(*it_user) != this) {
			result.push_back(it_user->getSnake().getBody().getParts());	
		}
	}
	_clientData.snakes_coord_vector = result;
}

void User::updateUserPosition() {
	_snake.updateAim(_input);
	_snake.interpolate(getSpeed());
	_clientData.my_snake_coord = _snake.getBody().getParts();
}

void User::sendClientData() {
	sf::Packet packet;
	packet << _clientData;
	std::cout << "Sending client data\n";
	send(OK, packet);
}

