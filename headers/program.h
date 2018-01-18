#ifndef PROGRAM_H
#define PROGRAM_H

#include <SFML/Graphics.hpp>
#include "controller.h"
#include "parameters.h"

class Program {
private:
	bool _is_running;

	sf::RenderWindow _window;
	Controller _controller;

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
