#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <SFML/Network.hpp>

class Controller {
private:
	float _speed;
	bool _rotating_right;
	bool _rotating_left;

	sf::Vector2f _aim;

public:
	void rotateLeft (bool);
	void rotateRight (bool);
	void setSpeed (float);
	float getSpeed ();

	void updateAim ();
	sf::Vector2f getAim ();

	friend sf::Packet &operator>>(sf::Packet &packet, Controller &controller);

	Controller ();
	~Controller () {}
};

#endif
