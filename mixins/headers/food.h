/*
 * Class to define the in game foods
*/ 

#ifndef FOOD_H_
#define FOOD_H_

#include <SFML/Graphics.hpp>

#include "parts.h"

class Food {
	public:

		/////////////////
		//   Getters   //
		/////////////////

		FoodPart getPart() const {
			return _part;
		}

		/////////////////
		// Constructor //
		/////////////////

		Food(FoodPart part) : _part(part) {}

	private:
		FoodPart _part;
};

#endif
