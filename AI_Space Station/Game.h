#pragma once
#include <SFML\Graphics.hpp>

#include "Player.h"
#include "alien.h"
#include "Worker.h"
#include "Spawner.h"
#include "Sweeper.h"
#include "Grid.h"
#include "Radar.h"
#include "Shield.h"
#include "Graph.h"
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
	float speed = 0;
	float accel = 0.1f;
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
	Shield shield1;
	Shield shield2;
	Shield shield3;

	Graph * map;

};