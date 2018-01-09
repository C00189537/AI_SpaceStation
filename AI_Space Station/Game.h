#pragma once
#include <SFML\Graphics.hpp>
#include "Player.h"
#include "alien.h"


class Game {
public:
	
	Game();
	~Game();
	void run();

private:

	void update(sf::Time t);
	void render();
	//void processEvents();

	Player m_player;
	int speed = 0;
	int accel = 1;
	float rotato = 5.0f;
	sf::RenderWindow m_window;




};