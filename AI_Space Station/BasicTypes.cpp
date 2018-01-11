#include "BasicTypes.h"

BasicTypes::BasicTypes()
{
}

BasicTypes::~BasicTypes()
{
}
sf::Vector2f BasicTypes::normalise(sf::Vector2f v)
{
	float length = sqrt((v.x * v.x) + (v.y * v.y));
	return sf::Vector2f(v.x / length, v.y / length);
}
//Calculates linear acceleration
sf::Vector2f BasicTypes::linear(sf::Vector2f v, sf::Vector2f m_v, float accel)
{
	sf::Vector2f linear = sf::Vector2f(v.x - m_v.x, v.y - m_v.y);
	linear = normalise(linear);
	linear = linear * accel;
	return linear;
}
//Calculates angular acceleration
float BasicTypes::angularVel(float r, float m_r)
{
	float angularAccel = r - m_r;
	return angularAccel;
}

//Calculates the length of a vector
float BasicTypes::length(sf::Vector2f v)
{
	float length = sqrt((v.x * v.x) + (v.y * v.y));
	return length;
}

float BasicTypes::mapToRange(float r)
{
	if (r > 3.14) {
		r -= 2 * 3.14;
	}
	else if (r < -3.14) {
		r += 2 * 3.14;
	}
	return r;
}