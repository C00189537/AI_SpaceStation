#pragma once
#include <SFML\Graphics.hpp>
#include "BasicTypes.h"
#include <iostream>
#include "Grid.h"
#include "CollisionManager.h"
class Bullet
{
public:
	Bullet() {}
	Bullet(sf::Vector2f pos, std::string file, float r);
	~Bullet();
	
	void update();
	void render(sf::RenderWindow &w);
	//void create(sf::Vector2f pos, std::string file);
	void setObjRotation(float r);

	float speed = 10;
	float angle = 0;
	sf::Vector2f m_pos;
	bool alive;

	sf::IntRect getRect();
	void collisionManager(std::vector<sf::IntRect>);
	void bounce(Grid &g);
	

protected:

	sf::Vector2f m_velocity;
	sf::Texture m_texture;
	sf::Sprite m_spr;
	std::string m_file;
	void loadSprite();
	void timeToLive(int t);
	int ttl = 0;
	const int MAX_SPEED = 20;
	const int MAX_ACCEL_LIN = 20;


	sf::IntRect myBox;
	CollisionManager cManager;
};

