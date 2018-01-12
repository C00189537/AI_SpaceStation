#pragma once
#include "alien.h"
class Sweeper :
	public alien
{
public:
	Sweeper(sf::Vector2f pos, sf::Vector2f vel, std::string file, int s, float maxSpeed, int health);
	~Sweeper();
	int workerCount = 0;
	void workerCollision(sf::IntRect r);
	sf::IntRect getRect();
	int getWorkers();
	sf::Vector2f getPos();
};

