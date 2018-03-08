#include "controller.h"
#include <cmath>
#include "parameters.h"
#include <iostream>
#include <SFML/Network.hpp>

void Controller::rotateLeft (bool value) {
	_input.rotating_left = value;
}

void Controller::rotateRight (bool value) {
	_input.rotating_right = value;
}

void Controller::setSpeed (float value) {
	_input.speed = value;
}

float Controller::getSpeed () {
	return _input.speed;
}

bool Controller::getRotatingLeft() {
	return _input.rotating_left;
}

input Controller::getInput() const {
	return _input;
}

bool Controller::getRotatingRight() {
	return _input.rotating_right;
}