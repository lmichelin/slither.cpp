#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <SFML/Network.hpp>
#include "parameters.h"
#include <string>

class Communication
{
	private:
		sf::TcpSocket _socket;
		std::string _addr;
		int _port;
		

	public:
		void init();
		void send(int header, const sf::Packet packet);
		void receive(int* header, sf::Packet* packet);

		Communication(std::string addr, int port) : _addr(addr), _port(port) {}
		~Communication() {}
};

#endif
