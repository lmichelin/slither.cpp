#ifndef SNAKE_H_
#define SNAKE_H_

#include <string>
#include <iostream>
#include <deque>
namespace game {

	template <typename C>
	class Snake {
		public:
			// Get name
			string getName() {
				return _name;
			}

			std::deque<C> getCoordinatesArray() {
				return _coordinates_array;
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

			// Move the snake to a new batch of coordinates
			void move(C coordinates) {
				_coordinates_array.push_front(coordinates);
				_coordinates_array.pop_back();
			}

			void die() {
				_is_dead = true;
			}

			void print_coordinates() {
				std::cout << "Snake " << _name << " coordinates are: \n"
				for (it = g.begin(); it != g.end(); ++it) {
					cout << '\t' << *it;
				}
				cout << '\n';
			}

			// Constructors
			Snake() {
				std::deque<C> coordinates;
				_coordinates_array = coordinates;
				_length = 0;
				_is_dead = false;
			}

			Snake(std::deque<C> coordinates, int length) _coordinates_array(coordinates), _length(length), is_dead(false) {}


		private:
			// name
			string _name;

			// Coordinates
			std::deque<C> _coordinates_array;

			// Variable to check whether the snake is dead or not
			bool _is_dead;

			// Snake length
			int _length;
	};

};

#endif
