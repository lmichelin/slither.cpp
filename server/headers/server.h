/*
 * Server class for the server
*/

#ifndef SERVER_H
#define SERVER_H

#include <SFML/Network.hpp>
#include "parameters.h"
#include <string>
#include "safequeue.h"
#include <memory>
class Server {
	public:

		//////////////////
		// Main Methods //
		//////////////////

		// Initialize server by listening for connections
		void init();

		// Run server and wait for connections
		void run();


		/////////////////
		// Constructor //
		/////////////////

		// Initialize listener, socket_queue and port
		Server(int port, SafeQueue<std::shared_ptr<sf::TcpSocket> >* socket_queue) : _listener(), _socket_queue(socket_queue) {
			_port = port;
		}
		~Server() {}


	private:

		// SFML listener to listen for new connections
		sf::TcpListener _listener;

		// Port on which the socket server listens
		int _port;

		// Safequeue to put new client connections in it (IMPORTANT FOR MULTITHREADING)
		SafeQueue<std::shared_ptr<sf::TcpSocket> >* _socket_queue;
};

#endif
