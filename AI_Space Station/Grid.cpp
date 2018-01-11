//Created by Dale Sinnott
#include "Grid.h"
#include <iostream>
Grid::Grid()
{

}
void Grid::render(sf::RenderWindow &window)
{
	for (int i = 0; i < HEIGHT * WIDTH; i++)
	{
		map.at(i)->render(window);
	}
}
void Grid::initialise()
{
	//Load the level grid from a text file
	load();
	
	sf::Texture defaultTexture;
	if (!defaultTexture.loadFromFile(defaultTexturePath)) { std::cout << defaultTexturePath << std::endl; }
	sf::Texture wallTexture;
	if (!wallTexture.loadFromFile(wallTexturePath)) { std::cout << wallTexturePath << std::endl; }

	Tile tempTile(sf::Vector2f(0 * 64, 0 * 64),
		std::make_shared<sf::Texture>(wallTexture),
		std::make_shared<sf::Texture>(defaultTexture),
		64);
	tCount = 0;
	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{//set tiles into grid
			tempTile.updatePosition(sf::Vector2f(x * 64, y * 64));
			switch (level[y][x])
			{
			case 1:
				tempTile.setType(Tile::WALL);
				break;
			default:
				tempTile.setType(Tile::DEFAULT);
				break;
			}
			map.push_back(std::make_shared<Tile>(tempTile));
		}
	}
	
}
void Grid::load()
{
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			level[i][j] = 0;
		}
	}
	//Open file and input into the array 
	std::ifstream file;
	file.open("assets/level.txt");
	if (file.is_open())
	{
		std::cout << "File Opened" << std::endl;
		while (!file.eof())
		{
			for (int i = 0; i < HEIGHT; i++)
			{
				for (int j = 0; j < WIDTH; j++)
				{
					file >> level[i][j];
					std::cout << level[i][j];
				}
				std::cout << std::endl;
			}
		}
	}
	file.close();
}