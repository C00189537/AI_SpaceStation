#include "Player.h"


Player::Player()
{

}
Player::~Player()
{

}
void Player::create(sf::Vector2f p, sf::Vector2f vel, std::string file)
{
	pos = p;
	m_velocity = vel;
	m_file = file;
	loadSprite();
	m_spr.setOrigin(m_spr.getGlobalBounds().width / 2, m_spr.getGlobalBounds().height / 2);
}
void Player::loadSprite()
{
	if (!m_texture.loadFromFile(m_file))
	{
		// simple error message if previous call fails
		std::cout << "problem loading logo" << std::endl;
	}
	m_spr.setTexture(m_texture);
	m_spr.setPosition(pos.x, pos.y);
}
void Player::update(sf::RenderWindow &w)
{
	boundary(w);
	angle = m_spr.getRotation();
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets.at(i)->alive)
		{
			bullets.at(i)->update(w);
		}
		else
		{
			delete bullets.at(i);
			bullets.erase(bullets.begin());
			currentBullets--;
		}
	}

}
void Player::updateVelocity(int v)
{
	pos = sf::Vector2f(pos.x + cos(m_spr.getRotation() * 3.14159265 / 180) * v, pos.y + sin(m_spr.getRotation() * 3.14159265 / 180) * v);
	m_spr.setPosition(pos);
}
void Player::render(sf::RenderWindow &w)
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
void Player::boundary(sf::RenderWindow &w)
{
	if (m_spr.getPosition().x > w.getSize().x)
	{
		pos.x = 0 -m_spr.getGlobalBounds().width;
	}
	else if (m_spr.getPosition().y > w.getSize().y)
	{
		pos.y = 0 - m_spr.getGlobalBounds().height;
	}
	else if (m_spr.getPosition().x + m_spr.getGlobalBounds().width < 0)
	{
		pos.x = w.getSize().x;
	}
	else if (m_spr.getPosition().y + m_spr.getGlobalBounds().height < 0)
	{
		pos.y = w.getSize().y;
	}

	m_spr.setPosition(pos);
}
void Player::setObjRotation(float r)
{
	m_spr.setRotation(m_spr.getRotation() + r);
}
sf::Vector2f Player::getVelocity()
{
	return m_velocity;
}
void Player::shoot()
{
	if (currentBullets < MAX_BULLETS)
	{
		currentBullets++;
		bullets.push_back(new Bullet(sf::Vector2f(pos.x, pos.y), "assets/playerbullet.png", m_spr.getRotation()));
		std::cout << "Fire" << std::endl;
	}
}