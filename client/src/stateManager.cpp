#include "stateManager.h"

std::string State::_next_state = "";
std::string State::_message = "";

void StateManager::initFirstState(std::string first_state) {
	State::setNextState(first_state);
	_current_state = first_state;
	init(); // init first state
}

void StateManager::switchState() {
	if (State::getNextState() != _current_state) {
		quit(); // finish previous state
    	_current_state = State::getNextState();
		init(); // init next state
	}
}

void StateManager::addState(std::string name, std::unique_ptr<State>& state) {
	_states[name] = std::move(state);
}

void StateManager::init() {
	_states[_current_state]->init();
}

void StateManager::getServerData() {
    _states[_current_state]->getServerData();
}

void StateManager::handleEvents() {
	_states[_current_state]->handleEvents();
}

void StateManager::update() {
	_states[_current_state]->update();
}

void StateManager::sendClientInput() {
	_states[_current_state]->sendClientInput();
}

void StateManager::display() {
	_states[_current_state]->display();
}

void StateManager::quit() {
	_states[_current_state]->quit();
}
