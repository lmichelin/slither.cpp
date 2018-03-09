#ifndef _Serverdata_H
#define _Serverdata_H

#include <vector>
#include <SFML/Graphics.hpp>
#include "data.h"
#include "parts.h"


struct snake_data {
	unsigned int id;
	std::vector<SnakePart> parts;
};

sf::Packet& operator <<(sf::Packet& packet, snake_data data_snake);
sf::Packet& operator >>(sf::Packet& packet, snake_data& data_snake);

struct data {
	snake_data my_snake;
	std::vector<snake_data> snakes;
	std::vector<FoodPart> food_vector;
};

sf::Packet& operator <<(sf::Packet& packet, data data);
sf::Packet& operator >>(sf::Packet& packet, data& data);

class serverData: public networkData<data> {
	public:
		void package(sf::Packet& packet);
		void extract(sf::Packet& packet);

		serverData() {};
		~serverData() {};
};

#endif // !_Serverdata_H