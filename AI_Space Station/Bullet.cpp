#include "Bullet.h"



Bullet::Bullet(sf::Vector2f pos, std::string file, float r) : m_pos(pos), m_file(file)
{
	alive = true;
	loadSprite();
	setObjRotation(r);
	m_spr.setOrigin(m_spr.getGlobalBounds().width / 2, m_spr.getGlobalBounds().height / 2);
	myBox = sf::IntRect(pos.x, pos.y, m_spr.getGlobalBounds().width, m_spr.getGlobalBounds().height);
}


Bullet::~Bullet()
{

}

void Bullet::loadSprite()
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
void Bullet::update()
{
	m_pos = sf::Vector2f(m_pos.x + cos(m_spr.getRotation() * 3.14159265 / 180) * speed, m_pos.y + sin(m_spr.getRotation() * 3.14159265 / 180) * speed);
	m_spr.setPosition(m_pos);
	myBox = sf::IntRect(m_pos.x, m_pos.y, m_spr.getGlobalBounds().width, m_spr.getGlobalBounds().height);
	timeToLive(100);

}

void Bullet::render(sf::RenderWindow &w)
{
	w.draw(m_spr);
}
void Bullet::setObjRotation(float r)
{
	m_spr.setRotation(r);
}
void Bullet::timeToLive(int t)
{
	ttl++;
	if (ttl > t)
	{
		alive = false;
	}
}
sf::IntRect Bullet::getRect()
{
	return myBox;
}
void Bullet::collisionManager(std::vector<sf::IntRect> r)
{
	for (int i = 0; i < r.size(); i++)
	{
		if (r.at(i).intersects(myBox))
		{
			alive = false;
		}
	}
}