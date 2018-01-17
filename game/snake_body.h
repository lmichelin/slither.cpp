#ifndef SNAKE_BODY_H
#define SNAKE_BODY_H

#include "../parameters.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <vector>
#include "snake.h"

namespace game {

	class SnakeBody {
	public:
		int getLength();
		void addTail(int);

		void interpolate();
		bool checkIntersection(const Snake&);

		// Constructors
		SnakeBody() {}
	private:
		std::vector<sf::Vector2f> _body;
	};

};

#endif
