/*
 * Class to model a snake with its own snake body, aim, id and speed
*/
#ifndef SNAKE_H_
#define SNAKE_H_

#include <string>
#include <iostream>
#include <cmath>
#include "input.h"
#include "snake_body.h"

class Snake {
	public:

		//////////////////
		// Main Methods //
		//////////////////

		// Update Body by setting its parts
		void updateBody(snake_part_vect parts) {
			_body.setParts(parts);
		}

		// Kill the snake
		void die() {
			_is_dead = true;
		}

		// Add a part to snake body
		void addTail(int n) {
			_body.addTail(n);
		}

		// Update aim with the input of the player
		void updateAimAndSpeed(const input& input) {
			_speed = input.speed;
			sf::Vector2f tmp = _aim;
			float angle = input.speed * ROTATION_ANGLE * (input.rotating_right - input.rotating_left);
			
			_aim.x = cos(angle)*tmp.x - sin(angle)*tmp.y;
			_aim.y = sin(angle)*tmp.x + cos(angle)*tmp.y;
		}

		// Get new head with speed and aim
		void interpolate () {
			_body.interpolate(_speed, _aim);
		}

		// Check intersection with a snakebody
		bool checkIntersection (const SnakeBody& s) {
			return _body.checkIntersection (s);
		}

		// Check intersection with food
		bool checkFoodIntersection (const Food& p) {
			return _body.checkFoodIntersection (p);
		}

		/////////////////
		//   Getters   //
		/////////////////

		SnakeBody& getBody() {
			return _body;
		}

		bool checkIfDead() {
			return _is_dead;
		}

		sf::Vector2f getAim() const {
			return _aim;
		}


		/////////////////
		// Constructor //
		/////////////////

		Snake() : _body(), _is_dead(false) {
			_speed = LOW_SPEED;
		}

		Snake(SnakePart init_pos, sf::Vector2f aim) : _body(init_pos), _is_dead(false) {
			_aim = aim;
			_speed = LOW_SPEED;
		}

		Snake(snake_part_vect coordinates): _body(coordinates), _is_dead(false) {}

	private:

		// Snake body
		SnakeBody _body;

		// Aim of the snake (direction coordinates)
		sf::Vector2f _aim;

		// Speed of the snake
		float _speed;

		// Variable to check whether the snake is dead or not
		bool _is_dead;
};

#endif
