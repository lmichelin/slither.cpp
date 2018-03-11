#include <iostream>
#include <cstdlib>
#include "serverProgram.h"
#include "parts.h"

// Initialize User external variables
int Player::_player_count = 0;
int Player::_player_playing_count = 0;
std::mutex Player::_m;
std::mutex m_compute;
std::mutex m_ready_compute;
unsigned int Program::_player_id_counter = 0;

// Initialize condition variables (Useful to wait for many threads)
std::condition_variable cv_compute;
std::condition_variable cv_ready_compute;

// Initialize users count (to count the number of users that have finished the computation)
std::atomic<int> done_players_count;

void Program::init () {
	// Set is running state
	_is_running = true;

	// Generate the foods
	initializeFoods();

	// Generate the AIs
	initializeAIs();
}

void Program::run () {
	// Run the server so that people can connect to the server in a new thread
	std::thread server_thread(&Server::run, &_server);

	std::list<std::thread> user_thread_container;
	std::list<std::thread> AI_thread_container;

	// Launch the AIs in their threads
	std::list<AI>::iterator it_AI; 
	for (it_AI = _AIs.begin(); it_AI != _AIs.end(); it_AI++) {
		AI_thread_container.push_back(std::thread(&Player::run, &(*it_AI)));
	}

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
			_users.push_back(User(socket, &_players, &_foods, generateId()));

			// Put the user in the player array
			_players.push_back(&_users.back());

			// Initialize user
			_users.back().init();

			// Start the run routine in a thread
			user_thread_container.push_back(std::thread(&Player::run, &_users.back()));
		}

		////////////////////////////////
		//  Erase disconnected users  //
		////////////////////////////////

		std::list<User>::iterator it_user = _users.begin();
		std::list<std::thread>::iterator it_thread = user_thread_container.begin();
		for (;it_user != _users.end();) {
			if (!it_user->isPlaying() && !it_user->isConnected()) {
				if (it_thread->joinable()) {
					it_thread->join();
				}
				std::cout << "ERASING USER" << '\n';
				_users.erase(it_user++);
				std::cout << "ERASING THREAD" << '\n';
				user_thread_container.erase(it_thread++);
			} else {
				it_user++;
				it_thread++;
			}
		}

		/////////////////////////////
		//  Erase disconnected AI  //
		/////////////////////////////

		std::list<AI>::iterator it_IA = _AIs.begin();
		std::list<std::thread>::iterator AI_it_thread = AI_thread_container.begin();
		for (;it_IA != _AIs.end();) {
			if (!it_IA->isPlaying() && !it_IA->isRunning()) {
				if (AI_it_thread->joinable()) {
					AI_it_thread->join();
				}
				_AIs.erase(it_IA++);
				AI_thread_container.erase(AI_it_thread++);
			} else {
				it_IA++;
				AI_it_thread++;
			}
		}

		//////////////////////////////////
		//  Erase disconnected Players  //
		//////////////////////////////////

		_players.remove(NULL);
		std::cout << "ERASED PLAYERS" << '\n';

		////////////////////
		//  POPULATE AIs  //
		////////////////////

		if (_AIs.size() < AI_NUMBER) {
			// Create new AI in the AI list
			_AIs.push_back(AI(&_players, &_foods, generateId()));

			// Put the Ai in the player list as pointer
			_players.push_back(&_AIs.back());

			// Initialize AI
			_AIs.back().init();

			AI_thread_container.push_back(std::thread(&Player::run, &_AIs.back()));
		}

		///////////////////////////////
		//        Update Game        //
		///////////////////////////////

		done_players_count = 0;
		// std::cout << "Prgram notifying\n"; // THREAD DEBUGGING
		cv_compute.notify_all(); // Notify all users threads that they may compute their positions and intersections

		// Wait for the users threads to finish computation of postitions and intersections ... If it takes too much time, break after 100ms
		std::unique_lock<std::mutex> lk_compute(m_compute);
		// std::cout << "Program waiting\n"; // THREAD DEBUGGING
		cv_ready_compute.wait_for(lk_compute, std::chrono::milliseconds(4));

		std::this_thread::sleep_for(std::chrono::milliseconds(4));
	}
}

void Program::initializeFoods() {
	for (size_t i = 0; i < FOOD_NUMBER - 1; i++) {
		_foods.push_back(Food(FoodPart::generateRandom(sf::Color::White)));
	}
}

void Program::initializeAIs() {
	for (size_t i = 0; i < AI_NUMBER; i++) {
		// Create new AI in the AI list
		_AIs.push_back(AI(&_players, &_foods, generateId()));

		// Put the Ai in the player list as pointer
		_players.push_back(&_AIs.back());

		// Initialize AI
		_AIs.back().init();
	}
}