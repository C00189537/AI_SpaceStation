#pragma once
#include <iostream>
#include <SFML\Graphics.hpp>
#include "Bullet.h"
#include <vector>
class Player
{

public:
	Player();
	~Player();

	void update();
	void updateVelocity(int v);
	void render(sf::RenderWindow &w);
	void create(sf::Vector2f p, sf::Vector2f vel, std::string file);
	void setObjRotation(float r);
	void shoot();
	sf::Vector2f getVelocity();

	int MAX_SPEED = 2;
	int MIN_SPEED = 0;
	float angle = 20;
	sf::Vector2f pos;

	std::vector<Bullet*> bullets;
	int MAX_BULLETS = 100;
	int currentBullets = 0;
	float getRotation();

	std::vector<sf::IntRect> Player::getRects();
	sf::IntRect getRect();
	void collectWorkers(sf::IntRect target);
	void collisionManager(std::vector<sf::IntRect> r);

private:

	sf::Vector2f m_velocity;
	sf::Texture m_texture;
	sf::Sprite m_spr;

	std::string m_file;
	void loadSprite();
	sf::IntRect myBox;
	int hp = 10;
	int workerCount = 0;

};
