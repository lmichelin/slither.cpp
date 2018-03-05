#include "clientData.h"
#include "server.h"

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
sf::Packet& operator <<(sf::Packet& packet, const data& data)
{
    return packet << data.my_snake_coord << data.snakes_coord_vector << data.food_vector;
}

sf::Packet& operator >>(sf::Packet& packet, data& data)
{
    return packet >> data.my_snake_coord >> data.snakes_coord_vector >> data.food_vector;
}

void clientData::send(sf::TcpSocket& socket, int header, sf::Socket::Status& status) {
	sf::Packet packet;
	packet << header << getData();
	Server::send(socket, header, packet, status);
}

void clientData::receive(sf::TcpSocket& socket, int& header, sf::Socket::Status& status) {
	sf::Packet packet;
	status = socket.receive(packet);
	data data;
	packet >> header >> data;
	setData(data);
}