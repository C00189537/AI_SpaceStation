//Created by Dale Sinnott, Connor Maguire
#include "Shield.h"
#include <iostream>
Shield::Shield()
{
	
}
void Shield::initialise(sf::Vector2f pos)
{
	if (!texture.loadFromFile("assets/ShieldPickup.png"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading logo" << std::endl;
	}
	pickup.setOrigin(pickup.getGlobalBounds().width / 2 - 32, pickup.getGlobalBounds().height / 2- 32);
	pickup.setTexture(texture);
	pickup.setPosition(pos);
}
void Shield::setActive(bool state)
{
	active = state;
}
bool* Shield::isActive()
{
	return &active;
}
void Shield::render(sf::RenderWindow &window)
{
	if(active)
		window.draw(pickup);
}