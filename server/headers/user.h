/*
 * User Class for the server
*/

#ifndef USER_H
#define USER_H

#include "snake.h"
#include <SFML/Network.hpp>
#include <string>
#include <mutex>
#include "server.h"
#include <condition_variable>
#include <thread>
#include <memory>
#include <atomic>

////////////////////////
// External variables //
////////////////////////

extern std::atomic<int> done_users_count; // Counter to count the number of users that have finished their main loop
extern std::mutex m_compute;
extern std::mutex m_ready_compute;
extern std::condition_variable cv_ready_compute;
extern std::condition_variable cv_compute;

class User {
	public: 

		void run();
		void send(int header, sf::Packet packet);
		void receive(int& header, sf::Packet& packet);

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
			std::lock_guard<std::mutex> lock(_m);			
			return _user_count;
		}

		static int getUserPlayingCount() {
			std::lock_guard<std::mutex> lock(_m);
			return _user_playing_count;
		} 

		static void addToUserCount(int add) {
			std::lock_guard<std::mutex> lock(_m);			
			_user_count += add;
		}

		static void addToUserPlayingCount(int add) {
			std::lock_guard<std::mutex> lock(_m);
			_user_playing_count += add;
		} 

		/////////////////
		// Constructor //
		/////////////////
		User(std::shared_ptr<sf::TcpSocket> socket): _socket(socket), _is_playing(false), _is_connected(true) {
			addToUserCount(1);
			// std::cout << _user_count << std::endl;
		}
		~User() {
			addToUserCount(-1);
		}

	private: 
		Snake _snake;
		std::shared_ptr<sf::TcpSocket> _socket;
		bool _is_playing;
		bool _is_connected;
		static int _user_count;
		static int _user_playing_count;
		static std::mutex _m;

		void processClientInput();

		void sendClientData();

		void computePosition();

		void computeIntersection();

		void play() {
			if (!_is_playing) {
				_is_playing = true;
				addToUserPlayingCount(1);
			}
		}
};

#endif // !USER_H