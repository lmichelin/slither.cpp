#ifndef USER_H
#define USER_H

#include "snake.h"
#include <SFML/Network.hpp>
#include <string>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <memory>

extern std::mutex m;
extern std::condition_variable cv_positions;
extern std::condition_variable cv_intersections;

class User {
	public: 

		void run();

		/////////////
		// Getters //
		////////////
		Snake& getSnake() {
			return _snake;
		}

		std::shared_ptr<sf::TcpSocket> getSocket() const {
			return _socket;
		}

		bool isPlaying() const {
			return _playing;
		}

		bool isConnected() const {
			return _is_connected;
		}

		/////////////////
		// Constructor //
		/////////////////
		User(std::shared_ptr<sf::TcpSocket> socket): _socket(socket), _playing(false), _is_connected(true) {
			_user_count++;
		}
		~User() {
			_user_count--;
		}

	private: 
		Snake _snake;
		std::shared_ptr<sf::TcpSocket> _socket;
		bool _playing;
		bool _is_connected;
		static int _user_count;
};

#endif // !USER_H