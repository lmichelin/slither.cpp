#include "snake_body.h"
#include <cmath>

SnakeBody::SnakeBody (sf::Vector2f init_pos) {
	_parts.push_back(init_pos);
	addTail(INIT_LENGTH -1);
}

SnakeBody::SnakeBody () {
	sf::Vector2f init_pos(0,0);
	_parts.push_back(init_pos);
	addTail(INIT_LENGTH -1);
}

int SnakeBody::getLength() const {
	return _parts.size();
}

coord_vect SnakeBody::getParts() const {
	return _parts;
}

void SnakeBody::addTail(int n) {
	for (int i = 0; i < n; i++) {
		_parts.push_back(_parts.back());
	}
}

void SnakeBody::interpolate(const float speed, sf::Vector2f aim) {
	// Head
	_parts[0] += aim * speed;

	// Rest of the body
	for (unsigned int i = 1; i < _parts.size(); i++) {
		aim = (_parts[i] - _parts[i-1]);

		float norm = sqrt(aim.x * aim.x + aim.y * aim.y);
		if (norm < EPSILON) {
			norm = 1;
		}

		aim = aim * std::min((float)SNAKE_CIRCLE_RADIUS, norm) / norm;
		_parts[i] = _parts[i-1] + aim;
	}
}

bool SnakeBody::checkFoodIntersection (const Food& p) {
	sf::Vector2f diff = p.getPosition() - _parts[0];
	float dist = sqrt(diff.x*diff.x+diff.y*diff.y);
	return (dist < FOOD_CIRCLE_RADIUS + SNAKE_CIRCLE_RADIUS);
}

bool SnakeBody::checkIntersection(const SnakeBody& S, int radius) {
	coord_vect parts = S.getParts();
	for (unsigned int i = 0; i < parts.size(); i++) {
		sf::Vector2f diff = getHead() - parts[i];
		float dist = sqrt(diff.x*diff.x+diff.y*diff.y);
		if (dist < 2 * radius) {
			return true;
		}
	}
	return false;
}

bool SnakeBody::checkIntersection(const SnakeBody& S) {
	return checkIntersection(S, SNAKE_CIRCLE_RADIUS);
}