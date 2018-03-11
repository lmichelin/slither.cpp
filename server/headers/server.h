/*
 * Server class for the server
*/

#ifndef SERVER_H
#define SERVER_H

#include <SFML/Network.hpp>
#include <string>
#include "parameters.h"
#include "safequeue.h"
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
		Server(int port, SafeQueue<sf::TcpSocket*>* socket_queue) : _listener(), _socket_queue(socket_queue) {
			_port = port;
		}
		~Server() {}


	private:

		// SFML listener to listen for new connections
		sf::TcpListener _listener;

		// Port on which the socket server listens
		int _port;

		// Safequeue to put new client connections in it (IMPORTANT FOR MULTITHREADING)
		SafeQueue<sf::TcpSocket*>* _socket_queue;
};

#endif
