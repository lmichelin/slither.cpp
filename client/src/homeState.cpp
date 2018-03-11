#include "state.h"
#include "SFML/Graphics.hpp"
#include "draw.h"

void HomeState::init() {
    if (!_texture.loadFromFile("build/static/home.png")) {
		// error when load file
		exit(1);
	}
}

void HomeState::getServerData() {

}

void HomeState::handleEvents() {
    sf::Event event;
	while (_window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
			// Disconnect from server
			_communication->disconnect();
			// Close window
			_window->close();
		}

        if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::Return) {
				State::setNextState("game");
			}
		}
    }
}

void HomeState::update() {

}

void HomeState::sendClientInput() {

}

void HomeState::display() {

    sf::Vector2f origin(_texture.getSize().x / 2 ,_texture.getSize().y / 2);

	_window->clear();

	drawTexture(_window, origin, _texture);

	// Display Result
	_window->display();

    // _window->draw(text);

}

void HomeState::quit() {
    
}