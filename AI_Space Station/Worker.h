#pragma once
#include "SFML\Graphics.hpp"
#include "BasicTypes.h"
#include <iostream>
class Worker
{
public:
	Worker(sf::Vector2f p, sf::Vector2f vel, std::string file);
	~Worker();
	void update();
	void updateVelocity(sf::Vector2f pos, float rotation, sf::Time t);
	void render(sf::RenderWindow &w);

	sf::IntRect getRect();
	void collisionManager(sf::IntRect target);
	bool alive = true;
	sf::Vector2f getPos();
	sf::Vector2f getVelocity();
	float getRotation();

private:

	sf::Vector2f m_velocity;
	sf::Texture m_texture;
	sf::Sprite m_spr;

	sf::Vector2f m_pos;

	std::string m_file;
	void loadSprite();
	sf::IntRect myBox;

	float m_rotation;

	bool flee;
	BasicTypes phys;

	int MAX_ROTATION = 360;
	float MAX_SPEED;
	float maxTimePrediction = 20.0f;

	int arrivalRad = 50;
	int slowRad = 100;

	float MAX_ACCEL_LIN = 10.0f;
	float MAX_ACCEL_ANG = 2.0f;

	float m_orientation;
	

	
};

