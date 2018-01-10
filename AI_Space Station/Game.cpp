#include "Game.h"
#include <iostream>



Game::Game() :
	m_window{ sf::VideoMode{ 1920, 1080, 32 }, "AI Behaviours" }
{
	m_player.create(sf::Vector2f(300.0f, 300.0f), sf::Vector2f(1.0f, 0.0f), "assets/player32.png");
	spawners.push_back(new Spawner(sf::Vector2f(800, 500), "assets/spawner82.png", 3));
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
				/*if (sf::Keyboard::Up == event.key.code)
				{
					if (speed < m_player.MAX_SPEED)
						speed += accel;
				}
				if (sf::Keyboard::Down == event.key.code)
				{
					if (speed > m_player.MIN_SPEED)
						speed -= accel;
				}
				if (sf::Keyboard::Right == event.key.code)
				{
					m_player.setObjRotation(rotato);
				}
				if (sf::Keyboard::Left == event.key.code)
				{
					m_player.setObjRotation(-rotato);
				}
				if (sf::Keyboard::Space == event.key.code)
				{
					m_player.shoot();
				}*/
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
	keyController();
	
}
void Game::render()
{
	m_window.clear(sf::Color::Black);
	for (int i = 0; i < spawners.size(); i++)
	{
		spawners.at(i)->render(m_window);
	}
	m_player.render(m_window);
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