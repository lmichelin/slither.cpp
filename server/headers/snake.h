#ifndef SNAKE_H_
#define SNAKE_H_

#include <string>
#include <iostream>
#include "input.h"
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

	sf::Vector2f getAim() const {
		return _aim;
	}

	void die() {
		_is_dead = true;
	}

	void addTail(int n) {
		_body.addTail(n);
	}

	void updateAim(const Input& input) {
		_body.updateAim(input);
	}

	void interpolate (const float speed) {
		_body.interpolate(speed);
	}

	bool checkIntersection (const SnakeBody& s) {
		return _body.checkIntersection (s);
	}

	bool checkFoodIntersection (const Food& p) {
		return _body.checkFoodIntersection (p);
	}

	// Constructors
	Snake() : _body(), _is_dead(false) {
		_name = "LOLILO";
	}

	Snake(sf::Vector2f init_pos, sf::Vector2f aim) : _body(init_pos), _is_dead(false) {
		_name = "LOLILO";
		_aim = aim;
		_speed = LOW_SPEED;
	}

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
