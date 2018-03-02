#include "user.h"
#include <iostream>

void User::run() {
	std::cout << "User with socket " << _socket->getRemoteAddress() << " now running" << std::endl;
	while (_is_connected) {
		std::unique_lock<std::mutex> lk(m);
		cv_positions.wait(lk);

		std::cout << "POSITION\n";
	}
}