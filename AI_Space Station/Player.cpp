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
	angle = 20;
	myBox = sf::IntRect(p.x, p.y, m_spr.getGlobalBounds().width, m_spr.getGlobalBounds().height);
	healthMeter.setFillColor(sf::Color(0,255,0,180));
	healthMeter.setSize(sf::Vector2f(60, 8));
	std::cout << hp << std::endl;

}
void Player::loadSprite()
{
	if (!m_texture.loadFromFile(m_file))
	{
		// simple error message if previous call fails
		std::cout << "problem loading logo" << std::endl;
	}
	m_spr.setTexture(m_texture);
	m_spr.setOrigin(m_spr.getGlobalBounds().width / 2, m_spr.getGlobalBounds().height / 2);
	m_spr.setPosition(pos.x, pos.y);
	if (!m_shieldTexture.loadFromFile("assets/Shield.png"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading logo" << std::endl;
	}
	m_shieldSpr.setTexture(m_shieldTexture);
	m_shieldSpr.setOrigin(m_shieldSpr.getGlobalBounds().width / 2, m_shieldSpr.getGlobalBounds().height / 2);
	m_shieldSpr.setPosition(pos.x, pos.y);
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

}
void Player::updateVelocity(float v)
{
	pos = sf::Vector2f(pos.x + cos(m_spr.getRotation() * 3.14159265 / 180) * v, pos.y + sin(m_spr.getRotation() * 3.14159265 / 180) * v);
	m_spr.setPosition(pos);
	m_shieldSpr.setPosition(pos);
	healthMeter.setPosition(sf::Vector2f(pos.x - 32, pos.y + 16));
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
	if (shieldApplied)
	{
		w.draw(m_shieldSpr);
	}
	w.draw(healthMeter);
}
void Player::boundary(sf::RenderWindow &w)
{
	if (m_spr.getPosition().x > 1280 - 64)
	{
		pos.x = 0;
	}
	else if (m_spr.getPosition().y > 1280 - 64)
	{
		pos.y = 0;
	}
	else if (m_spr.getPosition().x + m_spr.getGlobalBounds().width / 2 < 0)
	{
		pos.x = 1280 - 64;
	}
	else if (m_spr.getPosition().y + m_spr.getGlobalBounds().height / 2 < 0)
	{
		pos.y = 1280 - 64;
	}
}
void Player::setObjRotation(float r)
{
	m_spr.setRotation(m_spr.getRotation() + r);
	m_shieldSpr.setRotation(m_shieldSpr.getRotation() + r);
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
			if (shieldApplied)
			{
				shieldApplied = false;
				healthMeter.setFillColor(sf::Color(0, 255, 0, 180));
			}
			else
			{
				hp--;
				if (hp < 0)
					hp = 0;
				healthMeter.setSize(sf::Vector2f(10 * hp, 8));
			}
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
bool Player::isShieldApplied()
{
	return shieldApplied;
}
void Player::applyShield()
{
	shieldApplied = true;
	healthMeter.setFillColor(sf::Color(0, 255, 220, 180));
}