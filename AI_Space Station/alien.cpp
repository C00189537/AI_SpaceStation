#include "alien.h"



alien::alien(sf::Vector2f pos, sf::Vector2f vel, std::string file, int s, float maxSpeed, int health) : m_pos(pos), m_file(file),
m_velocity(vel), MAX_SPEED(maxSpeed), hp(health)
{
	m_spr.setOrigin(m_spr.getGlobalBounds().width / 2, m_spr.getGlobalBounds().height / 2);
	createBehaviour(s);
	loadSprite();
	alive = true;
	myBox = sf::IntRect(pos.x, pos.y, m_spr.getGlobalBounds().width, m_spr.getGlobalBounds().height);
}
alien::~alien()
{

}
void alien::createBehaviour(int s)
{

	switch (s)
	{
	case 1:
		behaviour = state::WANDER;
		break;
	case 2:
		behaviour = state::SEEK;
		break;
	default:
		break;
	}

	
}
void alien::loadSprite()
{
	if (!m_texture.loadFromFile(m_file))
	{
		// simple error message if previous call fails
		std::cout << "problem loading logo" << std::endl;
	}
	m_spr.setTexture(m_texture);
	m_spr.setPosition(m_pos.x, m_pos.y);
}
void alien::update()
{
	m_spr.setRotation(m_orientation);
	m_spr.setPosition(m_pos);
	myBox = sf::IntRect(m_pos.x, m_pos.y, m_spr.getGlobalBounds().width, m_spr.getGlobalBounds().height);
}
void alien::updateMovement(sf::Vector2f pos, sf::Time t, float rotation, sf::Vector2f v)
{
	switch (behaviour)
	{
	case alien::IDLE:

		break;
	case alien::WANDER:
		dynamicWander(pos);
		break;
	case alien::SEEK:
		dynamicSeek(pos, t, rotation);
		break;
	default:
		break;
	}
	

}
void alien::render(sf::RenderWindow &w)
{
	w.draw(m_spr);
	//std::cout << "sprite drawn" << std::endl;
}
void alien::boundaryBullet(sf::IntRect target)
{
	if (target.intersects(myBox))
	{
		hp--;
	}
	isAlive();
}
//Seek: Follow the player
void alien::dynamicSeek(sf::Vector2f pos, sf::Time t, float rotation)
{
	//Linear velocity
	sf::Vector2f steering = phys.linear(pos, m_pos, MAX_ACCEL_LIN);
	m_velocity = sf::Vector2f(m_velocity.x + steering.x * t.asSeconds(), m_velocity.y + steering.y * t.asSeconds());

	//Linear acceleration
	float rotato = phys.angularVel(m_rotation, rotation);
	m_rotation = m_spr.getRotation() + rotato * t.asSeconds() + 90;
	

	if (phys.length(m_velocity) > MAX_SPEED)
	{
		m_velocity = phys.normalise(m_velocity);
		m_velocity = sf::Vector2f(m_velocity.x * MAX_SPEED, m_velocity.y * MAX_SPEED);
	}

	if (m_rotation > MAX_ROTATION)
	{
		m_rotation = MAX_ROTATION;
	}
	else if (-m_rotation > MAX_ROTATION)
	{
		m_rotation = -MAX_ROTATION;
	}
	m_pos = sf::Vector2f(m_pos.x + m_velocity.x, m_pos.y + m_velocity.y);
	m_orientation = (atan2(m_velocity.y, m_velocity.x) * 180 / 3.14159265);
	m_spr.setRotation(m_orientation);
}
void alien::dynamicWander(sf::Vector2f pos)
{
	movetime++;
	if (movetime > 50)
	{
		movetime = 0;
		m_velocity = pos - m_pos;
		m_velocity = phys.normalise(m_velocity);
		m_orientation = m_orientation + MAX_ROTATION * (rand() % 2 - 2);
		m_velocity = sf::Vector2f(-sin(m_orientation), cos(m_orientation))*MAX_SPEED;
		m_pos = sf::Vector2f(m_pos.x + m_velocity.x, m_pos.y + m_velocity.y);
		m_orientation = (atan2(m_velocity.y, m_velocity.x) * 180 / 3.14159265);
		m_spr.setRotation(m_orientation);
	}
}
void alien::isAlive()
{
	if (hp <= 0)
	{
		alive = false;
	}
}
void alien::collisionManager(std::vector<sf::IntRect> r)
{
	for (int i = 0; i < r.size(); i++)
	{
		boundaryBullet(r.at(i));
	}
}