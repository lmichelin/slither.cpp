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

		void disconnect();
		
		Address getRemoteAddress();
		Socket& getSocket();

		void sendPacket(int header,  Packet packet, Status& status);
		void receivePacket(int& header, Packet& packet, Status& status);

		void sendPacket(int header, Packet packet);
		void receivePacket(int& header, Packet& packet);

		ServerCommunication(Socket* socket): _socket(socket) {}
		~ServerCommunication() {}
	
	private: 
		Socket* _socket;
};

#endif
