#pragma once
#include "SFML\Graphics.hpp"
#include <iostream>
class BasicTypes
{
public:
	BasicTypes();
	~BasicTypes();

	sf::Vector2f normalise(sf::Vector2f);
	sf::Vector2f linear(sf::Vector2f v, sf::Vector2f m_v, float accel);
	float mapToRange(float r);
	float length(sf::Vector2f);
	float angularVel(float r, float m_r);
};

