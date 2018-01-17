#ifndef GAME_H_
#define GAME_H_

#include <vector>
#include "snake.h"

namespace game {
	template <typename C>
	class Game {
		public:
			std::vector<Snake<C>> getSnakes();

		private:
			std::vector<Snake<C>> _snakes;

	};


};

#endif