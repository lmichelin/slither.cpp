#include <SFML/Network.hpp>
#include <iostream>

int main() {
	// ----- The client -----
	// Create a socket and connect it to 192.168.1.50 on port 55001
	sf::TcpSocket socket;
	socket.connect("192.168.1.50", 55001);
	// Send a message to the connected host
	std::string message = "Hi, I am a client";
	socket.send(message.c_str(), message.size() + 1);
	// Receive an answer from the server
	char buffer[1024];
	std::size_t received = 0;
	socket.receive(buffer, sizeof(buffer), received);
	std::cout << "The server said: " << buffer << std::endl;


	return 0;
}
