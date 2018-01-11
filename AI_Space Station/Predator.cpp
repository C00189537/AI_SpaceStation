#include "Predator.h"

Predator::Predator(sf::Vector2f pos, sf::Vector2f vel, std::string file, int s, float maxSpeed, int health): alien(pos, vel, file, s, maxSpeed, health)
{
	m_spr.setOrigin(m_spr.getGlobalBounds().width / 2, m_spr.getGlobalBounds().height / 2);
	createBehaviour(s);
	loadSprite();
	alive = true;
}

Predator::~Predator()
{
}
void Predator::shoot()
{
	gunTimer++;
	if (gunTimer > 50)
	{
		if (currentBullets < MAX_BULLETS)
		{
			currentBullets++;
			bullets.push_back(new Bullet(sf::Vector2f(m_pos.x, m_pos.y), "assets/predatorbullet.png", m_spr.getRotation()));
		}
		gunTimer = 0;
	}
}
void Predator::update()
{
	shoot();
	isAlive();
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets.at(i)->alive)
		{
			bullets.at(i)->update();
		}
		else
		{
			delete bullets.at(i);
			bullets.erase(bullets.begin() + i);
			currentBullets--;
		}
	}
	m_spr.setPosition(m_pos);
	myBox = sf::IntRect(m_pos.x, m_pos.y, m_spr.getGlobalBounds().width, m_spr.getGlobalBounds().height);
}
void Predator::render(sf::RenderWindow &w)
{
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets.at(i)->alive)
		{
			bullets.at(i)->render(w);
		}
	}
	w.draw(m_spr);
}
std::vector<sf::IntRect> Predator::getRects()
{
	std::vector<sf::IntRect> temp;

	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets.at(i)->alive)
		{
			temp.push_back(bullets.at(i)->getRect());
		}
	}
	temp.push_back(myBox);
	return temp;
}
void Predator::collisionManager(std::vector<sf::IntRect> r)
{
	for (int i = 0; i < r.size(); i++)
	{
		boundaryBullet(r.at(i));
	}
	for (int i = 0; i < bullets.size(); i++)
	{
		bullets.at(i)->collisionManager(r);
	}
}