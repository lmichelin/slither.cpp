#include "server.h"

/**
 * Initiate communication with a server
*/
void Server::init() {
    _socket.connect(_addr, _port);
    printf("Server launched\n");
}

/**
 * Send a packet with the sfml network library
 * Takes a header (int) in argument
*/
void Server::send(int header,  sf::Packet packet) {
	sf::Packet header_packet;
	header_packet << header;
	packet << header_packet;
    _socket.send(packet);
}

/**
 * Receive a packet with the sfml network library
 * Takes a pointer to a header (int) in argument
*/
void Server::receive(int* header, sf::Packet* packet) {
	*packet >> *header;
    _socket.receive(*packet);
}