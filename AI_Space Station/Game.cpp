#include "Game.h"
#include <iostream>



Game::Game() :
	m_window{ sf::VideoMode{ 1920, 1080, 32 }, "AI Behaviours" }
{
	m_player.create(sf::Vector2f(300.0f, 300.0f), sf::Vector2f(1.0f, 0.0f), "assets/player64.png");
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
				if (sf::Keyboard::Up == event.key.code)
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

}
void Game::render()
{
	m_window.clear(sf::Color::Black);
	m_player.render(m_window);
	m_window.display();
}

