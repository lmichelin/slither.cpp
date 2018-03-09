#include <iostream>
#include <cstdlib>
#include "serverProgram.h"
#include "parts.h"

// Initialize User external variables
int User::_user_count = 0;
int User::_user_playing_count = 0;
std::mutex User::_m;
std::mutex m_compute;
std::mutex m_ready_compute;
unsigned int Program::_user_id_counter = 0;

// Initialize condition variables (Useful to wait for many threads)
std::condition_variable cv_compute;
std::condition_variable cv_ready_compute;

// Initialize users count (to count the number of users that have finished the computation)
std::atomic<int> done_users_count;

void Program::init () {
	// Set is running state
	_is_running = true;

	// Generate the foods
	initializeFoods();
}

void Program::run () {
	// Run the server so that people can connect to the server in a new thread
	std::thread server_thread(&Server::run, &_server);

	std::list<std::thread> thread_container;

	while (_is_running) {
		// std::cout << "New main loop\n";

		///////////////////////////////
		// Check new user connection //
		///////////////////////////////

		// When a new user connects, create a user object in a new thread with his socket in it
		sf::TcpSocket* socket;
		if (_socket_queue.pop(socket)) {
			// Add the user in the users array
			// User new_user(socket);
			std::cout << "NEW USER" << '\n';
			_users.push_back(User(socket, &_users, &_foods, generateId()));

			// Initialize user
			_users.back().init();

			// Start the run routine in a thread
			thread_container.push_back(std::thread(&User::run, &_users.back()));
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
		// std::cout << "Prgram notifying\n"; // THREAD DEBUGGING
		cv_compute.notify_all(); // Notify all users threads that they may compute their positions and intersections

		// Wait for the users threads to finish computation of postitions and intersections ... If it takes too much time, break after 100ms
		std::unique_lock<std::mutex> lk_compute(m_compute);
		// std::cout << "Program waiting\n"; // THREAD DEBUGGING
		cv_ready_compute.wait_for(lk_compute, std::chrono::milliseconds(20));

		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}

void Program::initializeFoods() {
	for (size_t i = 0; i < FOOD_NUMBER - 1; i++) {
		_foods.push_back(Food(FoodPart::generateRandom(sf::Color::White)));
	}
}