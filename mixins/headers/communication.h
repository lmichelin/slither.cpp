/*
 * Interface to communicate between server and client
*/

#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <SFML/Network.hpp>
#include "parameters.h"

typedef sf::Socket::Status Status;
typedef sf::Packet Packet;
typedef sf::IpAddress Address;
typedef sf::TcpSocket Socket;

class Communication {
	public:

		//////////////////
		// Main Methods //
		//////////////////
		
		// Initialize communication
		virtual void init() =0;

		// Get remote address
		virtual Address getRemoteAddress() =0;

		// Get the socket
		virtual Socket& getSocket() =0;

		// Disconnect the socket from host
		virtual void disconnect() =0;

		// Send a template with status
		template <typename T>
		void send(int header, T send_data, Status& status) {
			Packet packet;
			packet << send_data;
			sendPacket(header, packet, status);
		}

		// Send a template type without returning status
		template <typename T>
		void send(int header, T send_data) {
			Status status;
			send(header, send_data, status);
		}

		// Send a header status code
		void send(int header) {
			Packet dummy;
			sendPacket(header, dummy);
		}

		// Send and receive packets with status (TO BE DONE BY SUBCLASS CLIENT AND SERVER)
		virtual void sendPacket(int header,  Packet packet, Status& status) =0;
		virtual void receivePacket(int& header, Packet& packet, Status& status) =0;

		// Send and receive packets without status (TO BE DONE BY SUBCLASS CLIENT AND SERVER)
		virtual void sendPacket(int header,  Packet packet) =0;
		virtual void receivePacket(int& header, Packet& packet) =0;

};

#endif
