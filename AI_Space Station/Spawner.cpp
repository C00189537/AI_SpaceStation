#include "Spawner.h"

Spawner::Spawner(sf::Vector2f pos, std::string file, int spawn) : m_pos(pos), 
m_file(file), MAX_SPAWN(spawn)
{
	loadSprite();
	myBox = sf::IntRect(pos.x, pos.y, m_spr.getGlobalBounds().width, m_spr.getGlobalBounds().height);
	alive = true;
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
	
	if (alive)
	{
		rotationer();
		spawnTimer++;
		if (spawnTimer > 100)
		{
			spawn();
			shoot(m_pos);
			spawnTimer = 0;
		}
	}
	for (int i = 0; i < predators.size(); i++)
	{
		if (predators.at(i)->alive)
		{
			predators.at(i)->update();
			predators.at(i)->updateMovement(targetPos, t, rotation, v);
		}
		else
		{
			delete predators.at(i);
			predators.erase(predators.begin() + i);
			spawnCount--;
		}
		
	}
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets.at(i)->alive)
		{
			bullets.at(i)->update(targetPos, t, rotation);
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
void Spawner::collisionManager(std::vector<sf::IntRect> r)
{
	for (int i = 0; i < r.size(); i++)
	{
		if (r.at(i).intersects(myBox))
		{
      		hp--;
		}
	}
	isAlive();
	for (int i = 0; i < predators.size(); i++)
	{
		predators.at(i)->collisionManager(r);
	}
	for (int i = 0; i < bullets.size(); i++)
	{
		bullets.at(i)->collisionManager(r);
	}
}
void Spawner::isAlive()
{
	if (hp <= 0)
	{
		alive = false;
	}
}
std::vector<sf::IntRect> Spawner::getRects()
{
	std::vector<sf::IntRect> temp;
	//Spawner hitbox
	temp.push_back(myBox);
	//homing missile hitbox
	for (int i = 0; i < bullets.size(); i++)
	{
		temp.push_back(bullets.at(i)->getRect());
	}
	//Predator + bullets hitboxes
	for (int i = 0; i < predators.size(); i++)
	{
		std::vector<sf::IntRect> holder = predators.at(i)->getRects();
		for (int j = 0; j < holder.size(); j++)
		{
			temp.push_back(holder.at(j));
		}
	}
	return temp;
}