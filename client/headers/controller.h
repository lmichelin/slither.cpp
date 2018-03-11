#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "clientInput.h"

class Controller {
private:
	input _input;

public:
	void rotateLeft(bool);
	void rotateRight(bool);
	void setSpeed(float);
	float getSpeed();

	input getInput() const;
	void resetInput() {
		_input = {LOW_SPEED, false, false};
	}

	bool getRotatingLeft();
	bool getRotatingRight();

	Controller(): _input({LOW_SPEED, false, false}) {}
	~Controller() {}
};

#endif
