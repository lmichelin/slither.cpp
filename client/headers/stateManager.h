#ifndef STATE_MANAGER_H
#define STATE_MANAGER_H

#include <map>
#include "state.h"
#include "clientCommunication.h"

class StateManager
{
public:

	void switchState(std::string state);

	// Run current state
	void run();

	StateManager(sf::RenderWindow* window, ClientCommunication* communication) : _current_state("home") {
		_states["home"] = HomeState(window, communication);
		_states["game"] = GameState(window, communication);
	}
	~StateManager();

private:
	std::map<std::string, State> _states;
	std::string _current_state;
};

#endif // !STATE_MANAGER_H