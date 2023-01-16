#include "../Header Files/GamePlay.h"
#include "../Header Files/GameOver.h"
#include "../Header Files/PauseGame.h"
#include <iostream>

#include "SFML/Window/Event.hpp"

#include <algorithm>
#include <stdlib.h>
#include <time.h>

GamePlay::GamePlay(std::shared_ptr<Context>& context) :
	m_context(context),
	m_snakeDirection(16.0f, 0.0f),
	m_elapsedTime(sf::Time::Zero),
	m_score(0),
	m_lives(3),
	m_isPaused(false),
	m_inGame(m_context->m_assets->getSoundTrack(IN_GAME_SOUND_TRACK)),
	foodAnimation(m_food)
{
	srand(time(nullptr));
}

GamePlay::~GamePlay()
{
	m_inGame.stop();
}

void GamePlay::init()
{
	// LOADING TEXTURES OF GAMEPLAY STATE
	m_context->m_assets->addTextures(OBJ, "Resources/assets/snakebody2.png");

	//GAME MAP
	m_context->m_assets->addTextures(MENU_BACKGROUND, "Resources/assets/bombmap.png");
	m_gameMap.setTexture(m_context->m_assets->getTexture(MENU_BACKGROUND));
	m_gameMap.setPosition(m_context->m_window->getSize().x / 2, m_context->m_window->getSize().y / 2);
	m_gameMap.setOrigin(sf::Vector2f(m_gameMap.getTexture()->getSize().x / 2, m_gameMap.getTexture()->getSize().y / 2));

	/*
	// GRASS/BACKGROUND INIT
	m_grass.setTexture(m_context->m_assets->getTexture(GRASS));
	m_grass.setTextureRect(m_context->m_window->getViewport(m_context->m_window->getDefaultView()));

	// WALLS INIT
	for (auto& wall : m_walls)
	{
		wall.setTexture(m_context->m_assets->getTexture(WALL));
	}
	m_walls[0].setTextureRect(sf::IntRect(0,0,m_context->m_window->getSize().x, 16 ));
	m_walls[1].setTextureRect(sf::IntRect(0,0,m_context->m_window->getSize().x, 16 ));
	m_walls[1].setPosition(0, m_context->m_window->getSize().y - 16);

	m_walls[2].setTextureRect(sf::IntRect(0,0,16,m_context->m_window->getSize().y));
	m_walls[3].setTextureRect(sf::IntRect(0,0,16,m_context->m_window->getSize().y));
	m_walls[3].setPosition(m_context->m_window->getSize().x - 16, 0);

	// FOOD SPAWN INIT
	m_food.setTexture(m_context->m_assets->getTexture(FOOD));
	
	foodAnimation.addFrame({ sf::IntRect(0,0,16,16), sf::Time(sf::seconds(0.1))});
	foodAnimation.addFrame({ sf::IntRect(16,0,16,16), sf::Time(sf::seconds(0.1))});
	foodAnimation.addFrame({ sf::IntRect(32,0,16,16), sf::Time(sf::seconds(0.1))});
	foodAnimation.addFrame({ sf::IntRect(48,0,16,16), sf::Time(sf::seconds(0.1))});

	m_food.setPosition(m_context->m_window->getSize().x / 2, m_context->m_window->getSize().y / 2);
	*/
	// SNAKE BODY/HEAD INIT
	m_snake.init(m_context->m_assets->getTexture(OBJ));
	

	// SCORE INIT
	m_scoreText.setFont(m_context->m_assets->getFont(MAIN_FONT));
	m_scoreText.setString("Score : " + std::to_string(m_score));
	m_scoreText.setPosition(0,-2);
	m_scoreText.setCharacterSize(15);
	m_scoreText.setFillColor(sf::Color::White);

	// LIVES COUNT INIT
	m_livesText.setFont(m_context->m_assets->getFont(MAIN_FONT));
	m_livesText.setString("Lives : " + std::to_string(m_lives));
	m_livesText.setPosition(m_context->m_window->getSize().x - 75, -2);
	m_livesText.setCharacterSize(15);
	m_livesText.setFillColor(sf::Color::White);

	// SOUND EFFECT SETTINGS
	m_foodEatSfx.setBuffer(m_context->m_assets->getSoundEffect(FOOD_SFX));
	m_foodEatSfx.setVolume(20);
	//takeScreenshot("../Resources/assets/");

}

