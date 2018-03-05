#include "input.h"
#include "server.h"

sf::Packet& operator <<(sf::Packet& packet, const input& input) {
    return packet << input.speed << input.rotating_right << input.rotating_left;
}

sf::Packet& operator >>(sf::Packet& packet, input& input) {
    return packet >> input.speed >> input.rotating_right >> input.rotating_left;
}

void clientInput::send(sf::TcpSocket& socket, int header, sf::Socket::Status& status) {
	sf::Packet packet;
	packet << header << getData();
	Server::send(socket, header, packet, status);
}

void clientInput::receive(sf::TcpSocket& socket, int& header, sf::Socket::Status& status) {
	sf::Packet packet;
	status = socket.receive(packet);
	input input;
	packet >> header >> input;
	setData(input);
}