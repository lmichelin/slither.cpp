#ifndef SERVER_H
#define SERVER_H

#include <SFML/Network.hpp>
#include "parameters.h"
#include <string>
#include "safequeue.h"
#include <memory>
class Server {
	public:
		// Initialize server by listening for connections
		void init();

		// Run server and wait for connections
		void run();

		// Send and receive messages with SFML Network
		static void send(sf::TcpSocket &socket, int header, const sf::Packet packet);
		static void receive(sf::TcpSocket &socket, int &header, sf::Packet &packet);


		/////////////////
		// Constructor //
		/////////////////
		Server(int port, SafeQueue<std::shared_ptr<sf::TcpSocket> >* socket_queue) : _listener(), _socket_queue(socket_queue) {
			_port = port;
		}
		~Server() {}


	private:
		sf::TcpListener _listener;
		int _port;
		SafeQueue<std::shared_ptr<sf::TcpSocket> >* _socket_queue;
};

#endif
