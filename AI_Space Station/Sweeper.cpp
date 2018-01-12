#include "Sweeper.h"



Sweeper::Sweeper(sf::Vector2f pos, sf::Vector2f vel, std::string file, int s, float maxSpeed, int health) : alien(pos, vel, file, s, maxSpeed, health)
{
	m_spr.setOrigin(m_spr.getGlobalBounds().width / 2, m_spr.getGlobalBounds().height / 2);
	createBehaviour(s);
	loadSprite();
	alive = true;
}

Sweeper::~Sweeper()
{
}
void Sweeper::workerCollision(sf::IntRect r)
{
	if (r.intersects(myBox))
	{
		workerCount++;
	}
}
sf::IntRect Sweeper::getRect()
{
	return myBox;
}
int Sweeper::getWorkers()
{
	return workerCount;
}
sf::Vector2f Sweeper::getPos()
{
	return m_pos;
}
