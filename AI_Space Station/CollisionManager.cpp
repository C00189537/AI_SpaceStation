//Created by Dale Sinnott, Connor Maguire
#include "CollisionManager.h"

CollisionManager::CollisionManager()
{

}

bool CollisionManager::checkCollision(sf::IntRect &a, sf::IntRect &b)
{
	if (a.intersects(b))
	{
		return true;
	}
	return false;
}
float CollisionManager::getHorizontalIntersectionDepth(sf::FloatRect &a, sf::FloatRect &b)
{
	float halfWidthA = a.width / 2;
	float halfWidthB = b.width / 2;

	float centerA = a.left + halfWidthA;
	float centerB = b.left + halfWidthB;

	float distanceX = centerA - centerB;
	float minDistanceX = halfWidthA + halfWidthB;

	if (std::abs(distanceX) >= minDistanceX)
	{
		return 0;
	}

	if (distanceX > 0) {
		return minDistanceX - distanceX;
	}
	else
	{
		return -minDistanceX - distanceX;
	}
}
float CollisionManager::getVerticalIntersectionDepth(sf::FloatRect &a, sf::FloatRect &b)
{
	float halfHeightA = a.height / 2;
	float HalfHeightB = b.height / 2;

	float centerA = a.top + halfHeightA;
	float centerB = b.top + HalfHeightB;

	float distanceY = centerA - centerB;
	float minDistanceY = halfHeightA + HalfHeightB;

	if (std::abs(distanceY) >= minDistanceY)
	{
		return 0;
	}

	if (distanceY > 0) {
		return minDistanceY - distanceY;
	}
	else
	{
		return -minDistanceY - distanceY;
	}
}
sf::FloatRect CollisionManager::asFloatRect(sf::IntRect &rect)
{
	return sf::FloatRect(rect.left, rect.top, rect.width, rect.height);
}