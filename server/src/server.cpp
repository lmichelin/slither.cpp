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
*/
void Server::run() {
	sf::TcpSocket socket_container[MAX_CONNECTIONS];

	for(;;) {
		for (size_t i = 0; i < MAX_CONNECTIONS; i++)
		{
			if (socket_container[i].getRemoteAddress() == sf::IpAddress::None) {
				if (_listener.accept(socket_container[i]) == sf::Socket::Done) {

					// Set socket to non blocking
					socket_container[i].setBlocking(false);

					// A new client just connected!
					std::cout << "New client connected: Socket number " << i << " Address: " << socket_container[i].getRemoteAddress() << ':' << socket_container[i].getRemotePort() << std::endl;

					// If it is the last socket available, reject the client
					if (i == MAX_CONNECTIONS - 1) {
						sf::Packet reject_packet;
						reject_packet << GAME_FULL;
						socket_container[i].send(reject_packet); 
						socket_container[i].disconnect();
					}

					// Send new client status (Add it to the socket queue so the program can do something with it)
					else {
						sf::TcpSocket* pointer = &socket_container[i];
						_socket_queue->push(pointer);
						break;
					}
				}
			}
		}
	}
}