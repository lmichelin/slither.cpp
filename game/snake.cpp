#include "snake.h"

int game::Snake::getX() {
	return _x;
}

int game::Snake::getY() {
	return _y;
}

int game::Snake::getLength() {
	return _length;
}

game::Snake::Snake() {
	_x = 0;
	_y = 0;
	_length = 0;
}

game::Snake::Snake(int x, int y, int length) {
	_x = x;
	_y = y,
	_length = length;
}