#include "snake.h"
#include <SFML/Network.hpp>

class User {
	public: 

		void run();

		/////////////
		// Getters //
		////////////
		Snake getSnake() const {
			return _snake;
		}

		sf::TcpSocket* getSocket() const {
			return _socket;
		}

		bool isPlaying() const {
			return _playing;
		}

		/////////////////
		// Constructor //
		/////////////////
		User(sf::TcpSocket* socket): _socket(socket), _playing(false) {}
		~User() {
			delete _socket;
		}

	private: 
		Snake _snake;
		sf::TcpSocket* _socket;
		bool _playing;
};