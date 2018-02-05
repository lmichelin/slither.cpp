#ifndef SNAKE_BODY_H
#define SNAKE_BODY_H

#include "parameters.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <vector>
#include "food.h"

typedef std::vector<sf::Vector2f> coord_vect;

class SnakeBody {
public:
	int getLength ();
	void addTail (int);

	void interpolate (const sf::Vector2f, const float);
	bool checkIntersection (const SnakeBody&);
	bool checkFoodIntersection (const Food&);

	friend void drawSnakeBody (sf::RenderWindow& _window, const SnakeBody&);

	// Constructors
	SnakeBody (sf::Vector2f);
	SnakeBody ();
private:
	coord_vect _parts;

	sf::Vector2f getHead() const {
		return _parts[0];
	}
};

#endif
