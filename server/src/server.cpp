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
		s_ptr->setBlocking(false);
		socket_container.push_back(s_ptr);

		if (_listener.accept(*s_ptr) == sf::Socket::Done) {
			// A new client just connected!
			std::cout << "New client connected: " << s_ptr->getRemoteAddress() << ':' << s_ptr->getRemotePort() << std::endl;
			
			// Send new client status (Add it to the socket queue so the program can do something with it)
			_socket_queue->push(s_ptr);
		}
	}
}