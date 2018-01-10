#pragma once
#include <SFML\Graphics.hpp>
#include "BasicTypes.h"
#include <iostream>
class Bullet
{
public:
	Bullet() {}
	Bullet(sf::Vector2f pos, std::string file, float r);
	~Bullet();
	
	void update(sf::RenderWindow &w);
	void render(sf::RenderWindow &w);
	//void create(sf::Vector2f pos, std::string file);
	void setObjRotation(float r);

	float speed = 20;
	float angle = 0;
	sf::Vector2f m_pos;
	bool alive;

protected:

	sf::Vector2f m_velocity;
	sf::Texture m_texture;
	sf::Sprite m_spr;

	std::string m_file;
	void loadSprite();
	void boundary(sf::RenderWindow &w);
	void timeToLive(int t);
	int ttl = 0;

	const int MAX_SPEED = 20;
	const int MAX_ACCEL_LIN = 20;
};

