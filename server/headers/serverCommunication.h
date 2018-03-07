/*
 * Class to communicate with client
*/

#ifndef SERVER_COMMUNICATION_H
#define SERVER_COMMUNICATION_H

#include "communication.h"
#include <memory>

class ServerCommunication : public Communication {
	public:

		void init();
		
		Address getRemoteAddress();
		Socket& getSocket();

		void send(int header,  Packet packet, Status& status);
		void receive(int& header, Packet& packet, Status& status);

		void send(int header, Packet packet);
		void receive(int& header, Packet& packet);

		ServerCommunication(std::shared_ptr<Socket>& socket): _socket(socket) {}
		~ServerCommunication() {}
	
	private: 
		std::shared_ptr<Socket>& _socket;
};

#endif
