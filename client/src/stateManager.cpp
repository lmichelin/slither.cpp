#include "stateManager.h"

void StateManager::switchState(std::string state) {
    _current_state = state;
}

void StateManager::run() {
    _states[_current_state].getServerData();
	_states[_current_state].handleEvents();
	_states[_current_state].update();
	_states[_current_state].sendClientInput();
	_states[_current_state].display();
}