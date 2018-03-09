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

class Program {

	public:
		void init ();
		void run ();
		
		Program ();
		~Program () {}

	private:
		bool _is_running;

		sf::RenderWindow _window;
		ClientCommunication _communication;
		StateManager _state_manager;

		void disconnect();
};

#endif