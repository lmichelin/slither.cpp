#include "parameters.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <vector>
#include "snake_body.h"

SnakeBody::SnakeBody (sf::Vector2f init_pos) {
	_body.push_back(init_pos);
	addTail(INIT_LENGTH -1);
	std::cout << "/* message */" << '\n';
}

SnakeBody::SnakeBody () {
	sf::Vector2f init_pos(0,0);
	_body.push_back(init_pos);
	addTail(INIT_LENGTH -1);
}

int SnakeBody::getLength() {
	return _body.size();
}

void SnakeBody::addTail(int n) {
	for (int i = 0; i < n; i++) {
		_body.push_back(_body.back());
	}
}

void SnakeBody::interpolate(const sf::Vector2f head_aim) {
	sf::Vector2f aim = head_aim;
	float speed = 2; //TODO
	// Head
	_body[0] += aim * speed;
	// Rest of the body
	for (unsigned int i = 1; i < _body.size(); i++) {
		aim = (_body[i] - _body[i-1]);
		float norm = sqrt(aim.x*aim.x+aim.y*aim.y);
		aim.x /= norm;
		aim.y /= norm;
		_body[i] += aim * std::min((float)SNAKE_CIRCLE_RADIUS, norm);
	}
}

bool SnakeBody::checkIntersection(const SnakeBody& S) {
	sf::Vector2f opponent_head = S.getHead();

	bool is_intersecting = false;
	for (coord_vect::iterator it = _body.begin(); it != _body.end(); it++) {
		sf::Vector2f diff = opponent_head - (*it);
		float dist = sqrt(diff.x*diff.x+diff.y*diff.y);
		if (dist < 2 * SNAKE_CIRCLE_RADIUS) {
			is_intersecting = true;
		}
	}

	return is_intersecting;
}
