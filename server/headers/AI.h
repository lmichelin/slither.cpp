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

// States of the AI
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

		/////////////
		// Getters //
		/////////////

		state getState() const {
			return _state;
		}

		static int getAICounter() {
			return _AI_counter;
		}

		/////////////
		// Setters //
		/////////////

		void addToAICounter(int n) {
			_AI_counter += n;
		}

		/////////////////
		// Constructor //
		/////////////////
		
		AI(std::list<Player*>* players, std::list<Food>* foods, unsigned int id): Player(players, foods, id) {
			addToAICounter(1);
		}
		~AI() {
			addToAICounter(-1);
		}

	private:

		// AI counter
		static int _AI_counter;

		// State variable for the state machine
		state _state;

		// Time module for search patterns
		TimeModule _time;

		// Check if any foods are on snake's aim
		bool checkFoodAimAndDistance();

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