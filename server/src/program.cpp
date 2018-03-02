#include <iostream>
#include <cstdlib>
#include "program.h"

void Program::init () {
	_is_running = true;

	std::srand(std::time(nullptr)); // use current time as seed for random generator
}

void Program::run () {
	// Run the server so that people can connect to the server in a new thread
	std::thread server_thread(&Server::run, &_server);

	while (_is_running) {
		// When a new user connects, create a user object in a new thread with his socket in it
		sf::TcpSocket* socket;
		if (_socket_queue.pop(socket)) {
			launchUser(socket);
		}
	}
}

// Launch a new user in a new thread
void Program::launchUser(sf::TcpSocket* socket) {
	User new_user(socket);
	_users.push_back(new_user); // Add the user in the users array

	// Launch new thread with user action
	std::thread new_user_thread(&User::run, &new_user);
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
