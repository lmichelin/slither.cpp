#include "communication.h"

/**
 * Initiate communication with a server
*/
void Communication::init() {
    _socket.connect(_addr, _port);
    printf("Communication launched\n");
}

/**
 * Send a packet with the sfml network library
 * Takes a header (int) in argument
*/
void Communication::send(int header,  sf::Packet packet) {
	sf::Packet header_packet;
	header_packet << header;
	packet << header_packet;
    _socket.send(packet);
}

/**
 * Receive a packet with the sfml network library
 * Takes a pointer to a header (int) in argument
*/
void Communication::receive(int* header, sf::Packet* packet) {
	*packet >> *header;
    _socket.receive(*packet);
}