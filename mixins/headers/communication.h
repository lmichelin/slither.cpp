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

		template <class T>
		void send(int header, T send_data, Status& status) {
			Packet packet;
			packet << header << send_data;
			send(header, packet, status);
		}

		template <class T>
		void receive(int header, T& receive_data, Status& status) {
			Packet packet;
			receive(header, packet, status);
			packet >> header >> receive_data;
		}

		template <class T>
		void send(int header, T send_data) {
			Status dummy;
			Status status;
			send(header, send_data, status);
		}
		template <class T>
		void receive(int header, T& receive_data) {
			Status dummy;
			Status status;
			receive(header, receive_data, status);
		}

		virtual void send(int header,  Packet packet, Status& status) =0;
		virtual void receive(int& header, Packet& packet, Status& status) =0;

		virtual void send(int header,  Packet packet) =0;
		virtual void receive(int& header, Packet& packet) =0;

};

#endif
