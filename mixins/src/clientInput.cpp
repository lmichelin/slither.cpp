#include "clientInput.h"
#include <iostream> //DEBUG

sf::Packet& operator <<(sf::Packet& packet, const input& input) {
    return packet << input.speed << input.rotating_right << input.rotating_left;
}

sf::Packet& operator >>(sf::Packet& packet, input& input) {
    return packet >> input.speed >> input.rotating_right >> input.rotating_left;
}

void clientInput::package(sf::Packet& packet) {
	packet << getData();
}

void clientInput::extract(sf::Packet& packet) {
	input temp;
	packet >> temp;
	setData(temp);
}