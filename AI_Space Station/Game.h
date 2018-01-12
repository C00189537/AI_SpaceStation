#pragma once
#include <SFML\Graphics.hpp>

#include "Player.h"
#include "alien.h"
#include "Worker.h"
#include "Spawner.h"
#include "Sweeper.h"
#include "Grid.h"
#include "Radar.h"
class Game {
public:
	
	Game();
	~Game();
	void run();

private:

	void update(sf::Time t);
	void render();
	double checkDistance(sf::Vector2f myPos, sf::Vector2f targetPos);
	//void processEvents();

	Player m_player;
	Grid grid;
	int speed = 0;
	int accel = 1;
	float rotato = 4.0f;
	sf::RenderWindow m_window;
	std::vector<Spawner*> spawners;
	void keyController();
	void CollisionManager();

	std::vector<Worker*> workers;
	sf::Vector2f workerSpawn[10];

	std::vector<Sweeper*> sweepers;

	sf::View camera;
	Radar radar;

};