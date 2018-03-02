#include "server.h"
#include <iostream>

/**
 * Initiate communication with a server
*/
void Server::init() {
	_listener.listen(_port);
	std::cout << "Server listening on port " << _port << std::endl;
}

/**
 * Run the server by listening for connection attempts
 * For each connection do something with the doStuff function
*/
void Server::run() {
	for(;;) {
		sf::TcpSocket socket;
		_listener.accept(socket);
		std::cout << "New client connected: " << socket.getRemoteAddress() << ':' << socket.getRemotePort() << std::endl;
	}
}

/**
 * Send a packet with the sfml network library
 * Takes a header (int) in argument
*/
void Server::send(sf::TcpSocket &socket, int header,  sf::Packet packet) {
	sf::Packet header_packet;
	header_packet << header;
	packet << header_packet;
    socket.send(packet);
}

/**
 * Receive a packet with the sfml network library
 * Takes a pointer to a header (int) in argument
*/
void Server::receive(sf::TcpSocket &socket, int& header, sf::Packet& packet) {
	packet >> header;
    socket.receive(packet);
}