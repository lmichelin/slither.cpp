#ifndef SNAKE_H_
#define SNAKE_H_

#include <string>
#include <iostream>
#include "input.h"
#include "snake_body.h"
#include <cmath>

class Snake {
public:

	void updateBody(coord_vect parts) {
		_body.setParts(parts);
	}

	// Get name
	std::string getName() {
		return _name;
	}

	SnakeBody& getBody() {
		return _body;
	}

	bool checkIfDead() {
		return _is_dead;
	}

	sf::Vector2f getAim() const {
		return _aim;
	}

	void die() {
		_is_dead = true;
	}

	void addTail(int n) {
		_body.addTail(n);
	}

	void updateAim(const input& input) {
		sf::Vector2f tmp = _aim;
		float angle = input.speed * ROTATION_ANGLE * (input.rotating_right - input.rotating_left);
		
		_aim.x = cos(angle)*tmp.x - sin(angle)*tmp.y;
		_aim.y = sin(angle)*tmp.x + cos(angle)*tmp.y;
	}

	void interpolate (const float speed) {
		_body.interpolate(speed, _aim);
	}

	bool checkIntersection (const SnakeBody& s) {
		return _body.checkIntersection (s);
	}

	bool checkFoodIntersection (const Food& p) {
		return _body.checkFoodIntersection (p);
	}

	// Constructors
	Snake() : _body(), _is_dead(false) {
		_speed = LOW_SPEED;
	}

	Snake(sf::Vector2f init_pos, sf::Vector2f aim) : _body(init_pos), _is_dead(false) {
		_aim = aim;
		_speed = LOW_SPEED;
	}

	Snake(coord_vect coordinates): _body(coordinates), _is_dead(false) {}

private:
	// name
	std::string _name;

	SnakeBody _body;

	sf::Vector2f _aim;

	float _speed;

	// Variable to check whether the snake is dead or not
	bool _is_dead;
};

#endif
