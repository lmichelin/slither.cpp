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
#include "serverData.h"
#include "serverCommunication.h"
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

		unsigned int getId() const {
			return _id;
		}

		std::list<User>& getUsers() const {
			std::lock_guard<std::mutex> lock(_m);
			return *_users;
		}

		std::list<Food>& getFoods() const {
			std::lock_guard<std::mutex> lock(_m);
			return *_foods;
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
		
		User(sf::TcpSocket* socket, std::list<User>* users, std::list<Food>* foods, unsigned int id): _communication(socket), _id(id), _has_received_data(true), _is_playing(false), _is_connected(true), _users(users), _foods(foods) {
			addToUserCount(1);
			_elapsed_disconnect_time = std::chrono::milliseconds::zero();
			std::cout << "SOCKET USER " << socket->getRemotePort() << "\n";
		}
		~User() {
			addToUserCount(-1);
		}

	private: 
		ServerCommunication _communication;
		unsigned int _id;
		bool _has_received_data;
		bool _is_playing;
		bool _is_connected;
		Snake _snake;
		static int _user_count;
		static int _user_playing_count;
		static std::mutex _m;
		clientInput _input;
		serverData _serverData;
		Time::time_point _disconnect_time; 
		ms _elapsed_disconnect_time;

		// Communication module

		// List the users
		std::list<User>* _users;

		// List the foods
		std::list<Food>* _foods;

		void processClientInput();

		void generateRandomInitialPosition();

		void updateUserPosition();

		void packageServerData();

		void processOutput();

		float getSpeed() const {
			return _input.getData().speed;
		}

		void computeIntersection();

		void computeUsersIntersection();

		void computeFoodsIntersection();

		void play() {
			if (!_is_playing) {
				_is_playing = true;
				addToUserPlayingCount(1);
			}
		}
};

#endif // !USER_H