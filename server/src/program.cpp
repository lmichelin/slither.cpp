#include <iostream>
#include <cstdlib>
#include "program.h"

int User::_user_count = 0;
int User::_user_playing_count = 0;
std::mutex m_positions;
std::mutex m_intersections;
std::mutex m_ready_positions;
std::mutex m_ready_intersections;
std::condition_variable cv_positions;
std::condition_variable cv_intersections;
std::condition_variable cv_ready_positions;
std::condition_variable cv_ready_intersections;
std::atomic<int> done_users_count;

void Program::init () {
	_is_running = true;

	std::srand(std::time(nullptr)); // use current time as seed for random generator
}

void Program::run () {
	// Run the server so that people can connect to the server in a new thread
	std::thread server_thread(&Server::run, &_server);

	std::vector<std::thread> thread_container;

	while (_is_running) {

		///////////////////////////////
		// Check new user connection //
		///////////////////////////////

		// When a new user connects, create a user object in a new thread with his socket in it
		std::shared_ptr<sf::TcpSocket> socket;
		if (_socket_queue.pop(socket)) {
			// Add the user in the users array
			// User new_user(socket);
			_users.push_back(User(socket));

			// Start the run routine in a thread
			thread_container.push_back(std::thread(&User::run, _users.back()));
		}

		///////////////////////////////
		//  Check for disconnection  //
		///////////////////////////////

		// std::list<User>::iterator it;
		// for (it = _users.begin(); it != _users.end(); it++) {

		// }

		////////////////////////////////
		//  Erase disconnected users  //
		////////////////////////////////

		// std::this_thread::sleep_for(std::chrono::seconds(1));


		///////////////////////////////
		//        Update Game        //
		///////////////////////////////

		if (User::getUserPlayingCount()) {

			done_users_count = 0;
			cv_positions.notify_all();	


			std::unique_lock<std::mutex> lk_positions(m_ready_positions);
			cv_ready_positions.wait(lk_positions);


			done_users_count = 0;
			cv_intersections.notify_all();

			std::unique_lock<std::mutex> lk_intersections(m_ready_intersections);
			cv_ready_intersections.wait(lk_intersections);
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(200));
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
