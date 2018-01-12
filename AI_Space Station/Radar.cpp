#include "Radar.h"

Radar::Radar()
{
	for (int x = 0; x < WIDTH; x++)
	{
		for (int y = 0; y < HEIGHT; y++)
		{
			m_radar[y][x].setFillColor(sf::Color::White);
			m_radar[y][x].setSize(sf::Vector2f(3, 3));
			
		}
	}
	m_playerTracker.setFillColor(sf::Color::Green);
	m_playerTracker.setSize(sf::Vector2f(3, 3));
	m_background.setFillColor(sf::Color(50,50,50,255));
	m_background.setSize(sf::Vector2f(1 + 4 * 20, 1 + 4 * 20));
	
}
void Radar::initialise(sf::Vector2f *playerPos, int _level[HEIGHT][WIDTH], std::vector<sf::Vector2f> shields, std::vector<bool*> &isShieldActive)
{
	m_shields = shields;
	m_isShieldActive = isShieldActive;
	for (int i = 0; i < 3; i++)
	{
		m_shieldSqaures.push_back(sf::RectangleShape(sf::Vector2f(3, 3)));
		m_shieldSqaures.at(i).setFillColor(sf::Color::Blue);
		
	}
	trackingPoint = playerPos;
	for (int x = 0; x < WIDTH; x++)
	{
		for (int y = 0; y < HEIGHT; y++)
		{
			if (_level[y][x] == 0)
			{
				m_radar[y][x].setFillColor(sf::Color(255,255,255,255));
			}
			else if (_level[y][x] == 1)
			{
				m_radar[y][x].setFillColor(sf::Color(0,0,0,255));
			}
			
		}
	}
}
void Radar::update()
{
	for (int x = 0; x < WIDTH; x++)
	{
		for (int y = 0; y < HEIGHT; y++)
		{
			m_radar[y][x].setPosition(sf::Vector2f(trackingPoint->x + (480 / 2) - (WIDTH * 4) + (x * 4), trackingPoint->y + (360 / 2) - (HEIGHT * 4) + (y * 4)));
		}
	}
	m_playerTracker.setPosition(sf::Vector2f(4 + trackingPoint->x + (480 / 2) - (WIDTH * 4) + (std::floor(trackingPoint->x / 64 - 0.5) * 4), 
		4 + trackingPoint->y + (360 / 2) - (HEIGHT * 4) + (std::floor(trackingPoint->y / 64 - 0.5) * 4)));
	m_background.setPosition(sf::Vector2f(trackingPoint->x + (480 / 2) - (WIDTH * 4) - 1, trackingPoint->y + (360 / 2) - (HEIGHT * 4) - 1));
	for (int i = 0; i < 3; i++)
	{
		m_shieldSqaures.at(i).setPosition(sf::Vector2f(trackingPoint->x + (480 / 2) - (WIDTH * 4) + ((std::floor(m_shields.at(i).x / 64 + 1) * 4)),
			trackingPoint->y + (360 / 2) - (HEIGHT * 4) + ((std::floor(m_shields.at(i).y / 64 + 1) * 4))));
	}
}
void Radar::render(sf::RenderWindow &window)
{
	window.draw(m_background);
	for (int x = 0; x < WIDTH; x++)
	{
		for (int y = 0; y < HEIGHT; y++)
		{
			window.draw(m_radar[y][x]);
		}
	}
	for (int i = 0; i < 3; i++)
	{
		if (*m_isShieldActive.at(i))
		{
			window.draw(m_shieldSqaures.at(i));
		}
	}
	window.draw(m_playerTracker);
}