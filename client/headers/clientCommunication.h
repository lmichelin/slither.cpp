/*
 * Class to communicate with server
*/

#ifndef CLIENT_COMMUNICATION_H
#define CLIENT_COMMUNICATION_H

#include <SFML/Network.hpp>
#include "parameters.h"
#include "communication.h"
#include <string>

class ClientCommunication : public Communication {
	public:
		void init();

		Address getRemoteAddress();
		Socket& getSocket();

		void send(int header,  Packet packet, Status& status);
		void receive(int& header, Packet& packet, Status& status);

		 void send(int header, Packet packet);
		 void receive(int& header, Packet& packet);

		ClientCommunication(std::string addr, int port) : _addr(addr), _port(port) {}
		~ClientCommunication() {}

	private:
		std::string _addr;
		int _port;
		Socket _socket;
};

#endif