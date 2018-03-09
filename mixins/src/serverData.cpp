#include "serverData.h"
#include <iostream> //DEBUG

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

// Send and receive Color types
sf::Packet& operator <<(sf::Packet& packet, sf::Color color)
{
    return packet << color.r << color.g << color.b << color.a;
}

sf::Packet& operator >>(sf::Packet& packet, sf::Color& color)
{
    return packet >> color.r >> color.g >> color.b >> color.a;
}

// Send and receive ShapePart types
sf::Packet& operator <<(sf::Packet& packet, ShapePart part)
{
    return packet << part.getCoordinates() << part.getColor() << part.getRadius();
}

sf::Packet& operator >>(sf::Packet& packet, ShapePart& part)
{
	sf::Vector2f coordinates;
	sf::Color color;
	float radius;
    packet >> coordinates >> color >> radius;
	part.setColor(color);
	part.setCoordinates(coordinates);
	part.setRadius(radius);
	return packet;
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

// Send and receive snake_data struct
sf::Packet& operator <<(sf::Packet& packet, snake_data data_snake)
{
    return packet << data_snake.id << data_snake.parts;
}

sf::Packet& operator >>(sf::Packet& packet, snake_data& data_snake)
{
    return packet >> data_snake.id >> data_snake.parts;
}

// Send and receive data struct
sf::Packet& operator <<(sf::Packet& packet, data data)
{
    return packet << data.my_snake << data.snakes << data.food_vector;
}

sf::Packet& operator >>(sf::Packet& packet, data& data)
{
    return packet >> data.my_snake >> data.snakes >> data.food_vector;
}

void serverData::package(sf::Packet& packet) {
	packet << getData();
}

void serverData::extract(sf::Packet& packet) {
	data temp;
	packet >> temp;
	setData(temp);
}