#include "clientCommunication.h"
#include <iostream>

void ClientCommunication::init() {
	getSocket().setBlocking(false);
    getSocket().connect(_addr, _port);
    printf("Communication with server launched\n");
}

Socket& ClientCommunication::getSocket() {
	return _socket;
}

void ClientCommunication::send(int header, Packet packet, Status& status) {
	sf::Packet header_packet;
	header_packet << header;
	header_packet.append(packet.getData(), packet.getDataSize());
	status = _socket.send(header_packet);
    if (status != sf::Socket::Done) {
		// Error
		std::cout << "Error when sending to server\n";
	}
}

void ClientCommunication::receive(int& header, Packet& packet, Status& status) {
    status = _socket.receive(packet);
	if (status == sf::Socket::Done) {
		// Retrieve header from the packet
		packet >> header;
	} else if (status == sf::Socket::NotReady) {
		// There is nothing to receive on server side
		std::cout << "Nothing to receive\n";
	} else {
		// There was an error on receive
		std::cout << "Error on receive\n";
	}
}

void ClientCommunication::send(int header, Packet packet) {
	Status dummy;
	send(header, packet, dummy);
}

void ClientCommunication::receive(int& header, Packet& packet) {
	Status dummy;
	receive(header, packet, dummy);
}

Address ClientCommunication::getRemoteAddress() {
	return _socket.getRemoteAddress();
}