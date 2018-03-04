
// ////////////////////////////////////////////////////////////
// // Headers
// ////////////////////////////////////////////////////////////
// #include <SFML/Network.hpp>
// #include <iostream>
// #include <thread>

// ////////////////////////////////////////////////////////////
// /// Create a client, connect it to a server, display the
// /// welcome message and send an answer.
// ///
// ////////////////////////////////////////////////////////////
// void runTcpClient(unsigned short port)
// {
//     // Ask for the server address
//     sf::IpAddress server = "localhost";

//     // Create a socket for communicating with the server
//     sf::TcpSocket socket;

//     // Connect to the server
//     if (socket.connect(server, port) != sf::Socket::Done)
//         return;
//     std::cout << "Connected to server " << server << std::endl;

// 	for(int i = 0; i < 20; i++) {
// 		// Send an answer to the server
// 		sf::Packet packet;
// 		packet << 200;
// 		std::cout << "Sending ok\n";
// 		packet << i;
// 		if (socket.send(packet) != sf::Socket::Done) {
// 			std::cout << "ERROR\n";
// 			return;
// 		}

// 		std::this_thread::sleep_for(std::chrono::milliseconds(100));
// 	}

// 	sf::Packet packet;
// 	packet << 405;
// 	std::cout << "Disconnection sent\n";
// 	if (socket.send(packet) != sf::Socket::Done) {
// 		std::cout << "ERROR\n";
// 		return;
// 	}

// }


// ////////////////////////////////////////////////////////////
// /// Entry point of application
// ///
// /// \return Application exit code
// ///
// ////////////////////////////////////////////////////////////
// int main()
// {
//     // Choose an arbitrary port for opening sockets
//     const unsigned short port = 8001;

//     runTcpClient(port);

//     // Wait until the user presses 'enter' key
//     std::cout << "Press enter to exit..." << std::endl;
//     std::cin.ignore(10000, '\n');
//     std::cin.ignore(10000, '\n');

//     return EXIT_SUCCESS;
// }