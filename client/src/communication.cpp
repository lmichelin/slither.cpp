#include "communication.h"

void Communication::init() {
    _socket.connect(_addr, _port);
    printf("Communication launched\n");
}

void Communication::send(sf::Packet packet) {
    printf("Sending stuff\n");
    _socket.send(packet);
}
