#include "Spawner.h"

Spawner::Spawner(sf::Vector2f pos, std::string file, int spawn) : m_pos(pos), 
m_file(file), MAX_SPAWN(spawn)
{
	loadSprite();
}

Spawner::~Spawner()
{
}
void Spawner::loadSprite()
{
	if (!m_texture.loadFromFile(m_file))
	{
		// simple error message if previous call fails
		std::cout << "problem loading logo" << std::endl;
	}
	m_spr.setTexture(m_texture);
	m_spr.setPosition(m_pos.x, m_pos.y);
	m_spr.setOrigin(m_spr.getGlobalBounds().height / 2, m_spr.getGlobalBounds().width / 2);
}
void Spawner::update(sf::Vector2f targetPos, sf::RenderWindow &w, sf::Time t, float rotation, sf::Vector2f v)
{
	rotationer();

	spawnTimer++;
	if(spawnTimer > 100)
	{
		spawn();
		shoot(m_pos);
		spawnTimer = 0;
	}
	for (int i = 0; i < predators.size(); i++)
	{
		predators.at(i)->update(w);
		predators.at(i)->updateMovement(targetPos, t, rotation, v);
	}
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets.at(i)->alive)
		{
			bullets.at(i)->update(w, targetPos, t, rotation);
		}
		else
		{
			delete bullets.at(i);
			bullets.erase(bullets.begin());
			bulletCount--;
		}
	}
}
void Spawner::spawn()
{
	if (spawnCount < MAX_SPAWN)
	{
		spawnCount++;
		predators.push_back(new Predator(sf::Vector2f(m_pos.x, m_pos.y), sf::Vector2f(1, 1), "assets/predator32.png", 2, 5, 4));
	}
}
void Spawner::render(sf::RenderWindow &w)
{
	w.draw(m_spr);
	for (int i = 0; i < predators.size(); i++)
	{
		predators.at(i)->render(w);
	}
	for (int i = 0; i < bullets.size(); i++)
	{
		bullets.at(i)->render(w);
	}
}
void Spawner::shoot(sf::Vector2f pos)
{
	if (bulletCount < MAX_BULLETS)
	{
		bulletCount++;
		bullets.push_back(new HomingMissiles(sf::Vector2f(m_pos.x, m_pos.y), "assets/hivebullet.png", m_spr.getRotation()));
		std::cout << "Fire" << std::endl;
	}
}
void Spawner::rotationer()
{
	rotationTimer++;
	if (rotationTimer > 20)
	{
		m_spr.setRotation(m_spr.getRotation() + 2);
	}
}