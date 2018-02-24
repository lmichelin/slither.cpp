#ifndef SERVER_H
#define SERVER_H

#include <SFML/Network.hpp>
#include "parameters.h"
#include <string>

class Server {
	private:
		sf::TcpListener _listener;
		int _port;
		

	public:
		void init();
		void send(sf::TcpSocket &socket, int header, const sf::Packet packet);
		void receive(sf::TcpSocket &socket, int &header, sf::Packet &packet);

		Server(std::string addr, int port) : _port(port) {}
		~Server() {}
};

#endif
