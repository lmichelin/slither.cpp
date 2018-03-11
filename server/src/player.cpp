#include "player.h"
#include "serverData.h"
#include "input.h"
#include <iostream>
#include <list>
#include <cmath>

		/////////////////////
		// INITIALIZATIONS //
		/////////////////////

void Player::generateRandomInitialPosition() {

	// Generate a random position
	SnakePart position(sf::Vector2f(std::rand()*(float)(GAME_SIZE_X*BACKGROUND_SIZE_X)/RAND_MAX, std::rand()*(float)(GAME_SIZE_Y*BACKGROUND_SIZE_Y)/RAND_MAX), sf::Color::Red);

	// Get Map Center
	ShapePart center(sf::Vector2f(((GAME_SIZE_X*BACKGROUND_SIZE_X)-1)/2, ((GAME_SIZE_Y*BACKGROUND_SIZE_Y)-1)/2));
	
	// Try again if position is the center of the map
	if (position.getCoordinates() == center.getCoordinates())
		return generateRandomInitialPosition();

	// Create our snake
	_snake = Snake(position, position.computeAim(center));

	// Test if no other snakes are present near the position
	bool flag = false;
	std::list<Player*>::iterator it_player;
	for (it_player = getPlayers().begin(); it_player != getPlayers().end(); it_player++) {
		if (*it_player != this && (*it_player)->isPlaying()) {
			flag = _snake.getBody().checkIntersection((*it_player)->_snake.getBody(), 2*SNAKE_CIRCLE_RADIUS);	
			if (flag)
				break;
		}
	}
	if (flag)
		return generateRandomInitialPosition();
}

void Player::init() {
	// Generate initial position
	generateRandomInitialPosition();

	// Send Snake data
	processOutput();
}

void Player::run() {

	while (_is_running) {

		///////////////////////////////
		// AWAIT SERVER NOTIFICATION //
		///////////////////////////////

		std::unique_lock<std::mutex> lk_compute(m_compute);
		// std::cout << "Player waiting\n"; // THREAD DEBUGGING
		cv_compute.wait(lk_compute);
		play();

		//////////////////////////////
		// HANDLE INPUT COMPUTATION //
		//////////////////////////////

		processPlayerInput();

		///////////////////////////////////////
		// POSITIONS AND INTERSECTIONS AWAIT //
		///////////////////////////////////////

		computeIntersection();
		updatePlayerPosition();
		
		//////////////////////////////////////
		// SEND NEW DATA TO CLIENT IF HUMAN //
		//////////////////////////////////////

		processOutput();

		/////////////////////////
		// NOTIFY MAIN PROGRAM //
		/////////////////////////

		done_players_count++;
		if (done_players_count >= getPlayerPlayingCount()) { // IMPORTANT SO THAT NO USER CAN DODGE WITH DISCONNECTION
			// std::cout << "Player notifying\n"; // THREAD DEBUGGING
			cv_ready_compute.notify_one();
		}
	}
	_is_playing = false;
	addToPlayerPlayingCount(-1);
	std::cout << "PLAYERS PLAYING: " << getPlayerPlayingCount() << '\n';
}

		///////////////////////////
		// INTERSECTIONS COMPUTE //
		///////////////////////////

void Player::computeIntersection() {
	computePlayersIntersection();
	computeFoodsIntersection();
	computeMapIntersection();
}

void Player::computePlayersIntersection() {
	bool flag = false;
	std::list<Player*>::iterator it_player;
	for (it_player = getPlayers().begin(); it_player != getPlayers().end(); it_player++) {
		if (*it_player != this && (*it_player)->isRunning() && (*it_player)->isPlaying()) {
			flag = _snake.getBody().checkIntersection((*it_player)->_snake.getBody());	
			if (flag) {
				break;
			}
		}
	}
	if (flag) {
		_snake.die();
		_is_running = false;
	}
}

void Player::computeMapIntersection() {
	coordinates head_coordinates = _snake.getBody().getHead().getCoordinates();
	if (head_coordinates.x < 0 || head_coordinates.y < 0 || head_coordinates.x > GAME_SIZE_X * BACKGROUND_SIZE_X || head_coordinates.y > GAME_SIZE_Y * BACKGROUND_SIZE_Y) {
		_snake.die();
		_is_running = false;
	}
}

void Player::computeFoodsIntersection() {
	std::list<Food>::iterator it_food;
	std::list<Food> foods_array = getFoods();
	for (it_food = getFoods().begin(); it_food != getFoods().end();) {
		if (_snake.checkFoodIntersection(*it_food)) {
			_snake.addTail(1);
			getFoods().erase(it_food++);
			getFoods().push_back(Food(FoodPart::generateRandom(sf::Color::White)));
		} else {
			it_food++;
		}
	}
}

		////////////////
		// UPDATE ALL //
		////////////////

void Player::updatePlayerPosition() {
	_snake.updateAim(_input);
	_snake.interpolate(_input.speed);
}

void Player::play() {
	if (!_is_playing) {
		_is_playing = true;
		addToPlayerPlayingCount(1);
	}
}