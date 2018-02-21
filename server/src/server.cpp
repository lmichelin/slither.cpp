#include <SFML/Network.hpp>
#include <iostream>




int main(int argc, char const *argv[]) {
	// ----- The server -----
	// Create a listener to wait for incoming connections on port 55001
	sf::TcpListener listener;
	listener.listen(8001);
	// Wait for a connection
	sf::TcpSocket socket;
	for (;;) {
		listener.accept(socket);
		bool exit = false;
		std::cout << "New client connected: " << socket.getRemoteAddress() << ':' << socket.getRemotePort() << std::endl;
		
		while (!exit) {
		// Receive a message from the client
		sf::Packet packet;
		if (socket.receive(packet) != sf::Socket::Done) {
			printf("it does not work work\n");
			exit = true;
		}
		int x;
		int y;
		bool left;
		bool right;
		if (packet >> x)
		{
			printf("It works you damn son of a bitch !!!!!\n");
		}
		else
		{
			printf("sucker ...\n");
		}
		packet >> x >> y >> left >> right;
		std::cout << x << y << left << right << std::endl;

		}
	}
	socket.disconnect();
	return 0;
}
