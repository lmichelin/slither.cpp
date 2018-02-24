#include <iostream>
#include <cstdlib>
#include "program.h"

Program::Program () {
	_is_running = false;
}

void Program::init () {
	_is_running = true;
	sf::Vector2f init_pos(200,200);
	Snake my_snake(init_pos);
	_snakes.push_back(my_snake);

	std::srand(std::time(nullptr)); // use current time as seed for random generator
}

void Program::run () {
	while (_is_running) {
		update();
	}

}

void Program::update () {
	// Refresh snake position
	// sf::Vector2f head_aim = _controller.getAim();
	// _snakes[0].interpolate(head_aim, _controller.getSpeed());
	// if (std::rand()/(float)RAND_MAX < FOOD_PROBA) {
	// 	sf::Vector2f new_food_position(std::rand()*(float)WINDOW_SIZE_X/RAND_MAX,std::rand()*(float)WINDOW_SIZE_Y/RAND_MAX);
	// 	Food new_food(new_food_position);
	// 	_foods.push_back(new_food);
	// }

	// for (std::list<Food>::iterator it = _foods.begin(); it != _foods.end(); it++) {
	// 	if (_snakes[0].checkFoodIntersection(*it)) {
	// 		it = _foods.erase(it);
	// 		_snakes[0].addTail(ADD_TAIL);
	// 	}
	// }

	// End game test
	// if (position.x < SNAKE_CIRCLE_RADIUS || position.x > WINDOW_SIZE_X - SNAKE_CIRCLE_RADIUS || position.y < SNAKE_CIRCLE_RADIUS || position.y > WINDOW_SIZE_Y - SNAKE_CIRCLE_RADIUS) {
	// 	_is_running = false;
	// }
}
