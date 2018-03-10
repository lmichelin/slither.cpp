/*
 * This struct is used as the input the client sends to the server 
 * It is basically a struct in which client events are logged (speed increase and rotation)
*/
#ifndef CLIENT_INPUT_H
#define CLIENT_INPUT_H

#include "data.h"
#include "parameters.h"
#include "input.h"

sf::Packet& operator <<(sf::Packet& packet, const input& input);
sf::Packet& operator >>(sf::Packet& packet, input& input);

class clientInput: public networkData<input> {
	public:
		void package(sf::Packet& packet);
		void extract(sf::Packet& packet);

		clientInput() {
			input input{LOW_SPEED, false, false};
			setData(input);
		};
		~clientInput() {};
};

#endif
