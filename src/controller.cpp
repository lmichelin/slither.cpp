#include "controller.h"
#include "parameters.h"
#include <iostream>

void Controller::rotateLeft (bool value) {
	_rotating_left = value;
}

void Controller::rotateRight (bool value) {
	_rotating_right = value;
}

void Controller::setSpeed (float value) {
	_speed = value;
}

float Controller::getSpeed () {
	return _speed;
}

void Controller::updateAim () {
	sf::Vector2f tmp = _aim;
	float angle = _speed * ROTATION_ANGLE * (_rotating_right - _rotating_left);

	_aim.x = cos(angle)*tmp.x - sin(angle)*tmp.y;
	_aim.y = sin(angle)*tmp.x + cos(angle)*tmp.y;
}

sf::Vector2f Controller::getAim () {
	return _aim;
}

Controller::Controller () {
	_speed = LOW_SPEED;
	_aim.x = 1.0;
	_aim.y = 0.0;
}
