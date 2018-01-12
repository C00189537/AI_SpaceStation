//Created by Dale Sinnott, Connor Maguire
#include "Tile.h"
#include <iostream>
Tile::Tile(sf::Vector2f position, std::shared_ptr<sf::Texture> _wallTexture, std::shared_ptr<sf::Texture> _defaultTexture, int const size = 64) :
	m_position(position), m_size(size, size)
{
	wallTexture = _wallTexture;
	defaultTexture = _defaultTexture;
	m_TileSprite.setTexture(*defaultTexture);
	m_TileSprite.setOrigin(m_TileSprite.getGlobalBounds().width / 2, m_TileSprite.getGlobalBounds().height / 2);
	m_TileSprite.setPosition(position.x, position.y);
	bounds.top = position.y;
	bounds.left = position.x;
	bounds.width = size;
	bounds.height = size;
	tileType = Tile::DEFAULT;
}
Tile::~Tile()
{

}
void Tile::setType(Tile::TileType newType)
{
	bounds.width = 64;
	bounds.height = 64;
	switch (newType)
	{
	case Tile::WALL:
		m_TileSprite.setTexture(*wallTexture);
		break;
	case Tile::DEFAULT:
		m_TileSprite.setTexture(*defaultTexture);
		break;
	default:
		break;
	}
	tileType = newType;
}
void Tile::render(sf::RenderWindow &window)
{
	window.draw(m_TileSprite);
}
void Tile::updatePosition(sf::Vector2f newPos)
{
	m_TileSprite.setPosition(newPos.x, newPos.y);
	bounds.top = newPos.y;
	bounds.left = newPos.x;
}