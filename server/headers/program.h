#ifndef PROGRAM_H
#define PROGRAM_H

#include "communication.h"
#include <vector>
#include <list>
#include "controller.h"
#include "parameters.h"
#include "snake.h"
#include "food.h"

class Program {
private:
	bool _is_running;

	Controller _controller;

	Communication _communication;

	std::vector<Snake> _snakes;
	std::list<Food> _foods;

	void update ();
public:
	void init ();
	void run ();

	Program ();
	~Program () {}
};

#endif
