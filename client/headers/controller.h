#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "input.h"

class Controller {
private:
	input _input;

public:
	void rotateLeft(bool);
	void rotateRight(bool);
	void setSpeed(float);
	float getSpeed();

	input getInput() const;

	bool getRotatingLeft();
	bool getRotatingRight();

	Controller() {};
	~Controller() {}
};

#endif
