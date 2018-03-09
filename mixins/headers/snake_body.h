#ifndef SNAKE_BODY_H
#define SNAKE_BODY_H

#include "parameters.h"
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include "input.h"
#include <string>
#include <iostream>
#include <vector>
#include "parts.h"
#include "food.h"

//////////////////////
// Type Definitions //
//////////////////////

typedef std::vector<sf::Vector2f> coord_vect;
typedef std::vector<SnakePart> snake_part_vect;

class SnakeBody {
	public:

		//////////////////
		// Main Methods //
		//////////////////

		void interpolate (const float speed, sf::Vector2f aim);
		bool checkIntersection (const SnakeBody& S);
		bool checkIntersection (const SnakeBody& S, float radius);
		bool checkFoodIntersection (const Food& p);
		void addTail (int);

		/////////////////
		//   Getters   //
		/////////////////

		SnakePart getHead() const {
			return _parts[0];
		}

		int getLength () const;

		snake_part_vect getParts() const;

		void setParts(snake_part_vect parts) {
			_parts = parts;
		}

		void addPart(SnakePart new_part) {
			_parts.push_back(new_part);
		}

		/////////////////
		// Constructor //
		/////////////////

		SnakeBody (SnakePart init_part) {
			_parts.push_back(init_part);
			addTail(INIT_LENGTH -1);
		}
		SnakeBody (snake_part_vect parts) {
			_parts = parts;
		}
		SnakeBody () {
			SnakePart init_pos(sf::Vector2f(0,0));
			_parts.push_back(init_pos);
			addTail(INIT_LENGTH -1);
		}

	private:
		snake_part_vect _parts;
};

#endif
