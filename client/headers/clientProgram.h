#ifndef PROGRAM_H
#define PROGRAM_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <list>
#include "controller.h"
#include "parameters.h"
#include "snake.h"
#include "food.h"
#include "serverData.h"
#include "clientCommunication.h"

class Program {

	public:
		void init ();
		void run ();

		friend void drawTexture(sf::RenderWindow &_window, const sf::Vector2f &origin, const sf::Texture &);

		friend void drawMinimap(sf::RenderWindow &window);

		friend void drawSnakeBodyMinimap(sf::RenderWindow &window, const SnakeBody &snake_body);
		
		Program ();
		~Program () {}

	private:
		bool _is_running;

		sf::RenderWindow _window;
		ClientCommunication _communication;

		bool _has_received_data;

		serverData _serverData;

		sf::Texture _texture;

		Controller _controller;


		Snake _snake;
		std::map<unsigned int, Snake> _snakes;
		std::list<Food> _foods;

		void update ();
		void disconnect();
		void display ();
		void handleEvents ();
		void getServerData();
		void sendClientInput();
};

#endif