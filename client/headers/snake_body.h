#ifndef SNAKE_BODY_H
#define SNAKE_BODY_H

#include "parameters.h"
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <string>
#include <iostream>
#include <vector>
#include "food.h"

typedef std::vector<sf::Vector2f> coord_vect;

class SnakeBody {
private:
	coord_vect _parts;

	sf::Vector2f getHead() const {
		return _parts[0];
	}
public:
	int getLength () const;
	void addTail (int);
	void updateParts(coord_vect parts);
	coord_vect getParts() const;

	void interpolate (const sf::Vector2f, const float);
	bool checkIntersection (const SnakeBody&, int radius);
	bool checkIntersection (const SnakeBody&);
	bool checkFoodIntersection (const Food&);

	friend void drawSnakeBody (sf::RenderWindow& _window, const SnakeBody&);

	friend sf::Packet &operator>>(sf::Packet &packet, SnakeBody &snake_body);

	// Constructors
	SnakeBody (sf::Vector2f);
	SnakeBody ();
};

#endif
