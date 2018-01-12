#include "Worker.h"

float GetMagnitude(sf::Vector2f vec2);
float random(int v, int v2);

Worker::Worker(sf::Vector2f p, sf::Vector2f vel, std::string file, Graph* g) : m_pos(p), 
m_velocity(vel), m_file(file), m_graph(g)
{
	loadSprite();
	m_spr.setOrigin(m_spr.getGlobalBounds().width / 2, m_spr.getGlobalBounds().height / 2);
	myBox = sf::IntRect(p.x, p.y, m_spr.getGlobalBounds().width, m_spr.getGlobalBounds().height);
	alive = true;
	flee = false;
	MAX_SPEED = 0.5;
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
	m_spr.setPosition(m_pos);
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

	/*	m_path = m_graph->Path((int)(pos.x / 64), (int)(pos.y / 64), (int)(m_pos.x /64), (int)(m_pos.y / 64));
		if (m_path.size() > 0)
		{
			sf::Rect<int> holderThis = sf::Rect<int>(m_pos.x - 32, m_pos.y - 32, myBox.width, myBox.height);
			sf::Rect<int> holderOther = sf::Rect<int>((m_path.back().x * 64) - 24, (m_path.back().y * 64) - 24, 48, 48);

			if (holderThis.intersects(holderOther))
			{
				if (m_path.size() > 1)
				{
					m_path.pop_back();
				}
			}
		Pursue(pos, t);

		}*/
		movetime++;
		if (movetime > 50)
		{
			movetime = 0;
			m_velocity = pos - m_pos;
			m_velocity = phys.normalise(m_velocity);
			m_orientation = m_orientation + MAX_ROTATION * random(-1, +1);
			m_velocity = sf::Vector2f(-sin(m_orientation), cos(m_orientation))*MAX_SPEED;
			m_pos = sf::Vector2f(m_pos.x + m_velocity.x, m_pos.y + m_velocity.y);
			m_orientation = (atan2(m_velocity.y, m_velocity.x) * 180 / 3.14159265);
			m_spr.setRotation(m_orientation);
		}
	
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
sf::Vector2f Worker::getPos()
{
	return m_pos;
}
sf::Vector2f Worker::getVelocity()
{
	return m_velocity;
}
float Worker::getRotation()
{
	return m_spr.getRotation();
}
void Worker::Pursue(sf::Vector2f otherLoc, sf::Time t)
{
	float timetotarget = 0.05;

	float targetSpeed = 0;
	sf::Vector2f targetVelocity = sf::Vector2f(0, 0);

	if (GetMagnitude(otherLoc - m_pos) < m_radiusStop)
	{
		targetSpeed = 0;
	}
	else if (GetMagnitude(otherLoc - m_pos) > m_radiusSlow)
	{
		targetSpeed = MAX_SPEED;
	}
	else
	{
		targetSpeed = MAX_SPEED * (GetMagnitude(otherLoc - m_pos) / m_radiusSlow);
	}

	targetVelocity = otherLoc - m_pos;
	targetVelocity.x = targetVelocity.x / GetMagnitude(targetVelocity);
	targetVelocity.y = targetVelocity.y / GetMagnitude(targetVelocity);

	targetVelocity = targetVelocity * targetSpeed;

	sf::Vector2f m_linear = targetVelocity - m_velocity;
	m_linear = m_linear / timetotarget;

	if (GetMagnitude(m_linear) > MAX_SPEED)
	{
		m_linear.x = m_linear.x / GetMagnitude(m_linear);
		m_linear.y = m_linear.y / GetMagnitude(m_linear);

		m_linear = m_linear * MAX_ACCEL_LIN;
	}

	m_velocity = m_velocity + (m_linear * (float)t.asSeconds());
	if (GetMagnitude(m_velocity) > MAX_SPEED)
	{
		m_velocity.x = m_velocity.x / GetMagnitude(m_velocity);
		m_velocity.y = m_velocity.y / GetMagnitude(m_velocity);
		m_velocity = m_velocity * MAX_ACCEL_LIN;
	}
	m_pos = sf::Vector2f(m_pos.x + m_velocity.x, m_pos.y + m_velocity.y);
	m_orientation = (atan2(m_velocity.y, m_velocity.x) * 180 / 3.14159265);
	m_spr.setRotation(m_orientation);
}

float GetMagnitude(sf::Vector2f vec2)//<! Vector magnitude
{
	return sqrt(vec2.x*vec2.x + vec2.y*vec2.y);;
}
float random(int v, int v2)
{
	return (rand() % v - v2);
}