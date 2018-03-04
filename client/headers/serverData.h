#ifndef _Serverdata_H
#define _Serverdata_H

#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

class Data {
	public:
		std::vector<sf::Vector2f> my_snake_coord;
		std::vector<std::vector<sf::Vector2f> > snakes_coord_vector;
		std::vector<sf::Vector2f> food_vector;

		// Send and receive data struct
		friend sf::Packet& operator <<(sf::Packet& packet, const Data& data);
		friend sf::Packet& operator >>(sf::Packet& packet, Data& data);

		Data() {}
		~Data() {}
};

#endif // !_Serverdata_H