/*
 * This struct is used as the input the client sends to the server 
 * It is basically a struct in which client events are logged (speed increase and rotation)
*/
#ifndef INPUT_H
#define INPUT_H

#include <SFML/Network.hpp>

struct Input {
	float speed;
	bool rotating_right;
	bool rotating_left;
};

#endif
