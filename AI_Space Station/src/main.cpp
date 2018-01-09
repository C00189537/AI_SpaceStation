#include <SFML\Graphics.hpp>
#include <iostream>

int main(int argc, char* argv[])
{
	sf::RenderWindow w(sf::VideoMode(800, 600), "SFML window");
	w.setFramerateLimit(60);

	while (w.isOpen())
	{
		// Event processing
		sf::Event event;
		while (w.pollEvent(event))
		{
			// Request for closing the window
			if (event.type == sf::Event::Closed)
				w.close();
		}
	}

	w.clear(sf::Color::White);
	w.display();

	system("PAUSE");

	return 0;
}