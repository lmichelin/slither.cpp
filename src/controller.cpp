#include "controller.h"
#include "parameters.h"

void Controller::rotateLeft (bool value) {
	_rotating_left = value;
}

void Controller::rotateRight (bool value) {
	_rotating_right = value;
}

void Controller::setSpeed (float value) {
	_speed = value;
}

void Controller::updateAim () {
	sf::Vector2f tmp = _aim;
	_aim.x = _speed * (cos(ROTATION_ANGULAR)*tmp.x - sin(ROTATION_ANGULAR)*tmp.y);
	_aim.y = _speed * (sin(ROTATION_ANGULAR)*tmp.x + cos(ROTATION_ANGULAR)*tmp.y);
}

sf::Vector2f Controller::getAim () {
	return _aim;
}

Controller::Controller () {
	_speed = LOW_SPEED;
}
