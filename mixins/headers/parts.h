#ifndef PARTSFACTORY_H
#define PARTSFACTORY_H

#include <SFML/Graphics.hpp>
#include "parameters.h"
#include <vector>

class Part {
	public:
		sf::Vector2f getCoordinates() const {
			return _coordinates;
		}
		
		virtual int getRadius() const =0;

		sf::Color getColor() const {
			return _color;
		}

		Part();
		~Part();

	private:
		sf::Vector2f _coordinates;
		sf::Color _color;
};

class SnakePart: public Part {
	public:
		int getRadius() const {
			return SNAKE_CIRCLE_RADIUS;
		}
};

class FoodPart: public Part {
	public:
		int getRadius() const {
			return FOOD_CIRCLE_RADIUS;
		}
};

#endif // !PARTSFACTORY_H