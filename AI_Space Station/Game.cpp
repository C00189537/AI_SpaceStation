#include "Game.h"
#include <iostream>



Game::Game() :
	m_window{ sf::VideoMode{ 1920, 1080, 32 }, "AI Behaviours" }
{
	camera.setCenter(sf::Vector2f(0,0));
	camera.setSize(sf::Vector2f(480,360));
	camera.setViewport(sf::FloatRect(0, 0, 1, 1));

	m_player.create(sf::Vector2f(300.0f, 300.0f), sf::Vector2f(1.0f, 0.0f), "assets/player32.png");
	spawners.push_back(new Spawner(sf::Vector2f(800, 500), "assets/spawner82.png", 3));

	grid.initialise();

	shield1.initialise(sf::Vector2f(64 * 3, 64 * 5));
	shield2.initialise(sf::Vector2f(64 * 16, 64 * 1));
	shield3.initialise(sf::Vector2f(64 * 8, 64 * 16));
	std::vector<sf::Vector2f> shields;
	shields.push_back(shield1.pickup.getPosition());
	shields.push_back(shield2.pickup.getPosition());
	shields.push_back(shield3.pickup.getPosition());
	std::vector<bool*> actives;
	actives.push_back(shield1.isActive());
	actives.push_back(shield2.isActive());
	actives.push_back(shield3.isActive());
	radar.initialise(&m_player.pos, grid.level, shields, actives);
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
	m_player.update(m_window);
	m_player.updateVelocity(speed);
	for (int i = 0; i < spawners.size(); i++)
	{
		spawners.at(i)->update(m_player.pos, m_window, t, m_player.getRotation(), m_player.getVelocity());
	}
	CollisionManager();
	keyController();
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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
	{
		if (speed < m_player.MAX_SPEED)
			speed += accel;
	}
	//Deccelerate
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
	{
		if (speed > m_player.MIN_SPEED)
			speed -= accel;
	}
	//Left
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
	{
		m_player.setObjRotation(-rotato);
	}
	//Right
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
	{
		m_player.setObjRotation(rotato);
	}
}
void Game::CollisionManager()
{
	for (int i = 0; i < spawners.size(); i++)
	{
		spawners.at(i)->collisionManager(m_player.getRects());
		m_player.collisionManager(spawners.at(i)->getRects());
	}
	if (m_player.getRect().intersects(sf::IntRect(shield1.pickup.getGlobalBounds())))
	{
		if (!m_player.isShieldApplied())
		{
			shield1.setActive(false);
			m_player.applyShield();
		}
	}
	else if (m_player.getRect().intersects(sf::IntRect(shield2.pickup.getGlobalBounds())))
	{
		if (!m_player.isShieldApplied())
		{
			shield2.setActive(false);
			m_player.applyShield();
		}
	}
	else if (m_player.getRect().intersects(sf::IntRect(shield3.pickup.getGlobalBounds())))
	{
		if (!m_player.isShieldApplied())
		{
			shield3.setActive(false);
			m_player.applyShield();
		}
	}
}