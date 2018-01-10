#pragma once
#include "SFML\Graphics.hpp"
#include "alien.h"
#include "HomingMissiles.h"
#include <iostream>
#include <vector>
class Spawner
{
public:
	Spawner(sf::Vector2f pos, std::string file, int spawn);
	~Spawner();

	void update(sf::Vector2f targetPos, sf::RenderWindow &w, sf::Time t, float rotation, sf::Vector2f v);
	void spawn();
	void render(sf::RenderWindow &w);
	void shoot(sf::Vector2f pos);

private:

	sf::Vector2f m_pos;
	sf::Texture m_texture;
	sf::Sprite m_spr;

	float currentOrientation = 0;
	float m_rotation = 0;

	int spawnCount = 0;
	int spawnTimer = 0;
	int MAX_SPAWN;

	int bulletCount = 0;
	const int MAX_BULLETS = 20;

	std::string m_file;
	void loadSprite();

	std::vector<alien*> predators;
	std::vector<HomingMissiles*> bullets;

	int rotationTimer = 0;
	void rotationer();

};

