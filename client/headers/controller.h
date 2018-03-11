#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "clientInput.h"

class Controller {

	public:

		//////////////////
		// Main Methods //
		//////////////////

		void rotateLeft(bool);
		void rotateRight(bool);
		void setSpeed(float);

		/////////////
		// Getters //
		/////////////

		float getSpeed();

		input getInput() const;

		void resetInput() {
			_input = {LOW_SPEED, false, false};
		}

		bool getRotatingLeft();
		bool getRotatingRight();

		/////////////////
		// Constructor //
		/////////////////

		Controller(): _input({LOW_SPEED, false, false}) {}
		~Controller() {}

	private:

		// Input struct
		input _input;
};

#endif
