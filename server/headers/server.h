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
		void send(int header, const sf::Packet packet);
		void receive(int* header, sf::Packet* packet);

		Server(std::string addr, int port) : _addr(addr), _port(port) {}
		~Server() {}
};

#endif
