#include "HomingMissiles.h"

HomingMissiles::HomingMissiles(sf::Vector2f pos, std::string file, float r) : Bullet(pos, file, r)
{
}

HomingMissiles::~HomingMissiles()
{
}
void HomingMissiles::update(sf::Vector2f targetPos, sf::Time t, float rotation)
{
	dynamicSeek(targetPos, t, rotation);
	m_spr.setPosition(m_pos);
	timeToLive(200);
}
void HomingMissiles::dynamicSeek(sf::Vector2f pos, sf::Time t, float rotation)
{
	//Linear velocity
	sf::Vector2f steering = phys.linear(pos, m_pos, MAX_ACCEL_LIN);
	m_velocity = sf::Vector2f(m_velocity.x + steering.x * t.asSeconds(), m_velocity.y + steering.y * t.asSeconds());

	//Linear acceleration
	float rotato = phys.angularVel(rotation, m_rotation);
	m_rotation = m_spr.getRotation() + rotato * t.asSeconds();


	if (phys.length(m_velocity) > MAX_SPEED)
	{
		m_velocity = phys.normalise(m_velocity);
		m_velocity = sf::Vector2f(m_velocity.x * MAX_SPEED, m_velocity.y * MAX_SPEED);
	}
	m_pos = sf::Vector2f(m_pos.x + m_velocity.x, m_pos.y + m_velocity.y);
	
}