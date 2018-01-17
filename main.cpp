#include <unistd.h>
#include <SFML/Graphics.hpp>

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "The IN204 Snake", sf::Style::Close);
	window.setVerticalSyncEnabled(true);
	sf::CircleShape shape(20.f);
	shape.setFillColor(sf::Color::Red);

	int x = 0;
	int y = 0;
	int speed = 2;

	while (window.isOpen())
	{

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			window.close();

			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Space) {
					speed = 4;
				}
				if (event.key.code == sf::Keyboard::Right) {
					x=1;
					y=0;
				}
				if (event.key.code == sf::Keyboard::Left) {
					x=-1;
					y=0;
				}
				if (event.key.code == sf::Keyboard::Up) {
					x=0;
					y=-1;
				}
				if (event.key.code == sf::Keyboard::Down) {
					x=0;
					y=1;
				}
			}
			if (event.type == sf::Event::KeyReleased) {
				if (event.key.code == sf::Keyboard::Space) {
					speed = 2;
				}
			}
		}

		shape.move(x * speed, y * speed);
		window.clear();
		window.draw(shape);
		window.display();
	}

	return 0;
}
