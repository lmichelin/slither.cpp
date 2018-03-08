/*
 * Interface to communicate between server and client
*/

#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <SFML/Network.hpp>
#include "parameters.h"
#include <memory>
#include <string>

typedef sf::Socket::Status Status;
typedef sf::Packet Packet;
typedef sf::IpAddress Address;
typedef sf::TcpSocket Socket;

class Communication {
	public:
		virtual void init() =0;

		virtual Address getRemoteAddress() =0;
		virtual Socket& getSocket() =0;
		virtual void disconnect() =0;

		template <typename T>
		void send(int header, T send_data, Status& status) {
			Packet packet;
			packet << send_data;
			sendPacket(header, packet, status);
		}

		template <typename T>
		void send(int header, T send_data) {
			Status status;
			send(header, send_data, status);
		}

		virtual void sendPacket(int header,  Packet packet, Status& status) =0;
		virtual void receivePacket(int& header, Packet& packet, Status& status) =0;

		virtual void sendPacket(int header,  Packet packet) =0;
		virtual void receivePacket(int& header, Packet& packet) =0;

};

#endif
