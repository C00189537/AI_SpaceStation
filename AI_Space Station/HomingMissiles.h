#pragma once
#include "Bullet.h"
class HomingMissiles :
	public Bullet
{
public:
	HomingMissiles(sf::Vector2f pos, std::string file, float r);
	~HomingMissiles();
	void update(sf::Vector2f targetPos, sf::Time t, float rotation);
	void dynamicSeek(sf::Vector2f pos, sf::Time t, float rotation);

private:
	float maxTimePrediction = 20.0f;
	BasicTypes phys;
	float m_rotation;
};

