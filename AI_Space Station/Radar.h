////////////////////////////////////////////////////////////
//
// Created by Dale Sinnott, Connor Maguire
//
////////////////////////////////////////////////////////////
#ifndef _RADAR_H_
#define _RADAR_H_

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML\Graphics.hpp>
#include <memory>

class Radar
{
public:

	static const int WIDTH = 20;
	static const int HEIGHT = 20;
	////////////////////////////////////////////////////////////
	/// Default constructor
	///
	////////////////////////////////////////////////////////////
	Radar();

	////////////////////////////////////////////////////////////
	/// Updates the object
	///
	////////////////////////////////////////////////////////////
	void initialise(sf::Vector2f *playerPos, int _level[HEIGHT][WIDTH], std::vector<sf::Vector2f> shields, std::vector<bool*> &isShieldActive, std::vector<sf::Vector2f> spawnerPos);
	void update();

	////////////////////////////////////////////////////////////
	/// Drwas the object and it's components
	///
	////////////////////////////////////////////////////////////
	void render(sf::RenderWindow &window);


private:
	sf::RectangleShape m_radar[HEIGHT][WIDTH];
	sf::RectangleShape m_playerTracker;
	sf::RectangleShape m_background;
	sf::Vector2f *trackingPoint;
	std::vector<sf::Vector2f> m_shields;
	std::vector<sf::Vector2f> m_spawners;
	std::vector<sf::RectangleShape> m_shieldSqaures;
	std::vector<sf::RectangleShape> m_spawnerSquares;
	std::vector<bool*> m_isShieldActive;
};
#endif;