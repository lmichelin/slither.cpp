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


		void interpolate (const sf::Vector2f head_aim, const float speed);
		bool checkIntersection (const SnakeBody& S);
		bool checkFoodIntersection (const Food& p);
		void updateAim(const Input& input);

		/////////////////
		//   Getters   //
		/////////////////

		int getLength () const;
		void addTail (int);

		// Overcharge send operator for sf::Packet
		friend sf::Packet &operator<<(sf::Packet& packet, const SnakeBody& snake_body);

		/////////////////
		// Constructor //
		/////////////////

		SnakeBody (sf::Vector2f);
		SnakeBody ();

	private:
		coord_vect _parts;

		sf::Vector2f _aim;

		sf::Vector2f getHead() const {
			return _parts[0];
		}
};

#endif
