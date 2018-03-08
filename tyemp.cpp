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

// Send and receive vector types
sf::Packet& operator <<(sf::Packet& packet, std::vector<sf::Vector2f> vector)
{
	unsigned int temp = vector.size();
	packet << temp;
	for (unsigned int i = 0; i < vector.size(); i++) {
		packet << vector[i];
	}
    return packet;
}

sf::Packet& operator >>(sf::Packet& packet, std::vector<sf::Vector2f>& vector)
{
    unsigned int size;
	packet >> size;
	vector.reserve(size);
	for (unsigned int i = 0; i < size; i++) {
		sf::Vector2f temp;
		packet >> temp;
		vector.push_back(temp);
	}
	return packet;
}

// Send and receive data struct
sf::Packet& operator <<(sf::Packet& packet, data data)
{
    packet << data.my_snake.id << data.my_snake.coordinates;

	unsigned int snakes_length = data.snakes.size();
	packet << snakes_length;
	for (size_t i = 0; i < snakes_length; i++) {
		packet << data.snakes[i].id << data.snakes[i].coordinates;
	}

	packet << data.food_vector;

	return packet;
}

sf::Packet& operator >>(sf::Packet& packet, data& data)
{
	snake_data my_snake;
    packet >> my_snake.id >> my_snake.coordinates;
	std::cout << "ID: " << my_snake.id << "\n";
	data.my_snake = my_snake;

	unsigned int snakes_length;
	packet >> snakes_length;
	std::cout << "HELLLLLLLOOOOOO" << snakes_length << '\n';
	for (size_t i = 0; i < snakes_length; i++) {
		packet >> data.snakes[i].id >> data.snakes[i].coordinates;
	}

	packet >> data.food_vector;

	return packet;
}

void serverData::package(sf::Packet& packet) {
	packet << getData();
}

void serverData::extract(sf::Packet& packet) {
	data temp;
	packet >> temp;
	setData(temp);
}