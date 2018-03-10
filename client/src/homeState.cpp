#include "state.h"
#include "SFML/Graphics.hpp"

void HomeState::init() {

}

void HomeState::getServerData() {

}

void HomeState::handleEvents() {
    sf::Event event;
	while (_window->pollEvent(event)) {
        if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::BackSpace) {
				State::setNextState("game");
			}
		}
        if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Right)
            {
                std::cout << "the right button was pressed" << std::endl;
                std::cout << "mouse x: " << event.mouseButton.x << std::endl;
                std::cout << "mouse y: " << event.mouseButton.y << std::endl;
            }
        }
    }
}

void HomeState::update() {

}

void HomeState::sendClientInput() {

}

void HomeState::display() {

    // _window->draw(text);

}

void HomeState::quit() {
    _communication->init();
}