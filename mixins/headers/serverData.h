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

class clientData: public networkData<data> {
	public:
		void send(sf::TcpSocket& socket, int header, sf::Socket::Status& status);
		void receive(sf::TcpSocket& socket, int& header, sf::Socket::Status& status);

		// Send and receive data struct
		friend sf::Packet& operator <<(sf::Packet& packet, const data& data);
		friend sf::Packet& operator >>(sf::Packet& packet, data& data);

		clientData() {};
		~clientData() {};
};

#endif // !_Serverdata_H