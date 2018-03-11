/*
 * Class to model the body of a snake with its positions, coordinates, circles ...
*/
#ifndef SNAKE_BODY_H
#define SNAKE_BODY_H

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <vector>

#include "parameters.h"
#include "input.h"
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

		// Get new position of the head with speed and aim in argument
		void interpolate (const float speed, sf::Vector2f aim);

		// Check intersection between head and other snake body
		bool checkIntersection (const SnakeBody& S);

		// Check intersection between head and another snakebody with a radius more
		bool checkIntersection (const SnakeBody& S, float radius);

		// Check intersection between head and food
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

		// Parts of the snake with coordinates and colors
		snake_part_vect _parts;
};

#endif
