#include <iostream>
#include <cstdlib>
#include "program.h"

int User::_user_count = 0;
int User::_user_playing_count = 0;
std::mutex User::_m;
std::mutex m_compute;
std::mutex m_ready_compute;
std::condition_variable cv_compute;
std::condition_variable cv_ready_compute;
std::atomic<int> done_users_count;

void Program::init () {
	_is_running = true;

	std::srand(std::time(nullptr)); // use current time as seed for random generator
}

void Program::run () {
	// Run the server so that people can connect to the server in a new thread
	std::thread server_thread(&Server::run, &_server);

	std::list<std::thread> thread_container;

	while (_is_running) {
		std::cout << "New main loop\n";

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
			thread_container.push_back(std::thread(&User::run, std::ref(_users.back())));
		}

		////////////////////////////////
		//  Erase disconnected users  //
		////////////////////////////////

		std::list<User>::iterator it_user = _users.begin();
		std::list<std::thread>::iterator it_thread = thread_container.begin();
		for (;it_user != _users.end();) {
			if (!it_user->isPlaying() && !it_user->isConnected()) {
				if (it_thread->joinable()) {
					it_thread->join();
				}
				_users.erase(it_user++);
				thread_container.erase(it_thread++);
			} else {
				it_user++;
				it_thread++;
			}
		}

		///////////////////////////////
		//        Update Game        //
		///////////////////////////////

		done_users_count = 0;
		cv_compute.notify_all();	
		if (User::getUserPlayingCount()) {
			std::unique_lock<std::mutex> lk_compute(m_compute);
			cv_ready_compute.wait(lk_compute);
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
