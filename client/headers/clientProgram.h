#ifndef PROGRAM_H
#define PROGRAM_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <list>
#include "controller.h"
#include "parameters.h"
#include "snake.h"
#include "food.h"
#include "clientCommunication.h"

class Program {
	private:
		bool _is_running;

		sf::RenderWindow _window;

		sf::Texture _texture;

		Controller _controller;

		ClientCommunication _communication;

		Snake _snake;
		std::vector<Snake> _snakes;
		std::list<Food> _foods;

		void update ();
		void disconnect();
		void display ();
		void handleEvents ();
		void getServerData();
	public:
		void init ();
		void run ();

		friend void drawTexture(sf::RenderWindow &window, const sf::Vector2f &origin, const sf::Texture &);

		friend void drawMinimap(sf::RenderWindow &window);

		friend void drawSnakeBodyMinimap(sf::RenderWindow &window, const SnakeBody &snake_body);

		Program ();
		~Program () {}
};

#endif