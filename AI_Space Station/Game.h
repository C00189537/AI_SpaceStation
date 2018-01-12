#pragma once
#include <SFML\Graphics.hpp>

#include "Player.h"
#include "alien.h"
#include "Spawner.h"
#include "Grid.h"
#include "Radar.h"
#include "Shield.h"
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
	Grid grid;
	float speed = 0;
	float accel = 0.1f;
	float rotato = 4.0f;
	sf::RenderWindow m_window;
	std::vector<Spawner*> spawners;
	void keyController();
	void CollisionManager();

	sf::View camera;
	Radar radar;
	Shield shield1;
	Shield shield2;
	Shield shield3;

};