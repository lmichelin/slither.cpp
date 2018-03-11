/*
 * User Class for the server
*/

#ifndef USER_H
#define USER_H

#include <SFML/Network.hpp>
#include <string>
#include <list>

#include "snake.h"
#include "server.h"
#include "clientInput.h"
#include "serverData.h"
#include "serverCommunication.h"
#include "timeModule.h"
#include "player.h"


class User: public Player {
	public: 

		//////////////////
		// Main Methods //
		//////////////////

		// Send everything to the user
		void processOutput();

		// Receive user input and process it
		void processPlayerInput();

		void endGame();

		/////////////
		// Getters //
		/////////////

		bool isConnected() const {
			return _is_connected;
		}

		/////////////////
		// Constructor //
		/////////////////
		
		User(sf::TcpSocket* socket, std::list<Player*>* players, std::list<Food>* foods, unsigned int id): Player(players, foods, id), _communication(socket), _is_connected(true), _has_received_data(true) {
			std::cout << "USER CREATED" << '\n';
		}
		~User() {}

	private: 

		// Communication module
		ServerCommunication _communication;

		// Is connected status
		bool _is_connected;

		// Data Modules
		clientInput _client_input;
		serverData _serverData;

		// Speed modules for speed and disconnection handlers
		TimeModule _disconnectTimeHandler;

		// Variable that tells if server has received client data (USEFUL FOR PING PONG)
		bool _has_received_data;

		// Put the data to be sent in serverData
		void packageServerData();
};

#endif // !USER_H