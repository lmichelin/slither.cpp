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
#include "user.h"
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

		/////////////////
		//   Getters   //
		/////////////////

		SafeQueue<std::shared_ptr<sf::TcpSocket> >& getSocketQueue() {
			return _socket_queue;
		}

		std::list<User>& getUsers() {
			return _users;
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

		// Server class of the server program
		Server _server; 

		// Safequeue to see if a new user is trying to connect through a new socket (IMPORTANT FOR MULTITHREADING)
		SafeQueue<std::shared_ptr<sf::TcpSocket> > _socket_queue;

		// List the users
		std::list<User> _users;

		// List the food objects
		std::list<Food> _foods;
};

#endif
