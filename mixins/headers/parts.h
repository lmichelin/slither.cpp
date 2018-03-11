#ifndef PARTSFACTORY_H
#define PARTSFACTORY_H

#include <SFML/Graphics.hpp>
#include "parameters.h"

typedef sf::Vector2f coordinates;

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

		ShapePart operator+(const coordinates value) {
			ShapePart shape_part(this->_coordinates, this->_color, this->_radius);
			shape_part.setCoordinates(this->_coordinates + value);
			return shape_part;
		}

		ShapePart operator-(const coordinates value) {
			ShapePart shape_part(this->_coordinates, this->_color, this->_radius);
			shape_part.setCoordinates(this->_coordinates - value);
			return shape_part;
		}

		ShapePart operator*(const float value) {
			ShapePart shape_part(this->_coordinates, this->_color, this->_radius);
			shape_part.setCoordinates(coordinates(this->_coordinates.x * value, this->_coordinates.y * value));
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

	protected:

		sf::Vector2f _coordinates;
		sf::Color _color;
		float _radius;
};

class SnakePart: public ShapePart {
	public:

		///////////////
		// OPERATORS //
		///////////////

		SnakePart operator+(const SnakePart& other_part) {
			SnakePart shape_part(this->_coordinates, this->_color);
			shape_part.setCoordinates(this->_coordinates + other_part.getCoordinates());
			return shape_part;
		}

		SnakePart operator-(const SnakePart& other_part) {
			SnakePart shape_part(this->_coordinates, this->_color);
			shape_part.setCoordinates(this->_coordinates - other_part.getCoordinates());
			return shape_part;
		}

		SnakePart operator+(const coordinates value) {
			SnakePart shape_part(this->_coordinates, this->_color);
			shape_part.setCoordinates(this->_coordinates + value);
			return shape_part;
		}

		SnakePart operator-(const coordinates value) {
			SnakePart shape_part(this->_coordinates, this->_color);
			shape_part.setCoordinates(this->_coordinates - value);
			return shape_part;
		}

		SnakePart operator*(const float value) {
			SnakePart shape_part(this->_coordinates, this->_color);
			shape_part.setCoordinates(coordinates(this->_coordinates.x * value, this->_coordinates.y * value));
			return shape_part;
		}

		///////////////
		//  BUILDER  //
		///////////////

		static SnakePart generateRandom(sf::Color color) {
			return SnakePart(sf::Vector2f(std::rand()*(float)(GAME_SIZE_X*BACKGROUND_SIZE_X)/RAND_MAX, std::rand()*(float)(GAME_SIZE_Y*BACKGROUND_SIZE_Y)/RAND_MAX), color);
		}
		
		SnakePart(): ShapePart(SNAKE_CIRCLE_RADIUS) {}
		SnakePart(sf::Vector2f coordinates): ShapePart(coordinates, SNAKE_CIRCLE_RADIUS) {}
		SnakePart(sf::Vector2f coordinates, sf::Color color): ShapePart(coordinates, color, SNAKE_CIRCLE_RADIUS) {} 
		~SnakePart() {}
};

class FoodPart: public ShapePart {
	public:

		///////////////
		//  BUILDER  //
		///////////////

		static FoodPart generateRandom(sf::Color color) {
			return FoodPart(sf::Vector2f(std::rand()*(float)(GAME_SIZE_X*BACKGROUND_SIZE_X)/RAND_MAX, std::rand()*(float)(GAME_SIZE_Y*BACKGROUND_SIZE_Y)/RAND_MAX), color);
		}


		FoodPart(): ShapePart(FOOD_CIRCLE_RADIUS) {}
		FoodPart(sf::Vector2f coordinates): ShapePart(coordinates, sf::Color::White, FOOD_CIRCLE_RADIUS) {}
		FoodPart(sf::Vector2f coordinates, sf::Color color): ShapePart(coordinates, color, FOOD_CIRCLE_RADIUS) {} 
		~FoodPart() {}
};



#endif // !PARTSFACTORY_H