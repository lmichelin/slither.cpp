#ifndef PROGRAM_H
#define PROGRAM_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <list>
#include "controller.h"
#include "parameters.h"
#include "snake.h"
#include "food.h"
// #include "communication.h"

class Program {
private:
	bool _is_running;

	sf::RenderWindow _window;
	Controller _controller;

	// Communication _communication;

	std::vector<Snake> _snakes;
	std::list<Food> _foods;

	void update ();
	void display ();
	void handleEvents ();
public:
	void init ();
	void run ();

	Program ();
	~Program () {}
};

#endif
