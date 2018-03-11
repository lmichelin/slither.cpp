#include "AI.h"

void AI::processPlayerInput() {
	if (checkForMap()) {
		avoid();
	} else if (checkFoodAimAndDistance()) {
		deccelerate();
		goStraight();
	} else {
		search();
	}
}

void AI::rotateRight() {
	_input.rotating_left = false;
	_input.rotating_right = true;
}

void AI::rotateLeft() {
	_input.rotating_left = true;
	_input.rotating_right = false;
}

void AI::goStraight() {
	_input.rotating_left = false;
	_input.rotating_right = false;
}

void AI::accelerate() {
	_input.speed = HIGH_SPEED;
}

void AI::deccelerate() {
	_input.speed = LOW_SPEED;
}

bool AI::checkForMap() {
	coordinates aim = _snake.getAim();
	coordinates head = _snake.getBody().getHead().getCoordinates();
	if (head.x > BACKGROUND_SIZE_X * GAME_SIZE_X - 10 * SNAKE_CIRCLE_RADIUS && aim.x > 0) {
		return true;
	} else if (head.x < 10 * SNAKE_CIRCLE_RADIUS && aim.x < 0) {
		return true;
	} else if (head.y > BACKGROUND_SIZE_Y * GAME_SIZE_Y - 10 * SNAKE_CIRCLE_RADIUS && aim.y > 0) {
		return true;
	} else if (head.y < 10 * SNAKE_CIRCLE_RADIUS && aim.y < 0) {
		return true;
	}
	return false;
}

bool AI::checkFoodAimAndDistance() {
	SnakePart part = _snake.getBody().getHead();
	SnakePart aim(_snake.getAim());
	for (float t = 1; t < 11; t++) {
		part = part + aim * SNAKE_CIRCLE_RADIUS;
		std::list<Food>::iterator it_food;
		for (it_food = getFoods().begin(); it_food != getFoods().end(); it_food++) {
			if (part.checkIntersection(it_food->getPart())) {
				return true;
			}
		}
	}
	return false;
}

void AI::avoid() {
	if (!(_state == Avoiding)) {
		_state = Avoiding;
		randomTurn();
		accelerate();
	}
}

void AI::search() {
	// If this is the first search reset timer and start random turn for one second
	if (!(_state == Feeding)) {
		_time.reset();
		_state = Feeding;
		deccelerate();
		randomTurn();
		_is_turning = true;
	} else {
		_time.updateElapsedTime();
		// Check for time to take new decision
		if (_time.getElapsedTime().count() > 1000 && _is_turning) {
			goStraight();
			_is_turning = false;
			_time.reset();
		} else if (_time.getElapsedTime().count() > 1000 && !_is_turning) {
			randomTurn();
			_is_turning = true;
			_time.reset();
		}
	}
}

void AI::randomTurn() {
	if (rand() % 2)
		rotateLeft();
	else 
		rotateRight();
}

void AI::endGame() {
	_is_running = false;
}