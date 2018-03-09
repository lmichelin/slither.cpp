#ifndef PARTSFACTORY_H
#define PARTSFACTORY_H

#include <SFML/Graphics.hpp>
#include "parameters.h"
#include <vector>

class Part {
	public:

		/////////////
		// Getters //
		/////////////

		// Get the radius (dependant on type of part)
		virtual int getRadius() const;
		
		// Get the coordinates of the center of the part
		sf::Vector2f getCoordinates() const;

		// Get the color of the part
		sf::Color getColor() const;

		//////////////
		// SetColor //
		//////////////

		//  Set the color of the part
		void setColor(sf::Color color);

		// Set coordinates
		void setCoordinates(sf::Vector2f coordinates);

		Part(): _coordinates(sf::Vector2f(0,0)) {}
		Part(sf::Vector2f coordinates): _coordinates(coordinates) {}
		~Part() {}

	private:
		sf::Vector2f _coordinates;
		sf::Color _color;
};

// class SnakePart: public Part {
// 	public:
// 		int getRadius() const {
// 			return SNAKE_CIRCLE_RADIUS;
// 		}

// 		float computeDistance(const SnakePart other_part);
// 		float computeDistance(const FoodPart other_part);

// 		SnakePart() {}
// 		SnakePart(sf::Vector2f coordinates): Part(coordinates) {}
// 		~SnakePart() {}
// };

// class FoodPart: public Part {
// 	public:
// 		int getRadius() const {
// 			return FOOD_CIRCLE_RADIUS;
// 		}

// 		float computeDistance(const SnakePart other_part);
// 		float computeDistance(const FoodPart other_part);

// 		FoodPart() {}
// 		FoodPart(sf::Vector2f coordinates): Part(coordinates) {}
// 		~FoodPart() {}
// };

#endif // !PARTSFACTORY_H