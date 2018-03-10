#ifndef STATE_MANAGER_H
#define STATE_MANAGER_H

#include <map>
#include "state.h"
#include "clientCommunication.h"

class StateManager
{
public:
	void initFirstState(std::string first_state);

	void switchState();
	void addState(std::string name, std::unique_ptr<State>& state);

	// Run current state
	void init();
	void getServerData();
	void handleEvents();
	void update();
	void sendClientInput();
	void display();
	void quit();

	StateManager() {}
	~StateManager() {}

private:
	std::map<std::string, std::unique_ptr<State> > _states;
	std::string _current_state;
};

#endif // !STATE_MANAGER_H