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

		ClientCommunication(std::string addr, int port) : _addr(addr), _port(port) {}
		~ClientCommunication() {}

	private:
		std::string _addr;
		int _port;
		Socket _socket;
};

#endif
