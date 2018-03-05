/*
 * This struct is used as the input the client sends to the server 
 * It is basically a struct in which client events are logged (speed increase and rotation)
*/
#ifndef INPUT_H
#define INPUT_H

#include <SFML/Network.hpp>

class Input {
	public:
		float speed;
		bool rotating_right;
		bool rotating_left;

		// Overload operators
		friend sf::Packet& operator >>(sf::Packet& packet, Input& input) {
			return packet >> input.speed >> input.rotating_right >> input.rotating_left;
		}
};


#endif
