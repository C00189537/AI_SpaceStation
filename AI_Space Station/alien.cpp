#include "alien.h"

sf::Vector2f normalise(sf::Vector2f);
float mapToRange(float r);
float length(sf::Vector2f);
float angularVel(float r, float m_r);

sf::Vector2f linear(sf::Vector2f v, sf::Vector2f m_v, float accel);

alien::alien()
{

}
alien::~alien()
{

}
void alien::create(sf::Vector2f pos, sf::Vector2f vel, std::string file, int s, float maxSpeed)
{
	m_pos = pos;
	m_velocity = vel;
	m_file = file;
	loadSprite();
	MAX_SPEED = maxSpeed;
	m_spr.setOrigin(m_spr.getGlobalBounds().width / 2, m_spr.getGlobalBounds().height / 2);

	switch (s)
	{
	case 1:
		behaviour = state::WANDER;
		break;
	case 2:
		behaviour = state::SEEK;
		break;
	case 3:
		behaviour = state::FLEE;
		break;
	case 4:
		behaviour = state::ARRIVE;
		break;
	case 5:
		behaviour = state::PURSUE;
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
void alien::update(sf::RenderWindow &w)
{
	boundary(w);
	m_spr.setRotation(m_orientation);
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
	case alien::FLEE:
		dynamicFlee(pos, t, rotation);
		break;
	case alien::ARRIVE:
		dynamicArrive(pos);
		break;
	case alien::PURSUE:
		pursue(pos, t, rotation, v);
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
void alien::boundary(sf::RenderWindow &w)
{
	if (m_spr.getPosition().x - (m_spr.getGlobalBounds().width / 2) > w.getSize().x)
	{
		m_pos.x = 0 - (m_spr.getGlobalBounds().width / 3);
	}
	else if (m_spr.getPosition().x + (m_spr.getGlobalBounds().width / 2) < 0)
	{
		m_pos.x = w.getSize().x + (m_spr.getGlobalBounds().width / 3);
	}
	else if (m_spr.getPosition().y - (m_spr.getGlobalBounds().height / 2) > w.getSize().y)
	{
		m_pos.y = 0 - m_spr.getGlobalBounds().height / 3;
	}
	else if (m_spr.getPosition().y + (m_spr.getGlobalBounds().height / 2) < 0)
	{
		m_pos.y = w.getSize().y + (m_spr.getGlobalBounds().height / 3);
		std::cout << m_pos.y << std::endl;
	}
	m_spr.setPosition(m_pos);
}

//Wander: Moves towards a target while rotating randomly
void alien::dynamicWander(sf::Vector2f pos)
{
	

}
//Seek: Follow the player
void alien::dynamicSeek(sf::Vector2f pos, sf::Time t, float rotation)
{
	//Linear velocity
	sf::Vector2f steering = linear(pos, m_pos, MAX_ACCEL_LIN);
	m_velocity = sf::Vector2f(m_velocity.x + steering.x * t.asSeconds(), m_velocity.y + steering.y * t.asSeconds());

	//Linear acceleration
	float rotato = angularVel(rotation, m_rotation);
	m_rotation = m_spr.getRotation() + rotato * t.asSeconds();


	if (length(m_velocity) > MAX_SPEED)
	{
		m_velocity = normalise(m_velocity);
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
	m_orientation = m_orientation + m_rotation * t.asSeconds();
}
void alien::dynamicFlee(sf::Vector2f pos, sf::Time t, float rotation)
{
	//Linear velocity
	sf::Vector2f steering = linear(m_pos, pos, MAX_ACCEL_LIN);
	m_velocity = sf::Vector2f(m_velocity.x + steering.x * t.asSeconds(), m_velocity.y + steering.y * t.asSeconds());

	//Linear acceleration
	float rotato = angularVel(rotation, m_rotation);
	m_rotation = m_spr.getRotation() + rotato * t.asSeconds();


	if (length(m_velocity) > MAX_SPEED)
	{
		m_velocity = normalise(m_velocity);
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
	m_orientation = m_orientation + m_rotation * t.asSeconds();
}
void alien::dynamicArrive(sf::Vector2f pos)
{
	sf::Vector2f direction = sf::Vector2f(pos.x - m_pos.x, pos.y - m_pos.y);
	float distance = length(direction);
	int targetSpeed = 0;
	//Set speed
	if (distance < arrivalRad)
	{
		targetSpeed = 0;
	}
	else if (distance > slowRad)
	{
		targetSpeed = MAX_SPEED;
	}
	else
	{
		targetSpeed = MAX_SPEED * (distance / slowRad);
	}
	m_velocity = direction;
	m_velocity = normalise(m_velocity);
	m_velocity = sf::Vector2f(m_velocity.x * targetSpeed, m_velocity.y * targetSpeed);
	m_pos = sf::Vector2f(m_pos.x + m_velocity.x, m_pos.y + m_velocity.y);
}
void alien::pursue(sf::Vector2f pos, sf::Time t, float rotation, sf::Vector2f v)
{
	sf::Vector2f direction = sf::Vector2f(pos.x - m_pos.x, pos.y - m_pos.y);
	float distance = length(direction);
	float speed = length(m_velocity);
	float timePrediction = 0;
	if (speed <= distance / maxTimePrediction)
	{
		timePrediction = maxTimePrediction;
	}
	else
	{
		timePrediction = distance / speed;
	}
	sf::Vector2f newTarget = sf::Vector2f((pos.x + v.x) * timePrediction, (pos.y + v.y) * timePrediction);
	dynamicSeek(newTarget, t, rotation);
}
//Normalises a vector
sf::Vector2f normalise(sf::Vector2f v)
{
	float length = sqrt((v.x * v.x) + (v.y * v.y));
	return sf::Vector2f(v.x / length, v.y / length);
}
//Calculates linear acceleration
sf::Vector2f linear(sf::Vector2f v, sf::Vector2f m_v, float accel)
{
	sf::Vector2f linear = sf::Vector2f(v.x - m_v.x, v.y - m_v.y);
	linear = normalise(linear);
	linear = linear * accel;
	return linear;
}
//Calculates angular acceleration
float angularVel(float r, float m_r)
{
	float angularAccel = r - m_r;
	return 0;
}

//Calculates the length of a vector
float length(sf::Vector2f v)
{
	float length = sqrt((v.x * v.x) + (v.y * v.y));
	return length;
}

float mapToRange(float r)
{
	if (r > 3.14) {
		r -= 2 * 3.14;
	}
	else if (r < -3.14) {
		r += 2 * 3.14;
	}
	return r;
}