#ifndef PROGRAM_H
#define PROGRAM_H

#include <vector>
#include <list>
#include <thread>
#include <mutex>
#include "parameters.h"
#include "server.h"
#include "user.h"
#include "food.h"
#include "safequeue.h"
#include <SFML/Network.hpp>

class Program {
	public:

		// Initialize game
		void init ();

		// Run game
		void run ();

		// Launch a new user
		void launchUser(sf::TcpSocket* socket);

		SafeQueue<sf::TcpSocket*>& getSocketQueue() {
			return _socket_queue;
		}

		std::vector<User> getUsers() {
			return _users;
		}

		/////////////////
		// Constructor //
		/////////////////
		Program (int port): _server(port, &_socket_queue) {
			_server.init();
		};
		~Program () {}

	private:
		bool _is_running;

		Server _server;
		SafeQueue<sf::TcpSocket*> _socket_queue;

		std::vector<User> _users;
		std::list<Food> _foods;

		void update ();
};

#endif
