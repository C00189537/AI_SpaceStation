//Created by Dale Sinnott, Connor Maguire

#ifndef _TILE_H_
#define _TILE_H_

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML\Graphics.hpp>
#include <memory>

class Tile {
public:

	Tile(sf::Vector2f position,
		std::shared_ptr<sf::Texture> _defaultTexture,
		std::shared_ptr<sf::Texture> _wallTexture,
		int const size);
	~Tile();

	void render(sf::RenderWindow &window);
	void updatePosition(sf::Vector2f newPos);
	sf::IntRect bounds;
	sf::RectangleShape m_rect;
	sf::Sprite m_TileSprite;
	std::shared_ptr<sf::Texture> defaultTexture;
	std::shared_ptr<sf::Texture> wallTexture;
	enum TileType
	{
		WALL,
		DEFAULT
	};

	void setType(Tile::TileType newType);
	TileType tileType;
private:
	sf::Vector2f m_position;
	sf::Vector2i m_size;
	int count = 0;

};
#endif;