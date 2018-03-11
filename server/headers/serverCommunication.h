/*
 * Class to communicate with client
*/

#ifndef SERVER_COMMUNICATION_H
#define SERVER_COMMUNICATION_H

#include "communication.h"

class ServerCommunication : public Communication {
	public:

		//////////////////
		// Main Methods //
		//////////////////

		// Init the communication
		void init();

		// Disconnect server
		void disconnect();
		
		// Get remote address
		Address getRemoteAddress();

		// Get the socket
		Socket& getSocket();

		// Send and receive packets with status
		void sendPacket(int header,  Packet packet, Status& status);
		void receivePacket(int& header, Packet& packet, Status& status);

		// Send and receive packets without status (TO BE DONE BY SUBCLASS CLIENT AND SERVER)
		void sendPacket(int header, Packet packet);
		void receivePacket(int& header, Packet& packet);

		/////////////////
		// Constructor //
		/////////////////

		ServerCommunication(Socket* socket): _socket(socket) {}
		~ServerCommunication() {}
	
	private: 

		// Socket of the player on server
		Socket* _socket;
};

#endif
