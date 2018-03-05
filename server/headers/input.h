/*
 * This struct is used as the input the client sends to the server 
 * It is basically a struct in which client events are logged (speed increase and rotation)
*/
#ifndef INPUT_H
#define INPUT_H

#include <SFML/Network.hpp>
#include "data.h"
#include "parameters.h"

struct input {
	float speed;
	bool rotating_right;
	bool rotating_left;
};

class clientInput: public networkData<input> {
	public:
		void send(sf::TcpSocket& socket, int header, sf::Socket::Status& status);
		void receive(sf::TcpSocket& socket, int& header, sf::Socket::Status& status);

		// Overload operators
		friend sf::Packet& operator <<(sf::Packet& packet, const input& input);
		friend sf::Packet& operator >>(sf::Packet& packet, input& input);

		clientInput() {
			_data.speed = LOW_SPEED;
			_data.rotating_right = false;
			_data.rotating_left = false;
		};
		~clientInput() {};
};


#endif
