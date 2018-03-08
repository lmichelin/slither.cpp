#ifndef STATE_MANAGER_H
#define STATE_MANAGER_H

#include <map>
#include "state.h"

class StateManager
{
public:

	void switchState(std::string state);

	// Wrapping state methods
	void getServerData();
	void handleEvents();
	void update();
	void display();

	StateManager();
	~StateManager();

private:
	std::map<std::string, State*> _states;
	std::string _current_state;
};

#endif // !STATE_MANAGER_H