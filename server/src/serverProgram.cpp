#include <iostream>
#include <cstdlib>
#include "serverProgram.h"
#include "parts.h"

// Initialize User external variables
int AI::_AI_counter = 0;
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

	std::list<std::thread> thread_container;

	// Launch the AIs in their threads
	std::list<Player*>::iterator it_AI; 
	for (it_AI = _players.begin(); it_AI != _players.end(); it_AI++) {
		thread_container.push_back(std::thread(&Player::run, *it_AI));
	}

	while (_is_running) {
		// std::cout << "New main loop\n";

		///////////////////////////////
		// Check new user connection //
		///////////////////////////////

		// When a new user connects, create a user object in a new thread with his socket in it
		sf::TcpSocket* socket;
		if (_socket_queue.pop(socket)) {
			// Add the user in the players array
			// User new_user(socket);
			_players.push_back(new User(socket, &_players, &_foods, generateId()));

			// Initialize user
			_players.back()->init();

			// Start the run routine in a thread
			thread_container.push_back(std::thread(&Player::run, _players.back()));
		}

		/////////////////////////////////////////////////////////
		//  Erase disconnected players AND REPLACE WITH FOODS  //
		/////////////////////////////////////////////////////////

		std::list<Player*>::iterator it_player = _players.begin();
		std::list<std::thread>::iterator it_thread = thread_container.begin();
		for (;it_player != _players.end();) {
			if (!(*it_player)->isPlaying() && !(*it_player)->isRunning()) {
				if (it_thread->joinable()) {
					it_thread->join();
				}
				std::cout << "REPLACING WITH FOODS" << '\n';
				for (size_t i = 0; i < (*it_player)->getSnake().getBody().getParts().size(); i+=2) {
					_foods.push_back(Food(FoodPart((*it_player)->getSnake().getBody().getParts()[i].getCoordinates())));
				}
				std::cout << "ERASING USER" << '\n';
				delete *it_player;
				it_player = _players.erase(it_player);
				std::cout << "ERASING THREAD" << '\n';
				thread_container.erase(it_thread++);
			} else {
				++it_player;
				++it_thread;
			}
		}

		////////////////////
		//  POPULATE AIs  //
		////////////////////
		if (AI::getAICounter() < AI_NUMBER) {
			std::cout << AI::getAICounter() << '\n';
			std::cout << thread_container.size() << '\n';
			// Create new AI in the _players list
			_players.push_back(new AI(&_players, &_foods, generateId()));

			// Initialize AI
			_players.back()->init();

			thread_container.push_back(std::thread(&Player::run, _players.back()));
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
		cv_ready_compute.wait_for(lk_compute, std::chrono::milliseconds(8));

		std::this_thread::sleep_for(std::chrono::milliseconds(8));
	}
}

void Program::initializeFoods() {
	for (size_t i = 0; i < FOOD_NUMBER - 1; i++) {
		_foods.push_back(Food(FoodPart::generateRandom(sf::Color::White)));
	}
}

void Program::initializeAIs() {
	for (size_t i = 0; i < AI_NUMBER; i++) {
		// Create new AI in the _players list
		_players.push_back(new AI(&_players, &_foods, generateId()));

		// Initialize AI
		_players.back()->init();
	}
}