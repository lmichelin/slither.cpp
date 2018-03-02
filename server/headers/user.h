#include "snake.h"
#include <SFML/Network.hpp>
#include <string>
#include <thread>
#include <memory>

class User {
	public: 

		void run();

		/////////////
		// Getters //
		////////////
		Snake getSnake() const {
			return _snake;
		}

		std::shared_ptr<sf::TcpSocket> getSocket() const {
			return _socket;
		}

		bool isPlaying() const {
			return _playing;
		}

		/////////////////
		// Constructor //
		/////////////////
		User(std::shared_ptr<sf::TcpSocket> socket): _socket(socket), _playing(false) {}
		~User() {
			// delete _socket;
		}

	private: 
		Snake _snake;
		std::shared_ptr<sf::TcpSocket> _socket;
		bool _playing;
};