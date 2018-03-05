#include "user.h"
#include "clientData.h"
#include <iostream>
#include <list>

void User::init() {
	// Generate initial position
	// generateRandomInitialPosition();

	// Run the user
	run();
}

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

void User::send(int header, sf::Packet packet, sf::Socket::Status& status) {
	Server::send(*_socket, header, packet, status);
}

void User::send(int header, sf::Packet packet) {
	Server::send(*_socket, header, packet);
}

void User::receive(int& header, sf::Packet& packet, sf::Socket::Status& status) {
	Server::receive(*_socket, header, packet, status);
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
	sf::Socket::Status status;
	int header;
	receive(header, input, status);


	if (status == sf::Socket::Done) {
		_elapsed_disconnect_time = std::chrono::milliseconds::zero();
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
	} else if (status == sf::Socket::Disconnected) {
		if (_elapsed_disconnect_time == std::chrono::milliseconds::zero()) {
			std::cout << "HELLLLOOOOOO\n";
			_elapsed_disconnect_time = ms(10);
			_disconnect_time = Time::now();
		} else {
			fsec fs = Time::now() - _disconnect_time;
			_elapsed_disconnect_time = std::chrono::duration_cast<ms>(fs);
			std::cout << "Elapsed time: " << _elapsed_disconnect_time.count() << "\n";

			if (_elapsed_disconnect_time.count() > 1000) {
				_is_connected = false;
				std::cout << "The client has disconnected\n";
			}
		}
	}
}

void User::generateRandomInitialPosition() {
	sf::Vector2f position(std::rand()*(float)GAME_SIZE_X/RAND_MAX, std::rand()*(float)GAME_SIZE_Y/RAND_MAX);
	Snake _snake(position);
	bool flag = false;
	std::list<User>::iterator it_user;
	for (it_user = _users->begin(); it_user != _users->end(); it_user++) {
		flag = _snake.getBody().checkIntersection(it_user->_snake.getBody(), 10*SNAKE_CIRCLE_RADIUS);	
		if (flag)
			break;
	}
	if (flag)
		return generateRandomInitialPosition();
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

