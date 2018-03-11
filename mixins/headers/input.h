/*
 * Struct to define the input of the player (whether it is a human or AI)
*/ 


#ifndef INPUT_H
#define INPUT_H

struct input {
	float speed;
	bool rotating_right;
	bool rotating_left;
};

#endif