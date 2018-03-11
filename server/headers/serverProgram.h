/*
 * Main Program class that will execute the main loop for the server
*/

#ifndef PROGRAM_H
#define PROGRAM_H

#include <vector>
#include <list>
#include <thread>
#include <mutex>
#include <memory>
#include "parameters.h"
#include "server.h"
#include "player.h"
#include "user.h"
#include "AI.h"
#include "food.h"
#include "safequeue.h"
#include <SFML/Network.hpp>

class Program {
	public:

		//////////////////
		// Main Methods //
		//////////////////

		// Initialize game by setting running to true and initialize time
		void init ();

		// Run game (Main loop for the game with ticks)
		void run ();

		// Generate user id
		static unsigned int generateId () {
			return _player_id_counter++;
		}

		// Generate limited number of foods
		void initializeFoods();

		// Generate limited number of AIs
		void initializeAIs();

		/////////////////
		//   Getters   //
		/////////////////

		SafeQueue<sf::TcpSocket*>& getSocketQueue() {
			return _socket_queue;
		}

		std::list<Player*>& getPlayers() {
			return _players;
		}

		/////////////////
		// Constructor //
		/////////////////

		Program (int port): _server(port, &_socket_queue) {
			// Initialize server on construction
			_server.init();
		};
		~Program () {}

	private:
	
		// Tells whether the program is running or not
		bool _is_running; 

		// Int to generate user id
		static unsigned int _player_id_counter;

		// Server class of the server program
		Server _server; 

		// Safequeue to see if a new user is trying to connect through a new socket (IMPORTANT FOR MULTITHREADING)
		SafeQueue<sf::TcpSocket*> _socket_queue;

		// List the players
		std::list<Player*> _players;

		// List the food objects
		std::list<Food> _foods;

		// List the players
		std::list<User> _users;

		// List the food objects
		std::list<AI> _AIs;
};

#endif