void GamePlay::processInput()
{
	float countSpeed = 16.0f;
	sf::Event event;
	while (m_context->m_window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			m_context->m_window->close();
		else if (event.type == sf::Event::KeyPressed)
		{
			sf::Vector2f newDirection = m_snakeDirection;
			switch (event.key.code)
			{
				case sf::Keyboard::Up:
				{
					newDirection = { 0.0f, -countSpeed };
				}
				break;
				case sf::Keyboard::Down:
				{
					newDirection = { 0.0f, countSpeed };
				}
				break;
				case sf::Keyboard::Left:
				{
					newDirection = { -countSpeed, 0.0f };
				}
				break; 
				case sf::Keyboard::Right:
				{
					newDirection = { countSpeed, 0.0f };
				}
				break;
				case sf::Keyboard::Escape:
				{
					// INIT PAUSE STATE, ADD PAUSE STATE to m_states
					m_context->m_states->add(std::make_unique<PauseGame>(m_context));
					
				}
				break;
				default:
					break;
			}
			if (std::abs(m_snakeDirection.x) != std::abs(newDirection.x) || std::abs(m_snakeDirection.y) != std::abs(newDirection.y))
			{
				m_snakeDirection = newDirection;
			}
		}
	}
}

void GamePlay::update(sf::Time deltaTime)
{
	if (!m_isPaused)
	{
		foodAnimation.update(deltaTime);
		m_elapsedTime += deltaTime;

		if (m_elapsedTime.asSeconds() > 0.1)
		{
			//bool isOnWall = false;
			for (auto& wall : m_walls)
			{
				if (m_snake.isOn(wall))
				{
					m_inGame.stop();
					m_context->m_states->add(std::make_unique<GameOver>(m_context), true);
					break;
				}
			}
			if (m_snake.isOn(m_food))
			{
				//m_snake.grow(m_snakeDirection);
				m_foodEatSfx.play();

				int x = 0, y = 0;
				x = std::clamp<int>(rand() % m_context->m_window->getSize().x, 16, m_context->m_window->getSize().x - 2 * 16);
				y = std::clamp<int>(rand() % m_context->m_window->getSize().y, 16, m_context->m_window->getSize().y - 2 * 16);


				m_food.setPosition(x, y);
				m_score += 1;
				m_scoreText.setString("Score : " + std::to_string(m_score));
			}
			else
			{
				m_snake.move(m_snakeDirection);
			}

			if (m_snake.isSelfIntersecting())
			{
				--m_lives;
				m_livesText.setString("Lives : " + std::to_string(m_lives));

				if (m_lives == 0)
				{
					m_inGame.stop();
					
					m_context->m_states->add(std::make_unique<GameOver>(m_context), true);
					

				}
			}
			m_elapsedTime = sf::Time::Zero;
		}
	}
}

void GamePlay::draw()
{
	m_context->m_window->clear();
	m_context->m_window->draw(m_gameMap);

	/*m_context->m_window->draw(m_grass);
	for (auto& wall : m_walls)
	{
		m_context->m_window->draw(wall);

	}
	m_context->m_window->draw(m_food);*/
	m_context->m_window->draw(m_snake);
	m_context->m_window->draw(m_scoreText);
	m_context->m_window->draw(m_livesText);
	m_context->m_window->display();
}

void GamePlay::pause()
{
	m_isPaused = true;
	m_inGame.stop();
}

void GamePlay::start()
{
	m_isPaused = false;
	m_inGame.play();
}

void GamePlay::takeScreenshot(const std::string& filename)
{
	sf::Texture texture;
	texture.create(m_context->m_window->getSize().x, m_context->m_window->getSize().y);
	texture.update(*m_context->m_window);
	if (texture.copyToImage().saveToFile(filename))
	{
		std::cout << "screenshot saved to " << filename << std::endl;
	}
	else
	{
		// Error handling
	}
}
