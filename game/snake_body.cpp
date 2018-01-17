#include "../parameters.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <vector>
#include "snake_body.h"

using namespace game;

int SnakeBody::getLength() {
	return _body.size();
}

void SnakeBody::addTail(int n) {
	for (int i = 0; i < n; i++) {
		_body.push_back(_body.back());
	}
}

void SnakeBody::interpolate() {

}

bool SnakeBody::checkIntersection(const Snake&) {

}
