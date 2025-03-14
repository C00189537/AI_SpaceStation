#include "Game.h"
#include <iostream>



Game::Game() :
	m_window{ sf::VideoMode{ 1920, 1080, 32 }, "AI Behaviours" }
{
	camera.setCenter(sf::Vector2f(0,0));
	camera.setSize(sf::Vector2f(528,396));
	camera.setViewport(sf::FloatRect(0, 0, 1, 1));

	m_player.create(sf::Vector2f(80.0f, 80.0f), sf::Vector2f(1.0f, 0.0f), "assets/player32.png");

	spawners.push_back(new Spawner(sf::Vector2f(6 * 64, 13 * 64), "assets/spawner82.png", 3));
	spawners.push_back(new Spawner(sf::Vector2f(13 * 64, 6 * 64), "assets/spawner82.png", 3));
	spawners.push_back(new Spawner(sf::Vector2f(13 * 64, 13 * 64), "assets/spawner82.png", 3));

	grid.initialise();
	map = new Graph();
	for (int x = 0; x < grid.WIDTH; x++)
	{
		for (int y = 0; y < grid.HEIGHT; y++)
		{
			if (grid.level[y][x] == 0)
			{
				map->AddNode(x, y, false);
			}
			else
			{
				map->AddNode(x, y, true);
			}
		}
	}
	map->GenerateGraph();
	

	workerSpawn[0] = sf::Vector2f(64 *4, 64 * 2);
	workerSpawn[1] = sf::Vector2f(64 * 6, 64 * 2);
	workerSpawn[2] = sf::Vector2f(64 * 8, 64 * 2);
	workerSpawn[3] = sf::Vector2f(64 * 10, 64 * 2);
	workerSpawn[4] = sf::Vector2f(64 * 12, 64 * 2);
	workerSpawn[5] = sf::Vector2f(64 * 14, 64 * 2);
	workerSpawn[6] = sf::Vector2f(64 * 16, 64 * 2);
	workerSpawn[7] = sf::Vector2f(64 * 18, 64 * 2);
	workerSpawn[8] = sf::Vector2f(64 * 18, 64 * 4);
	workerSpawn[9] = sf::Vector2f(64 * 11, 64 * 2);


	for (int i = 0; i < 10; i++)
	{
		workers.push_back(new Worker(workerSpawn[i], sf::Vector2f(1, 1), "assets/worker48.png", map));
	}

	sweepers.push_back(new Sweeper(sf::Vector2f(500, 500), sf::Vector2f(1, 1), "assets/sweeper32.png", 2, 1, 6));

	shield1.initialise(sf::Vector2f(64 * 5, 64 * 5));
	shield2.initialise(sf::Vector2f(64 * 16, 64 * 1));
	shield3.initialise(sf::Vector2f(64 * 5, 64 * 16));
	std::vector<sf::Vector2f> shields;
	shields.push_back(shield1.pickup.getPosition());
	shields.push_back(shield2.pickup.getPosition());
	shields.push_back(shield3.pickup.getPosition());
	std::vector<bool*> actives;
	actives.push_back(shield1.isActive());
	actives.push_back(shield2.isActive());
	actives.push_back(shield3.isActive());
	std::vector<sf::Vector2f> spawnersPositions;
	for (int i = 0; i < spawners.size(); i++)
	{
		spawnersPositions.push_back(spawners.at(i)->m_pos);
	}
	radar.initialise(&m_player.pos, grid.level, shields, actives, spawnersPositions);
}
Game::~Game()
{
	
}
void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Time timePerFrame = sf::seconds(1.f / 60.f); // 60 fps
	while (m_window.isOpen())
	{
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			//processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps

			sf::Event event;
			while (m_window.pollEvent(event))
			{
				if (sf::Event::Closed == event.type) // window message
				{
					m_window.close();
				}
			}

		}
		render(); // as many as possible
	}
}
void Game::update(sf::Time t)
{
	collision();
	keyController();
	m_player.update();
	m_player.updateVelocity(speed);
	for (int i = 0; i < spawners.size(); i++)
	{
		spawners.at(i)->update(m_player.pos, m_window, t, m_player.getRotation(), m_player.getVelocity());
	}

	for (int i = 0; i < sweepers.size(); i++)
	{
		//Find the closest worker
		int holder = 0;
		double distance = 1000;
		for (int j = 0; j < workers.size(); j++)
		{
			double temp = checkDistance(sweepers.at(i)->getPos(), workers.at(i)->getPos());
			if (temp < distance)
			{
				holder = j;
			}
		}
		if (sweepers.at(i)->alive)
		{
			sweepers.at(i)->update();
			if (workers.size() != 0)
			{
				sweepers.at(i)->updateMovement(workers.at(holder)->getPos(), t, workers.at(holder)->getRotation(), workers.at(holder)->getVelocity());
			}
			else
			{
				sweepers.at(i)->dynamicWander(m_player.pos);
			}
		}
		else
		{
			m_player.addWorker(sweepers.at(i)->workerCount);
			delete sweepers.at(i);
			sweepers.erase(sweepers.begin() + i);
		}
	}
	for (int  i = 0; i < workers.size(); i++)
	{
		if (workers.at(i)->alive)
		{
			workers.at(i)->update();
			for (int j = 0; j < sweepers.size(); j++)
			{
				if (checkDistance(workers.at(i)->getPos(), sweepers.at(j)->getPos()) <= 100)
				{
					std::cout << workers.at(i)->flee << std::endl;	
					workers.at(i)->flee = true;
				}
				else
				{
					workers.at(i)->flee = false;
				}
			}
			workers.at(i)->updateVelocity(m_player.pos, m_player.getRotation(), t);
		}
		else
		{
			delete workers.at(i);
			workers.erase(workers.begin() + i);
		}
	}

	
	camera.setCenter(m_player.pos); 
	m_window.setView(camera); //comment out for full view
	radar.update();

}
void Game::render()
{
	m_window.clear(sf::Color::Black);
	grid.render(m_window);
	for (int i = 0; i < spawners.size(); i++)
	{
		spawners.at(i)->render(m_window);
	}
	for (int i = 0; i < workers.size(); i++)
	{
		workers.at(i)->render(m_window);
	}
	for (int i = 0; i < sweepers.size(); i++)
	{
		sweepers.at(i)->render(m_window);
	}
	shield1.render(m_window);
	shield2.render(m_window);
	shield3.render(m_window);
	m_player.render(m_window);
	radar.render(m_window);
	m_window.display();
}

