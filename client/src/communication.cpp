#include "communication.h"

void Communication::init() {
    _socket.connect(_addr, _port);
    printf("Communication launched\n");
}

void Communication::send(sf::Packet packet) {
	_socket.send(packet);
    printf("Sending stuff\n");
}

void Communication::receive(sf::Packet *packet)
{
    _socket.receive(*packet);
}