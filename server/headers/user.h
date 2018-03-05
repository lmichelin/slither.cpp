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
#include <list>
#include <memory>
#include <atomic>
#include "input.h"
#include "clientData.h"
#include <chrono>

////////////////////////
// External variables //
////////////////////////

extern std::atomic<int> done_users_count; // Counter to count the number of users that have finished their main loop
extern std::mutex m_compute;
extern std::mutex m_ready_compute;
extern std::condition_variable cv_ready_compute;
extern std::condition_variable cv_compute;

typedef std::chrono::high_resolution_clock Time;
typedef std::chrono::milliseconds ms;
typedef std::chrono::duration<float> fsec;

class User {
	public: 

		//////////////////
		// Main Methods //
		//////////////////

		void init();
		void run();

		/////////////
		// Getters //
		/////////////
		Snake& getSnake() {
			return _snake;
		}

		std::shared_ptr<sf::TcpSocket> getSocket() const {
			return _socket;
		}

		std::list<User>& getUsers() const {
			std::lock_guard<std::mutex> lock(_m);
			return *_users;
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

		/////////////
		// Setters //
		/////////////

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
		
		User(std::shared_ptr<sf::TcpSocket> socket, std::list<User>* users): _socket(socket), _is_playing(false), _is_connected(true), _users(users) {
			addToUserCount(1);
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
		input _input;
		clientData _clientData;
		Time::time_point _disconnect_time; 
		ms _elapsed_disconnect_time;

		// List the users
		std::list<User>* _users;

		void processClientInput();

		void sendClientData();

		void computePosition();

		void updateOtherUserPositions();

		void generateRandomInitialPosition();

		void updateUserPosition();

		float getSpeed() const {
			return _input.speed;
		}

		void computeIntersection();

		void send(int header, sf::Packet packet, sf::Socket::Status& status);
		void send(int header, sf::Packet packet);
		void receive(int& header, sf::Packet& packet, sf::Socket::Status& status);
		void receive(int& header, sf::Packet& packet);

		void play() {
			if (!_is_playing) {
				_is_playing = true;
				addToUserPlayingCount(1);
			}
		}
};

#endif // !USER_H