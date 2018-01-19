#ifndef FOOD_H_
#define FOOD_H_

#include <SFML/Graphics.hpp>

class Food {
public:
	sf::Vector2f getPosition() const {
		return _position;
	}

	friend void drawFoods (sf::RenderWindow& _window, const Food&);

	Food(sf::Vector2f p) : _position(p) {}

private:
	sf::Vector2f _position;

};

#endif
