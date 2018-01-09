#pragma once
#include <SFML\Graphics.hpp>

class Game {
public:
	
	Game();
	~Game();
	void run();

private:

	void update(sf::Time t);
	void render();

	void loadSprite();

	sf::RenderWindow m_window;

	sf::Texture m_text2; 
	sf::Texture m_text2;
	sf::Sprite m_spr1;
	sf::Sprite m_spr2;


};