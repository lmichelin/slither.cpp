#ifndef SNAKE_H_
#define SNAKE_H_

#include <string>
#include <iostream>
namespace game {

	class Snake {
		public:
			// Get name
			std::string getName() {
				return _name;
			}

			bool checkIfDead() {
				return _is_dead;
			}

			// Get length
			int getLength() {
				return length;
			}

			// Add length can only be added by 1
			void addLength() {
				// TODO
				_length += 1;
			}

			void die() {
				_is_dead = true;
			}

			// Constructors
			Snake() {
				_length = 0;
				_is_dead = false;
			}

			Snake(int length) _length(length), is_dead(false) {}


		private:
			// name
			std::string _name;

			// Variable to check whether the snake is dead or not
			bool _is_dead;

			// Snake length
			int _length;
	};

};

#endif