void Game::keyController()
{
	//Space to shoot
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
	{
		m_player.shoot();
	}
	//Accelerate
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
	{
		if (speed < m_player.MAX_SPEED)
			speed += accel;
	}
	//Deccelerate
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
	{
		if (speed >= m_player.MIN_SPEED)
		{
			speed *= 0.9f;
		}
	}
	//Left
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		m_player.setObjRotation(-rotato);
	}
	//Right
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		m_player.setObjRotation(rotato);
	}
}
void Game::collision()
{
	for (int i = 0; i < spawners.size(); i++)
	{
		spawners.at(i)->collisionManager(m_player.getRects());
		m_player.collisionManager(spawners.at(i)->getRects());
	}
	std::vector<sf::IntRect> temp;
	for (int i = 0; i < sweepers.size(); i++)
	{
		sweepers.at(i)->collisionManager(m_player.getRects());
		temp.push_back(sweepers.at(i)->getRect());
	}
	m_player.collisionManager(temp); 
	m_player.specialCollision(grid);


	for (int i = 0; i < workers.size(); i++)
	{
		m_player.collectWorkers(workers.at(i)->getRect());
		workers.at(i)->collisionManager(m_player.getRect());

		for (int j = 0; j < sweepers.size(); j++)
		{
			workers.at(i)->collisionManager(sweepers.at(j)->getRect());
		}
	}
	for (int i = 0; i < sweepers.size(); i++)
	{
		for (int j = 0; j < workers.size(); j++)
		{
			sweepers.at(i)->workerCollision(workers.at(j)->getRect());
		}
	}
	if (m_player.getRect().intersects(sf::IntRect(shield1.pickup.getGlobalBounds())) && *shield1.isActive())
	{
		if (!m_player.isShieldApplied())
		{
			shield1.setActive(false);
			m_player.applyShield();
		}
	}
	else if (m_player.getRect().intersects(sf::IntRect(shield2.pickup.getGlobalBounds())) && *shield2.isActive())
	{
		if (!m_player.isShieldApplied())
		{
			shield2.setActive(false);
			m_player.applyShield();
		}
	}
	else if (m_player.getRect().intersects(sf::IntRect(shield3.pickup.getGlobalBounds())) && *shield3.isActive())
	{
		if (!m_player.isShieldApplied())
		{
			shield3.setActive(false);
			m_player.applyShield();
		}
	}
	for (int x = 0; x < grid.WIDTH; x++)
	{
		for (int y = 0; y < grid.HEIGHT; y++)
		{
			if (grid.level[y][x] == 1)
			{
				if (m_player.getRect().intersects(sf::IntRect(x * 64, y * 64, 64, 64)))
				{
					if (cManager.checkCollision(m_player.getRect(), sf::IntRect(x * 64, y * 64, 64, 64)))
					{
						float offsetX = cManager.getHorizontalIntersectionDepth(cManager.asFloatRect(m_player.getRect()), cManager.asFloatRect(sf::IntRect(x * 64, y * 64, 64, 64)));
						float offsetY = cManager.getVerticalIntersectionDepth(cManager.asFloatRect(m_player.getRect()), cManager.asFloatRect(sf::IntRect(x * 64, y * 64, 64, 64)));

						if (std::abs(offsetX) > std::abs(offsetY))
						{
							m_player.setPosition(sf::Vector2f(m_player.pos.x, m_player.pos.y += offsetY));
						}
						else
						{
							m_player.setPosition(sf::Vector2f(m_player.pos.x += offsetX, m_player.pos.y ));
						}
					}
				}
			}
		}
	}
}
double Game::checkDistance(sf::Vector2f myPos, sf::Vector2f targetPos)
{
	int distancex = (targetPos.x - myPos.x) * (targetPos.x - myPos.x);
	int distancey = (targetPos.y - myPos.y) * (targetPos.y - myPos.y);

	return sqrt(distancex - distancey);
}
