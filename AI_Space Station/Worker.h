#pragma once
#include "SFML\Graphics.hpp"
#include "BasicTypes.h"
#include "Graph.h"
#include <iostream>
class Worker
{
public:
	Worker(sf::Vector2f p, sf::Vector2f vel, std::string file, Graph * g);
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
	bool flee;

private:

	sf::Vector2f m_velocity;
	sf::Texture m_texture;
	sf::Sprite m_spr;

	sf::Vector2f m_pos;

	std::string m_file;
	void loadSprite();
	sf::IntRect myBox;

	float m_rotation;

	
	BasicTypes phys;

	int MAX_ROTATION = 360;
	float MAX_SPEED = 2;
	float maxTimePrediction = 20.0f;

	int arrivalRad = 50;
	int slowRad = 100;

	float MAX_ACCEL_LIN = 10.0f;
	float MAX_ACCEL_ANG = 2.0f;

	float m_orientation;
	Graph * m_graph;
	std::vector<Node> m_path;

	void Pursue(sf::Vector2f otherLoc, sf::Time t);
	float m_radiusStop = 5;
	float  m_radiusSlow = 20;
	
	int movetime = 0;
};

