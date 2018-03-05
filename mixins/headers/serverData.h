#ifndef _Serverdata_H
#define _Serverdata_H

#include <vector>
#include <SFML/Graphics.hpp>
#include "data.h"

struct data {
	std::vector<sf::Vector2f> my_snake_coord;
	std::vector<std::vector<sf::Vector2f> > snakes_coord_vector;
	std::vector<sf::Vector2f> food_vector;
};

class serverData: public networkData<data> {
	public:
		void package(sf::Packet& packet);
		void extract(sf::Packet& packet);

		// Send and receive data struct
		friend sf::Packet& operator <<(sf::Packet& packet, const data& data);
		friend sf::Packet& operator >>(sf::Packet& packet, data& data);

		serverData() {};
		~serverData() {};
};

#endif // !_Serverdata_H