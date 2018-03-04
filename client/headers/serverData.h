#ifndef _Serverdata_H
#define _Serverdata_H

#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

struct Data
{
	std::vector<sf::Vector2f> my_snake_coord;
	std::vector<std::vector<sf::Vector2f> > snakes_coord_vector;
	std::vector<sf::Vector2f> food_vector;
};


// Overload operators

// Send and receive Vector2f types
sf::Packet& operator <<(sf::Packet& packet, sf::Vector2f vector)
{
    return packet << vector.x << vector.y;
}

sf::Packet& operator >>(sf::Packet& packet, sf::Vector2f& vector)
{
    return packet >> vector.x >> vector.y;
}

// Send and receive vector types
template <class T>
sf::Packet& operator <<(sf::Packet& packet, std::vector<T> vector)
{
	unsigned int temp = vector.size();
	packet << temp;
	for (unsigned int i = 0; i < vector.size(); i++) {
		packet << vector[i];
	}
    return packet;
}

template <class T>
sf::Packet& operator >>(sf::Packet& packet, std::vector<T>& vector)
{
    unsigned int size;
	packet >> size;
	for (unsigned int i = 0; i < size; i++) {
		T temp;
		packet >> temp;
		vector.push_back(temp);
	}
	return packet;
}

// Send and receive data struct
sf::Packet& operator <<(sf::Packet& packet, const Data& data)
{
    return packet << data.my_snake_coord << data.snakes_coord_vector << data.food_vector;
}

sf::Packet& operator >>(sf::Packet& packet, Data& data)
{
    return packet >> data.my_snake_coord >> data.snakes_coord_vector >> data.food_vector;
}

#endif // !_Serverdata_H