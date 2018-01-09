#pragma once
#include <iostream>
#include <SFML\Graphics.hpp>
#include <math.h>
class alien
{

public:
	alien();
	~alien();

	void update(sf::RenderWindow &w);
	void updateMovement(sf::Vector2f pos, sf::Time t, float rotation, sf::Vector2f v);
	void render(sf::RenderWindow &w);
	void create(sf::Vector2f pos, sf::Vector2f vel, std::string file, int s, float maxSpeed);
	void dynamicWander(sf::Vector2f pos);
	void dynamicSeek(sf::Vector2f pos, sf::Time t, float rotation);
	void dynamicFlee(sf::Vector2f pos, sf::Time t, float rotation);
	void dynamicArrive(sf::Vector2f pos);
	void pursue(sf::Vector2f pos, sf::Time t, float rotation, sf::Vector2f v);
	

	

	float angle = 0;
	int behaviour = 0;
	enum state { IDLE, WANDER, SEEK, FLEE, ARRIVE, PURSUE};



private:

	float m_orientation = 0;

	int MAX_ROTATION = 1;
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

	float getNewOrientation(float orientation, sf::Vector2f v);
	std::string m_file;
	void loadSprite();
	void boundary(sf::RenderWindow &w);

};
