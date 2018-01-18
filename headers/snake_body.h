#ifndef SNAKE_BODY_H
#define SNAKE_BODY_H

#include "parameters.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <vector>

typedef std::vector<sf::Vector2f> coord_vect;

class SnakeBody {
public:
	int getLength();
	void addTail(int);

	void interpolate(const sf::Vector2f);
	bool checkIntersection(const SnakeBody&);

	// Constructors
	SnakeBody(sf::Vector2f);
	SnakeBody();
private:
	coord_vect _body;

	sf::Vector2f getHead() const {
		return _body[0];
	}
};

#endif
