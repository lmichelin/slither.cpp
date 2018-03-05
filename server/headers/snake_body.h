#ifndef SNAKE_BODY_H
#define SNAKE_BODY_H

#include "parameters.h"
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include "input.h"
#include <string>
#include <iostream>
#include <vector>
#include "food.h"

//////////////////////
// Type Definitions //
//////////////////////

typedef std::vector<sf::Vector2f> coord_vect;


class SnakeBody {
	public:

		//////////////////
		// Main Methods //
		//////////////////


		void interpolate (const float speed);
		bool checkIntersection (const SnakeBody& S, int radius);
		bool checkIntersection (const SnakeBody& S);
		bool checkFoodIntersection (const Food& p);
		void updateAim(const Input& input);

		/////////////////
		//   Getters   //
		/////////////////

		sf::Vector2f getHead() const {
			return _parts[0];
		}
		int getLength () const;
		sf::Vector2f getAim() const;
		coord_vect getParts() const;

		void addTail (int);

		/////////////////
		// Constructor //
		/////////////////

		SnakeBody (sf::Vector2f);
		SnakeBody ();

	private:
		coord_vect _parts;

		sf::Vector2f _aim;

};

#endif
