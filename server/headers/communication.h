#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <SFML/Network.hpp>
#include "parameters.h"
#include <string>

class Communication
{
	private:
		int _port;
		sf::TcpSocket _socket;
		std::string _addr;
		

	public:
		void init();
		void send(sf::Packet);
		void receive(sf::Packet*);

		Communication(std::string addr, int port) : _addr(addr), _port(port) {}
		~Communication() {}
};

#endif
