#ifndef INPUT_H
#define INPUT_H

#include <SFML/Network.hpp>

struct Input {
	float speed;
	bool rotating_right;
	bool rotating_left;
};

sf::Packet &operator>>(sf::Packet &packet, Input &input) {
	packet >> input.speed >> input.rotating_left >> input.rotating_right;
	return packet;
}

#endif
