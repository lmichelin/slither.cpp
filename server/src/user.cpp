#include "user.h"
#include "clientData.h"
#include <iostream>

void User::run() {
	std::cout << "User with socket " << _socket->getRemoteAddress() << " now running" << std::endl;

	while (_is_connected) {

		/////////////////////////////
		// HANDLE SOCKET RECEPTION //
		/////////////////////////////

		processClientInput();

		///////////////////////////////////////
		// POSITIONS AND INTERSECTIONS AWAIT //
		//////////////////////////////////////

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
}

void User::computeIntersection() {
	std::cout << "INTERSECTION\n";
}

void User::processClientInput() {
	sf::Packet input;
	int header;
	receive(header, input);

	// FOR DEBUG ONLY //
	int x;
	input >> x;
	////////////////////

	switch (header) {
	
	case OK:
		std::cout << "OK the server received the packet: " << x << "\n";
		break;
	
	case DISCONNECT:
		_is_connected = false;
		std::cout << "The client has disconnected normally\n";
		break;
	
	default:
		break;
	}
}

void User::sendClientData() {
	Data clientData;
	sf::Vector2f coord(50,50);
	clientData.my_snake_coord.push_back(coord);
	std::cout << "COORD: " << clientData.my_snake_coord[0].x << "\n"; 
	sf::Packet packet;
	packet << clientData;
	std::cout << "Sending client data\n";
	send(OK, packet);
}

