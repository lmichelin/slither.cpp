#include "user.h"
#include "serverData.h"
#include "input.h"
#include <iostream>
#include <list>
#include <cmath>

void User::init() {
	// Generate initial position
	generateRandomInitialPosition();

	// Send Snake data
	processOutput();
}

void User::run() {
	std::cout << "User with socket " << _communication.getRemoteAddress() << " now running + ID " << _id << " + Port: " << _communication.getSocket().getRemotePort() << std::endl;

	while (_is_connected) {

		///////////////////////////////
		// AWAIT SERVER NOTIFICATION //
		///////////////////////////////

		std::unique_lock<std::mutex> lk_compute(m_compute);
		// std::cout << "User waiting\n"; // THREAD DEBUGGING
		cv_compute.wait(lk_compute);
		play();

		/////////////////////////////
		// HANDLE SOCKET RECEPTION //
		/////////////////////////////

		processClientInput();

		///////////////////////////////////////
		// POSITIONS AND INTERSECTIONS AWAIT //
		///////////////////////////////////////

		computeIntersection();
		updateUserPosition();
		
		/////////////////////////////
		// SEND NEW DATA TO CLIENT //
		/////////////////////////////

		processOutput();

		/////////////////////////
		// NOTIFY MAIN PROGRAM //
		/////////////////////////

		done_users_count++;
		if (done_users_count >= getUserPlayingCount()) { // IMPORTANT SO THAT NO USER CAN DODGE WITH DISCONNECTION
			// std::cout << "User notifying\n"; // THREAD DEBUGGING
			cv_ready_compute.notify_one();
		}
	}
	std::cout << "Not playing anymore\n";
	_communication.disconnect();
	_is_playing = false;
	addToUserPlayingCount(-1);
}

void User::computeIntersection() {
	computeUsersIntersection();
	computeFoodsIntersection();
}

void User::computeUsersIntersection() {
	bool flag = false;
	std::list<User>::iterator it_user;
	for (it_user = getUsers().begin(); it_user != getUsers().end(); it_user++) {
		if (&(*(it_user)) != this && it_user->isConnected() && it_user->isPlaying()) {
			flag = _snake.getBody().checkIntersection(it_user->_snake.getBody());	
			if (flag) {
				break;
			}
		}
	}
	if (flag) {
		_snake.die();
		_is_connected = false;
	}
}

void User::computeFoodsIntersection() {
	std::list<Food>::iterator it_food;
	std::list<Food> foods_array = getFoods();
	for (it_food = getFoods().begin(); it_food != getFoods().end();) {
		if (_snake.checkFoodIntersection(*it_food)) {
			_snake.addTail(1);
			getFoods().erase(it_food++);
		} else {
			it_food++;
		}
	}
}

void User::processClientInput() {
	sf::Packet input_packet;
	sf::Socket::Status status;
	int header;
	_communication.receivePacket(header, input_packet, status);

	if (status == sf::Socket::Done) {
		_elapsed_disconnect_time = std::chrono::milliseconds::zero();

		switch (header) {
		
		case OK:
			_input.extract(input_packet);
			_has_received_data = true;	
			break;
		
		case DISCONNECT:
			_is_connected = false;
			break;
		
		default:
			break;
		}
	} else if (status == sf::Socket::Disconnected || (status == sf::Socket::NotReady && _is_playing)) {
		if (_elapsed_disconnect_time == std::chrono::milliseconds::zero()) {
			_elapsed_disconnect_time = ms(10);
			_disconnect_time = Time::now();
		} else {
			fsec fs = Time::now() - _disconnect_time;
			_elapsed_disconnect_time = std::chrono::duration_cast<ms>(fs);
			std::cout << "Elapsed time: " << _elapsed_disconnect_time.count() << "\n";

			if (_elapsed_disconnect_time.count() > INACTIVITY_TIMEOUT)
			{
				_is_connected = false;
				std::cout << "The client has disconnected\n";
			}
		}
	}
}

void User::generateRandomInitialPosition() {

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
	std::list<User>::iterator it_user;
	for (it_user = getUsers().begin(); it_user != getUsers().end(); it_user++) {
		if (&(*(it_user)) != this && it_user->isConnected() && it_user->isPlaying()) {
			flag = _snake.getBody().checkIntersection(it_user->_snake.getBody(), 2*SNAKE_CIRCLE_RADIUS);	
			if (flag)
				break;
		}
	}
	if (flag) {
		return generateRandomInitialPosition();
	}
}

void User::updateUserPosition() {
	_snake.updateAim(_input.getData());
	_snake.interpolate(getSpeed());
}

void User::processOutput() {
	if (_has_received_data) {
		packageServerData();
		_communication.send(OK, _serverData.getData());
		_has_received_data = false;
	}
}

void User::packageServerData() {
	data send_data;

	snake_data my_snake;
	my_snake.id = _id;
	my_snake.parts = _snake.getBody().getParts();

	send_data.my_snake = my_snake;

	std::list<User>::iterator it_user;
	for (it_user = getUsers().begin(); it_user != getUsers().end(); it_user++) {
		if (&(*it_user) != this && it_user->isConnected() && it_user->isPlaying()) {
			snake_data snake_element;
			snake_element.id = it_user->getId();
			snake_element.parts = it_user->getSnake().getBody().getParts();
			send_data.snakes.push_back(snake_element);	
		}
	}

	// TODO ADD FOODS
	std::list<Food>::iterator it_food;
	for (it_food = getFoods().begin(); it_food != getFoods().end(); it_food++) {
		send_data.food_vector.push_back(it_food->getPart());
	}

	// Package
	_serverData.setData(send_data);
}

