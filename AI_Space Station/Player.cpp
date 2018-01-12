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
	angle = 20;
	myBox = sf::IntRect(p.x, p.y, m_spr.getGlobalBounds().width, m_spr.getGlobalBounds().height);
	//std::cout << hp << std::endl;
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
void Player::update()
{
	angle = m_spr.getRotation();
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
	myBox = sf::IntRect(pos.x, pos.y, m_spr.getGlobalBounds().width, m_spr.getGlobalBounds().height);
	//std::cout << workerCount << std::endl;

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

void Player::setObjRotation(float r)
{
	m_spr.setRotation(m_spr.getRotation() + r);
}
sf::Vector2f Player::getVelocity()
{
	return m_velocity;
}
float Player::getRotation()
{
	return m_spr.getRotation();
}
void Player::shoot()
{
	if (currentBullets < MAX_BULLETS)
	{
		currentBullets++;
		bullets.push_back(new Bullet(sf::Vector2f(pos.x, pos.y), "assets/playerbullet.png", m_spr.getRotation()));
	}
}
std::vector<sf::IntRect> Player::getRects()
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
void Player::collisionManager(std::vector<sf::IntRect> r)
{
	for (int i = 0; i < r.size(); i++)
	{
		if (r.at(i).intersects(myBox))
		{
			hp--;
			std::cout << hp << std::endl;
		}
	}
	for (int i = 0; i < bullets.size(); i++)
	{
		bullets.at(i)->collisionManager(r);
	}
}
sf::IntRect Player::getRect()
{
	return myBox;
}
void Player::collectWorkers(sf::IntRect target)
{
	if (target.intersects(myBox))
	{
		workerCount++;
	}
}
void Player::addWorker(int w)
{
	workerCount += w;
}