/*
 * User Class for the server
*/

#ifndef PLAYER_H
#define PLAYER_H

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
#include "timeModule.h"

////////////////////////
// External variables //
////////////////////////

extern std::atomic<int> done_players_count; // Counter to count the number of players that have finished their main loop
extern std::mutex m_compute;
extern std::mutex m_ready_compute;
extern std::condition_variable cv_ready_compute;
extern std::condition_variable cv_compute;

class Player {
	public: 

		//////////////////
		// Main Methods //
		//////////////////

		// initialize a User by generating a random initial position
		void init();

		// Run main loop
		void run();

		// End the game for the player
		virtual void endGame() =0;

		// Do something with the updated player (DEPENDS IF AI OR HUMAN)
		virtual void processOutput() =0;

		// Process the input (DEPENDS IF AI OR HUMAN)
		virtual void processPlayerInput() =0;

		/////////////
		// Getters //
		/////////////

		bool isRunning() const {
			return _is_running;
		}

		Snake& getSnake() {
			return _snake;
		}

		unsigned int getId() const {
			return _id;
		}

		std::list<Player*>& getPlayers() const {
			std::lock_guard<std::mutex> lock(_m);
			return *_players;
		}

		std::list<Food>& getFoods() const {
			std::lock_guard<std::mutex> lock(_m);
			return *_foods;
		}

		bool isPlaying() const {
			return _is_playing;
		}

		static int getPlayerCount() {
			std::lock_guard<std::mutex> lock(_m);			
			return _player_count;
		}

		static int getPlayerPlayingCount() {
			std::lock_guard<std::mutex> lock(_m);
			return _player_playing_count;
		} 

		/////////////
		// Setters //
		/////////////

		static void addToPlayerCount(const int add) {
			std::lock_guard<std::mutex> lock(_m);			
			_player_count += add;
		}

		static void addToPlayerPlayingCount(const int add) {
			std::lock_guard<std::mutex> lock(_m);
			_player_playing_count += add;
		} 

		/////////////////
		// Constructor //
		/////////////////
		
		Player(std::list<Player*>* players, std::list<Food>* foods, unsigned int id): _id(id), _is_running(true), _is_playing(false), _players(players), _foods(foods) {
			addToPlayerCount(1); // Update User count
		}
		virtual ~Player() {};

	protected:

		// Snake Object of the user
		Snake _snake;

		// User id
		unsigned int _id;

		// Is running status
		bool _is_running;

		// input struct
		input _input;

	private: 

		// Is playing status 
		bool _is_playing;

		// Number of users (FOR SYNC)
		static int _player_count;

		// Number of playing users (FOR SYNC)
		static int _player_playing_count;

		// Lock variable to avoid conflicts when retrieving shared data
		static std::mutex _m;

		// List the users
		std::list<Player*>* _players;

		// List the foods
		std::list<Food>* _foods;

		// Generate random coordinates and random parts
		void generateRandomInitialPosition();

		// Update the player position by checking input and update the positions accordingly
		void updatePlayerPosition();

		// Compute the intersections with every object in the game
		void computeIntersection();

		// Compute the intersections with the players
		void computePlayersIntersection();

		// Compute intersections with foods
		void computeFoodsIntersection();

		// COmpute intersections with map edges
		void computeMapIntersection();

		// Set _is_playing to true if not the case and modify playerplayingcount accordingly
		void play();
};

#endif // !USER_H