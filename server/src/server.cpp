#include "server.h"
#include <iostream>
#include <list>

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
 * IMPORTANT TO USE SHARED POINTERS TO KEEP THE SOCKETS IN SCOPE !!!
*/
void Server::run() {
	std::list<std::shared_ptr<sf::TcpSocket> > socket_container;

	for(;;) {
		// sf::TcpSocket socket;
		std::shared_ptr<sf::TcpSocket> s_ptr = std::make_shared<sf::TcpSocket>();
		socket_container.push_back(s_ptr);

		if (_listener.accept(*s_ptr) == sf::Socket::Done) {
			// A new client just connected!
			std::cout << "New client connected: " << s_ptr->getRemoteAddress() << ':' << s_ptr->getRemotePort() << std::endl;

			// Send new client status
			_socket_queue->push(s_ptr);
		}
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