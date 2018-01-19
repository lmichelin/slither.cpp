#ifndef SNAKE_H_
#define SNAKE_H_

#include <string>
#include <iostream>
#include "snake_body.h"

class Snake {
public:
	// Get name
	std::string getName() {
		return _name;
	}

	SnakeBody getBody() {
		return _body;
	}

	bool checkIfDead() {
		return _is_dead;
	}

	void die() {
		_is_dead = true;
	}

	void addTail(int n) {
		_body.addTail(n);
	}

	void interpolate (const sf::Vector2f h, float s) {
		_body.interpolate(h, s);
	}

	bool checkIntersection (const SnakeBody& s) {
		return _body.checkIntersection (s);
	}

	bool checkFoodIntersection (const Food& p) {
		return _body.checkFoodIntersection (p);
	}

	// Constructors
	Snake() : _body(), _is_dead(false) {}

	Snake(sf::Vector2f init_pos) : _body(init_pos), _is_dead(false) {}

private:
	// name
	std::string _name;

	SnakeBody _body;

	// Variable to check whether the snake is dead or not
	bool _is_dead;
};

#endif
