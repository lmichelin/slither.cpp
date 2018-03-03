#include "user.h"
#include <iostream>

void User::run() {
	std::cout << "User with socket " << _socket->getRemoteAddress() << " now running" << std::endl;

	while (_is_connected) {

		/////////////////////
		// POSITIONS AWAIT //
		/////////////////////

		std::unique_lock<std::mutex> lk_positions(m_positions);
		play();
		cv_positions.wait(lk_positions);

		std::cout << "POSITION\n";

		
		done_users_count++;
		if (done_users_count == _user_playing_count){
			cv_ready_positions.notify_one();
		}

		/////////////////////////
		// INTERSECTIONS AWAIT //
		/////////////////////////

		std::unique_lock<std::mutex> lk_intersections(m_intersections);
		cv_intersections.wait(lk_intersections);

		std::cout << "INTERSECTION\n";
		
		done_users_count++;
		if (done_users_count == _user_playing_count){
			cv_ready_intersections.notify_one();
		}
	}
}