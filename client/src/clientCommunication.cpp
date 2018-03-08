#include "clientCommunication.h"
#include <iostream>

void ClientCommunication::init() {
	_socket.setBlocking(false);
    _socket.connect(_addr, _port);
    printf("Communication with server launched\n");
}

Socket& ClientCommunication::getSocket() {
	return _socket;
}

void ClientCommunication::disconnect() {
	_socket.disconnect();
}

void ClientCommunication::sendPacket(int header, Packet packet, Status& status) {
	sf::Packet header_packet;
	header_packet << header;
	header_packet.append(packet.getData(), packet.getDataSize());
	status = _socket.send(header_packet);
    if (status != sf::Socket::Done) {
		// Error
		std::cout << "Error when sending to server\n";
	}
}

void ClientCommunication::receivePacket(int& header, Packet& packet, Status& status) {
    status = _socket.receive(packet);
	if (status == sf::Socket::Done) {
		// Retrieve header from the packet
		// std::cout << "I DID SOMETRHING" << '\n';
		packet >> header;
	} else if (status == sf::Socket::NotReady) {
		// There is nothing to receive on server side
		std::cout << "Nothing to receive\n";
	} else {
		// There was an error on receive
		std::cout << "Error on receive\n";
	}
}

void ClientCommunication::sendPacket(int header, Packet packet) {
	Status dummy;
	sendPacket(header, packet, dummy);
}

void ClientCommunication::receivePacket(int& header, Packet& packet) {
	Status dummy;
	receivePacket(header, packet, dummy);
}

Address ClientCommunication::getRemoteAddress() {
	return _socket.getRemoteAddress();
}