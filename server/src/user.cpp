#include "user.h"
#include <iostream>

void User::run() {
	std::cout << "User with socket " << _socket->getRemoteAddress() << " now running" << std::endl;
}