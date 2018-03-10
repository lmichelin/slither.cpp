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

class State
{
public:
	virtual void init() =0;
	virtual void quit() =0;

	static std::string getNextState() {
		return _next_state;
	}

	static void setNextState(std::string state) {
		_next_state = state;
	}
	
	virtual void getServerData() =0;
	virtual void handleEvents() =0;
	virtual void update() =0;
	virtual void sendClientInput() =0;
	virtual void display() =0;

	State(sf::RenderWindow* window, ClientCommunication* communication): _window(window), _communication(communication) {}
	~State() {}

protected:
	sf::RenderWindow* _window;
	ClientCommunication* _communication;

private:
	static std::string _next_state;
};

class HomeState : public State
{
public:
	void init();
	void quit();

	friend void drawTexture(sf::RenderWindow* _window, const sf::Vector2f &origin, const sf::Texture &);

	void getServerData();
	void handleEvents();
	void update();
	void sendClientInput();
	void display();

	HomeState(sf::RenderWindow* window, ClientCommunication* communication) : State(window, communication) {}
	~HomeState() {}

private:
	sf::Texture _texture;
	
};

class GameState : public State
{
public:
	void init();
	void quit();

	friend void drawTexture(sf::RenderWindow* _window, const sf::Vector2f &origin, const sf::Texture &);

	friend void drawMinimap(sf::RenderWindow* window);

	friend void drawSnakeBodyMinimap(sf::RenderWindow* window, const SnakeBody &snake_body);

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

	sf::Texture _texture;

	Controller _controller;


	Snake _snake;
	std::map<unsigned int, Snake> _snakes;
	std::list<Food> _foods;
};

#endif // !STATE_H