#include "stateManager.h"

void StateManager::switchState(std::string state) {
    _current_state = state;
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
