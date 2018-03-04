#include "communication.h"
#include <iostream>

void Communication::init() {
	_socket.setBlocking(false);
    _socket.connect(_addr, _port);
    printf("Communication with server launched\n");
}

void Communication::send(int header,  sf::Packet packet) {
	sf::Packet header_packet;
	header_packet << header;
	header_packet << packet;
    auto status = _socket.send(header_packet);
	if (status == sf::Socket::Done) {
		std::cout << "Sending packet\n";
	} else {
		// Error
		std::cout << "Error when sending to server\n";
	}
}

void Communication::receive(int& header, sf::Packet& packet) {
    auto status = _socket.receive(packet);
	if (status == sf::Socket::Done) {
		// Retrieve header from the packet
		packet >> header;
		std::cout << "Receiving stuff " << header << "\n";
	} else if (status == sf::Socket::NotReady) {
		// There is nothing to receive on server side
		std::cout << "Nothing to receive\n";
	} else {
		// There was an error on receive
		std::cout << "Error on receive\n";
	}
}
