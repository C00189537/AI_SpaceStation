////////////////////////////////////////////////////////////
//
// Created by Dale Sinnott, Connor Maguire
//
////////////////////////////////////////////////////////////
#ifndef _COLLISIONMANAGER_H_
#define _COLLISIONMANAGER_H_
////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML\Graphics.hpp>
#include <memory>

class CollisionManager
{
public:
	CollisionManager();
	bool checkCollision(sf::IntRect &a, sf::IntRect &b);
	float getHorizontalIntersectionDepth(sf::FloatRect &a, sf::FloatRect &b);
	float getVerticalIntersectionDepth(sf::FloatRect &a, sf::FloatRect &b);
	sf::FloatRect asFloatRect(sf::IntRect& rect);

};
#endif;