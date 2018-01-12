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

	void update(sf::RenderWindow &w);
	void updateVelocity(float v);
	void render(sf::RenderWindow &w);
	void create(sf::Vector2f p, sf::Vector2f vel, std::string file);
	void setObjRotation(float r);
	void shoot();
	sf::Vector2f getVelocity();

	float MAX_SPEED = 2.f;
	float MIN_SPEED = 0;
	float angle = 20;
	sf::Vector2f pos;

	std::vector<Bullet*> bullets;
	int MAX_BULLETS = 100;
	int currentBullets = 0;
	float getRotation();

	std::vector<sf::IntRect> Player::getRects();
	sf::IntRect Player::getRect();
	void collisionManager(std::vector<sf::IntRect> r);
	bool isShieldApplied();
	void applyShield();
private:

	sf::Vector2f m_velocity;
	sf::Texture m_texture;
	sf::Sprite m_spr;
	sf::Texture m_shieldTexture;
	sf::Sprite m_shieldSpr;
	sf::RectangleShape healthMeter;

	std::string m_file;
	void loadSprite();
	void boundary(sf::RenderWindow &w);
	sf::IntRect myBox;
	int hp = 10;
	bool shieldApplied = false;
};
