#include "user.h"
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
		cv_compute.wait(lk_compute);
		play();

		computeIntersection();
		computePosition();
		
		done_users_count++;
		if (done_users_count >= getUserPlayingCount()) { // IMPORTANT SO THAT NO USER CAN DODGE WITH DISCONNECTION
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

	switch (header) {
	
	case OK:
		std::cout << "OK the server received the packet: " << input << "\n";
		break;
	
	case DISCONNECT:
		_is_connected = false;
		std::cout << "The client has disconnected normally\n";
		break;
	
	default:
		break;
	}
}

void User::sendClientData() {}

