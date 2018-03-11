#ifndef STATE_H
#define STATE_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <list>
#include "controller.h"
#include "parameters.h"
#include "snake.h"
#include "food.h"
#include "serverData.h"
#include "clientCommunication.h"

class State {
	public:

		//////////////////
		// Main Methods //
		//////////////////

		virtual void init() =0;
		virtual void quit() =0;
		virtual void getServerData() =0;
		virtual void handleEvents() =0;
		virtual void update() =0;
		virtual void sendClientInput() =0;
		virtual void display() =0;


		/////////////
		// Getters //
		/////////////

		static std::string getNextState() {
			return _next_state;
		}

		static std::string getMessage() {
			return _message;
		}

		static void setNextState(std::string state, std::string message="") {
			_next_state = state;
			_message = message;
		}

		

		/////////////////
		// Constructor //
		/////////////////

		State(sf::RenderWindow* window, ClientCommunication* communication): _window(window), _communication(communication) {}
		~State() {}

	protected:

		// Client window 
		sf::RenderWindow* _window;

		// Communication module
		ClientCommunication* _communication;

	private:
		static std::string _next_state;
		static std::string _message;
};

class HomeState : public State
{
public:
	void init();
	void quit();

	friend void drawTexture(sf::RenderWindow* _window, const sf::Vector2f &origin, const sf::Texture &);

	friend void drawHomeMessage(sf::RenderWindow* _window, const sf::Font& _font, std::string message);

	void getServerData();
	void handleEvents();
	void update();
	void sendClientInput();
	void display();

	HomeState(sf::RenderWindow* window, ClientCommunication* communication) : State(window, communication) {}
	~HomeState() {}

private:
	sf::Texture _texture;

	sf::Font _font;	
	
};

class GameState : public State
{
public:
	void init();
	void quit();

	friend void drawTexture(sf::RenderWindow* _window, const sf::Vector2f &origin, const sf::Texture &);

	friend void drawMinimap(sf::RenderWindow* window);

	friend void drawSnakeBodyMinimap(sf::RenderWindow* window, const SnakeBody &snake_body, bool is_my_snake);

	friend void drawCurrentScore(sf::RenderWindow* window, const sf::Font& _font, int score);	

	void getServerData();
	void handleEvents();
	void update();
	void sendClientInput();
	void display();

	GameState(sf::RenderWindow* window, ClientCommunication* communication) : State(window, communication), _has_received_data(false) {}
	~GameState() {}

private:
	bool _has_received_data;

	serverData _serverData;

	sf::Font _font;

	sf::Texture _texture;

	Controller _controller;


	Snake _snake;
	std::map<unsigned int, Snake> _snakes;
	std::list<Food> _foods;
};

#endif // !STATE_H