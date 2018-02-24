#ifndef PROGRAM_H
#define PROGRAM_H

#include "communication.h"
#include <vector>
#include <list>
#include "parameters.h"
#include "snake.h"
#include "food.h"

class Program {
private:
	bool _is_running;

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
