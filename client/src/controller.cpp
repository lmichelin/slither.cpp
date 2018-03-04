#include "controller.h"
#include <cmath>
#include "parameters.h"
#include <iostream>
#include <SFML/Network.hpp>

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

bool Controller::getRotatingLeft() {
	return _rotating_left;
}


bool Controller::getRotatingRight() {
	return _rotating_right;
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

sf::Packet &operator<<(sf::Packet &packet, const Controller &controller) {
	return packet << controller._speed << controller._rotating_right << controller._rotating_left;
}
