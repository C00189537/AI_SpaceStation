#include "Worker.h"



Worker::Worker(sf::Vector2f p, sf::Vector2f vel, std::string file) : m_pos(p), 
m_velocity(vel), m_file(file)
{
	loadSprite();
	m_spr.setOrigin(m_spr.getGlobalBounds().width / 2, m_spr.getGlobalBounds().height / 2);
	myBox = sf::IntRect(p.x, p.y, m_spr.getGlobalBounds().width, m_spr.getGlobalBounds().height);
	alive = true;
}


Worker::~Worker()
{
}

void Worker::loadSprite()
{
	if (!m_texture.loadFromFile(m_file))
	{
		// simple error message if previous call fails
		std::cout << "problem loading logo" << std::endl;
	}
	m_spr.setTexture(m_texture);
	m_spr.setPosition(m_pos.x, m_pos.y);
}
void Worker::update()
{
	myBox = sf::IntRect(m_pos.x, m_pos.y, m_spr.getGlobalBounds().width, m_spr.getGlobalBounds().height);
}
void Worker::render(sf::RenderWindow &w)
{
	w.draw(m_spr);
}
void Worker::updateVelocity(sf::Vector2f pos, float rotation, sf::Time t)
{
	if (flee)
	{
		//Linear velocity
		sf::Vector2f steering = phys.linear(m_pos, pos, MAX_ACCEL_LIN);
		m_velocity = sf::Vector2f(m_velocity.x + steering.x * t.asSeconds(), m_velocity.y + steering.y * t.asSeconds());

		//Linear acceleration
		float rotato = phys.angularVel(rotation, m_rotation);
		m_rotation = m_spr.getRotation() + rotato * t.asSeconds();


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
	else
	{

	}
}
sf::IntRect Worker::getRect()
{
	return myBox;
}
void Worker::collisionManager(sf::IntRect target)
{
	if (target.intersects(myBox))
	{
		alive = false;
	}
}