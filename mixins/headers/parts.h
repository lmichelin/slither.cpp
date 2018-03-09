#ifndef PARTSFACTORY_H
#define PARTSFACTORY_H

#include <SFML/Graphics.hpp>
#include "parameters.h"

class ShapePart {

	public:

		//////////////////
		// Main Methods //
		//////////////////

		float computeDistance(const ShapePart& other_part);
		bool checkIntersection(const ShapePart& other_part);
		bool checkIntersection(const ShapePart& other_part, float radius);
		sf::Vector2f computeAim(const ShapePart& other_part);

		/////////////
		// Getters //
		/////////////

		// Get the coordinates of the center of the part
		virtual sf::Vector2f getCoordinates() const {
			return _coordinates;
		}

		virtual float getRadius() const {
			return _radius;
		}

		// Get the color of the part
		virtual sf::Color getColor() const {
			return _color;
		}

		//////////////
		// Settters //
		//////////////

		//  Set the color of the part
		void setColor(const sf::Color color) {
			_color = color;
		}

		// Set coordinates
		void setCoordinates(const sf::Vector2f coordinates) {
			_coordinates = coordinates;
		}

		// Set Radius
		void setRadius(const float radius) {
			_radius = radius;
		}

		///////////////
		// OPERATORS //
		///////////////

		ShapePart operator+(const ShapePart& other_part) {
			ShapePart shape_part(this->_coordinates, this->_color, this->_radius);
			shape_part.setCoordinates(this->_coordinates + other_part.getCoordinates());
			return shape_part;
		}
		ShapePart operator-(const ShapePart& other_part) {
			ShapePart shape_part(this->_coordinates, this->_color, this->_radius);
			shape_part.setCoordinates(this->_coordinates - other_part.getCoordinates());
			return shape_part;
		}

		/////////////////
		// Constructor //
		/////////////////

		ShapePart() {}
		ShapePart(sf::Vector2f coordinates, sf::Color color, float radius): _coordinates(coordinates), _color(color), _radius(radius) {}
		ShapePart(float radius): _radius(radius) {}
		ShapePart(sf::Vector2f coordinates): _coordinates(coordinates) {}
		ShapePart(sf::Vector2f coordinates, float radius): _coordinates(coordinates), _radius(radius) {}
		~ShapePart() {}

	private:

		sf::Vector2f _coordinates;
		sf::Color _color;
		float _radius;
};

class SnakePart: public ShapePart {
	public:
		SnakePart(): ShapePart(SNAKE_CIRCLE_RADIUS) {}
		SnakePart(sf::Vector2f coordinates): ShapePart(coordinates, SNAKE_CIRCLE_RADIUS) {}
		SnakePart(sf::Vector2f coordinates, sf::Color color): ShapePart(coordinates, color, SNAKE_CIRCLE_RADIUS) {} 
		~SnakePart() {}
};

class FoodPart: public ShapePart {
	public:
		FoodPart(): ShapePart(FOOD_CIRCLE_RADIUS) {}
		FoodPart(sf::Vector2f coordinates): ShapePart(coordinates, FOOD_CIRCLE_RADIUS) {}
		FoodPart(sf::Vector2f coordinates, sf::Color color): ShapePart(coordinates, color, FOOD_CIRCLE_RADIUS) {} 
		~FoodPart() {}
};



#endif // !PARTSFACTORY_H