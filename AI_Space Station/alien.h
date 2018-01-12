#pragma once
#include <iostream>
#include "BasicTypes.h"
#include <SFML\Graphics.hpp>
#include <math.h>
class alien
{

public:
	alien(){}
	alien(sf::Vector2f pos, sf::Vector2f vel, std::string file, int s, float maxSpeed, int health);
	~alien();

	void update();
	void updateMovement(sf::Vector2f pos, sf::Time t, float rotation, sf::Vector2f v);
	void render(sf::RenderWindow &w);
	void createBehaviour(int s);
	void dynamicWander(sf::Vector2f pos);
	void dynamicSeek(sf::Vector2f pos, sf::Time t, float rotation);
	
	float angle = 0;
	int behaviour = 0;
	enum state { IDLE, WANDER, SEEK, FLEE, ARRIVE, PURSUE};

	bool alive = true;
	int hp = 2;

	sf::IntRect myBox;
	void collisionManager(std::vector<sf::IntRect> r);

protected:

	float m_orientation = 0;

	int MAX_ROTATION = 360;
	float MAX_SPEED;
	float maxTimePrediction = 20.0f;

	int arrivalRad = 50;
	int slowRad = 100;

	float MAX_ACCEL_LIN = 10.0f;
	float MAX_ACCEL_ANG = 2.0f;

	sf::Vector2f m_pos;
	sf::Vector2f m_velocity;
	sf::Texture m_texture;
	sf::Sprite m_spr;

	float currentOrientation = 0;
	float m_rotation = 0;

	int spawnCount = 0;
	int spawnTimer = 0;
	int MAX_SPAWN = 2;

	std::string m_file;
	void loadSprite();
	void boundaryBullet(sf::IntRect target);
	BasicTypes phys;

	void isAlive();
	int movetime = 0;
};
