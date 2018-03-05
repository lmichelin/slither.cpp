#include <iostream>
#include <cstdlib>
#include "program.h"

// Initialize User external variables
int User::_user_count = 0;
int User::_user_playing_count = 0;
std::mutex User::_m;
std::mutex m_compute;
std::mutex m_ready_compute;

// Initialize condition variables (Useful to wait for many threads)
std::condition_variable cv_compute;
std::condition_variable cv_ready_compute;

// Initialize users count (to count the number of users that have finished the computation)
std::atomic<int> done_users_count;

void Program::init () {
	_is_running = true;
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
			_users.push_back(User(socket, &_users));

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
		// std::cout << "Program waiting\n"; // THREAD DEBUGGING

		// Wait for the users threads to finish computation of postitions and intersections ... If it takes too much time, break after 100ms
		std::unique_lock<std::mutex> lk_compute(m_compute);
		cv_ready_compute.wait_for(lk_compute, std::chrono::milliseconds(100));

		// std::this_thread::sleep_for(std::chrono::milliseconds(200));
	}
}