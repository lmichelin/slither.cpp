#ifndef PROGRAM_H
#define PROGRAM_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <list>
#include "controller.h"
#include "parameters.h"
#include "snake.h"
#include "food.h"
#include "communication.h"

class Program {
	private:
		bool _is_running;

		sf::RenderWindow _window;

		unsigned int _window_height;
		unsigned int _window_width;
		sf::Vector2f _window_center;

		sf::Texture _texture;

		Controller _controller;

		Communication _communication;

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

		void drawTexture(sf::RenderWindow &_window, const sf::Vector2f &origin, const sf::Vector2f &center, const sf::Texture &);

		Program ();
		~Program () {}
};

#endif