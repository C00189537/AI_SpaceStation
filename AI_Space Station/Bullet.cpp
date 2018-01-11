#include "Bullet.h"



Bullet::Bullet(sf::Vector2f pos, std::string file, float r) : m_pos(pos), m_file(file)
{
	alive = true;
	loadSprite();
	setObjRotation(r);
	m_spr.setOrigin(m_spr.getGlobalBounds().width / 2, m_spr.getGlobalBounds().height / 2);
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
void Bullet::update(sf::RenderWindow &w)
{
	boundary(w);
	m_pos = sf::Vector2f(m_pos.x + cos(m_spr.getRotation() * 3.14159265 / 180) * speed, m_pos.y + sin(m_spr.getRotation() * 3.14159265 / 180) * speed);
	m_spr.setPosition(m_pos);
	timeToLive(100);

}

void Bullet::render(sf::RenderWindow &w)
{
	w.draw(m_spr);
}
void Bullet::boundary(sf::RenderWindow &w)
{
	if (m_spr.getPosition().x > w.getSize().x || m_spr.getPosition().y > w.getSize().y 
		|| m_spr.getPosition().x + m_spr.getGlobalBounds().width < 0 
		|| m_spr.getPosition().y + m_spr.getGlobalBounds().height < 0)
	{
		
	}
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
