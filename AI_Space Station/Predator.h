#pragma once
#include "alien.h"
#include "Bullet.h"
class Predator :
	public alien
{
public:
	Predator(sf::Vector2f pos, sf::Vector2f vel, std::string file, int s, float maxSpeed, int health);
	~Predator();
	void shoot();
	void update(sf::RenderWindow &w);
	void render(sf::RenderWindow &w);
private:
	std::vector<Bullet*> bullets;
	int MAX_BULLETS = 5;
	int currentBullets = 0;
	int gunTimer = 0;
};

