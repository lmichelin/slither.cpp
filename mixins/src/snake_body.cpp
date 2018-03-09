#include "snake_body.h"
#include <cmath>

int SnakeBody::getLength() const {
	return _parts.size();
}

snake_part_vect SnakeBody::getParts() const {
	return _parts;
}

void SnakeBody::addTail(int n) {
	for (int i = 0; i < n; i++) {
		_parts.push_back(_parts.back());
	}
}

void SnakeBody::interpolate(const float speed, sf::Vector2f aim) {
	// Head
	_parts[0].setCoordinates(_parts[0].getCoordinates() + aim * speed);

	// Rest of the body
	for (unsigned int i = 1; i < _parts.size(); i++) {
		aim = (_parts[i] - _parts[i-1]).getCoordinates();

		float norm = sqrt(aim.x * aim.x + aim.y * aim.y);
		if (norm < EPSILON)
			norm = 1;

		aim = aim * std::min(_parts[i].getRadius(), norm) / norm;
		_parts[i].setCoordinates(_parts[i-1].getCoordinates() + aim);
	}
}

bool SnakeBody::checkFoodIntersection (const Food& food) {
	return _parts[0].checkIntersection(food.getPart());
}

bool SnakeBody::checkIntersection(const SnakeBody& S, float radius) {
	snake_part_vect parts = S.getParts();
	for (unsigned int i = 0; i < parts.size(); i++) {
		if (getHead().checkIntersection(parts[i], radius))
			return true;
	}
	return false;
}

bool SnakeBody::checkIntersection(const SnakeBody& S) {
	snake_part_vect parts = S.getParts();
	for (unsigned int i = 0; i < parts.size(); i++) {
		if (getHead().checkIntersection(parts[i]))
			return true;
	}
	return false;
}