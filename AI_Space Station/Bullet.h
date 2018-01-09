#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
class Bullet
{
public:
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

private:

	sf::Vector2f m_velocity;
	sf::Texture m_texture;
	sf::Sprite m_spr;

	std::string m_file;
	void loadSprite();
	void boundary(sf::RenderWindow &w);
	void timeToLive();
	int ttl = 0;
};

