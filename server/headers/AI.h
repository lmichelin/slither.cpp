/*
 * User Class for the server
*/

#ifndef IA_H
#define IA_H

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

enum state {Avoiding, Feeding};

class AI: public Player {
	public: 

		//////////////////
		// Main Methods //
		//////////////////

		// For the IA just do not do anything ...
		void processOutput() {};

		// Receive user input and process it
		void processPlayerInput();

		// End the game
		void endGame();

		// Disconnect the user from the server
		void disconnect() {};

		/////////////
		// Getters //
		/////////////

		state getState() const {
			return _state;
		}

		/////////////////
		// Constructor //
		/////////////////
		
		AI(std::list<Player*>* players, std::list<Food>* foods, unsigned int id): Player(players, foods, id) {}
		~AI() {}

	private:

		// State variable for the state machine
		state _state;

		// Time module for search patterns
		TimeModule _time;

		// Check if any foods are on snake's aim
		bool checkFoodAimAndDistance();

		// Check if there are enemies in front
		bool checkForEnemy();

		// Check if we are leaving the map
		bool checkForMap();

		// Turn right
		void rotateRight();

		// Turn left
		void rotateLeft();

		// Randomly turn right or left
		void randomTurn();

		// Go straigth
		void goStraight();

		// Accelerate
		void accelerate();

		// Deccelerate
		void deccelerate();

		// Search routine
		void search();

		// Variable to check if the player is turning in the search routine
		bool _is_turning;

		// Avoid routine
		void avoid();

};

#endif // !USER_H