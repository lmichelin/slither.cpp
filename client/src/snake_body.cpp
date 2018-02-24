#include "parameters.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <vector>
#include <cmath>
#include "snake_body.h"
#include "food.h"

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

void SnakeBody::addTail(int n) {
	for (int i = 0; i < n; i++) {
		_parts.push_back(_parts.back());
	}
}

void SnakeBody::interpolate(const sf::Vector2f head_aim, const float speed) {
	sf::Vector2f aim = head_aim;

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

bool SnakeBody::checkIntersection(const SnakeBody& S) {
	sf::Vector2f opponent_head = S.getHead();

	bool is_intersecting = false;
	for (coord_vect::iterator it = _parts.begin(); it != _parts.end(); it++) {
		sf::Vector2f diff = opponent_head - (*it);
		float dist = sqrt(diff.x*diff.x+diff.y*diff.y);
		if (dist < 2 * SNAKE_CIRCLE_RADIUS) {
			is_intersecting = true;
		}
	}

	return is_intersecting;
}

sf::Packet &operator>>(sf::Packet &packet, SnakeBody &snake_body)
{
	int size;
	packet >> size;
	sf::Vector2f temp_element;
	for (int i = 0; i < size; i++)
	{
		packet >> temp_element.x >> temp_element.y;
		snake_body._parts.push_back(temp_element);
	}
	return packet;
}
