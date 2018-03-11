/*
 * Data subclass for the server
*/

#ifndef _Serverdata_H
#define _Serverdata_H

#include <vector>
#include <SFML/Graphics.hpp>

#include "data.h"
#include "parts.h"

// Define the struct type data that will be sent and received between server and client
struct snake_data {
	// Id of the snake and player
	unsigned int id;
	// Coordinates and parts of the snake
	std::vector<SnakePart> parts;
};

sf::Packet& operator <<(sf::Packet& packet, snake_data data_snake);
sf::Packet& operator >>(sf::Packet& packet, snake_data& data_snake);

// Define the struct type data that will be sent and received between server and client
struct data {
	snake_data my_snake;
	std::vector<snake_data> snakes;
	std::vector<FoodPart> food_vector;
};

sf::Packet& operator <<(sf::Packet& packet, data data);
sf::Packet& operator >>(sf::Packet& packet, data& data);

class serverData: public networkData<data> {
	public:

		// Package and extract data in packets
		void package(sf::Packet& packet);
		void extract(sf::Packet& packet);

		/////////////////
		// Constructor //
		/////////////////

		serverData() {};
		~serverData() {};
};

#endif // !_Serverdata_H