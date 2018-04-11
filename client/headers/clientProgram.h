#ifndef PROGRAM_H
#define PROGRAM_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <list>
#include "controller.h"
#include "parameters.h"
#include "snake.h"
#include "food.h"
#include "serverData.h"
#include "clientCommunication.h"
#include "stateManager.h"
#include "draw.h"

// init SFML settings
void initSettings ();

class Program {

	public:

		//////////////////
		// Main Methods //
		//////////////////

		// Launch program
		void init ();

		// Run main routine
		void run ();

		/////////////////
		// Constructor //
		/////////////////

		Program (std::string hostname);
		~Program () {}

	private:

		// CHeck if running
		bool _is_running;

		// Client window
		sf::RenderWindow _window;

		// Client communication module
		ClientCommunication _communication;

		// State manager module
		StateManager _state_manager;

		void disconnect();
};

#endif
