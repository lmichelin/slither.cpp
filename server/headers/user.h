#ifndef USER_H
#define USER_H

#include "snake.h"
#include <SFML/Network.hpp>
#include <string>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <memory>
#include <atomic>

extern std::atomic<int> done_users_count;
extern std::mutex m_positions;
extern std::mutex m_intersections;
extern std::mutex m_ready_positions;
extern std::mutex m_ready_intersections;
extern std::condition_variable cv_ready_positions;
extern std::condition_variable cv_ready_intersections;
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
			return _is_playing;
		}

		bool isConnected() const {
			return _is_connected;
		}

		static int getUserCount() {
			return _user_count;
		}

		static int getUserPlayingCount() {
			return _user_playing_count;
		} 

		/////////////////
		// Constructor //
		/////////////////
		User(std::shared_ptr<sf::TcpSocket> socket): _socket(socket), _is_playing(false), _is_connected(true) {
			_user_count++;
			std::cout << _user_count << std::endl;
		}
		~User() {
			// _user_count--;
		}

	private: 
		Snake _snake;
		std::shared_ptr<sf::TcpSocket> _socket;
		bool _is_playing;
		bool _is_connected;
		static int _user_count;
		static int _user_playing_count;

		void play() {
			if (!_is_playing) {
				_is_playing = true;
				_user_playing_count++;
			}
		}
};

#endif // !USER_H