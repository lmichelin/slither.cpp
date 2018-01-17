

#ifndef SNAKE_H_
#define SNAKE_H_

namespace game {

	template <typename T>
	class Snake {
		public:

			// Get Coordinates
			int getX();
			int getY();

			// Get length
			int getLength();

			// Move the snake to given coordinates
			void move(int x, int y);

			// Constructors
			Snake();
			Snake(int x, int y, int length);


		private:
			// Coordinates
			int _x;
			int _y;

			// Snake length
			int _length;
	};
};

#endif