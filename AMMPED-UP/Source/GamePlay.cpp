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
	m_playerDirection(0.0f, 0.0f),
	m_elapsedTime(sf::Time::Zero),
	m_score(0),
	m_lives(3),
	m_isPaused(false),
	m_inGame(m_context->m_assets->getSoundTrack(IN_GAME_SOUND_TRACK))
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
	m_context->m_assets->addTextures(PLAYER, "Resources/assets/yellowPlayer.png");
	m_context->m_assets->addTextures(BREAKABLE, "Resources/assets/breakable.png");
	m_context->m_assets->addTextures(BOMB_TRIGGER, "Resources/assets/bombTileset.png");

	//GAME MAP
	m_context->m_assets->addTextures(MENU_BACKGROUND, "Resources/assets/bombmap.png");
	m_gameMap.setTexture(m_context->m_assets->getTexture(MENU_BACKGROUND));
	m_gameMap.setPosition(m_context->m_window->getSize().x / 2, m_context->m_window->getSize().y / 2);
	m_gameMap.setOrigin(sf::Vector2f(m_gameMap.getTexture()->getSize().x / 2, m_gameMap.getTexture()->getSize().y / 2));

	//TILESET SETUP
	for (int i = 0; i < 30; i++)
	{
		for (int j = 0; j < 40; j++)
		{
			if (collisionMap[i][j] == BREAKABLE_TILE)
			{
				sf::Sprite breakabletile;
				breakabletile.setTexture(m_context->m_assets->getTexture(BREAKABLE));
				breakabletile.setPosition(sf::Vector2f( j * 16, i * 16 ));
				m_breakableTiles.push_back(breakabletile);
			}
		}
	}
	
	// PLAYER INIT
	m_player.init(m_context->m_assets->getTexture(PLAYER));
	m_player.m_bomb.init(m_context->m_assets->getTexture(BOMB_TRIGGER));




	// SCORE INIT
	m_scoreText.setFont(m_context->m_assets->getFont(MAIN_FONT));
	m_scoreText.setString("Score : " + std::to_string(m_score));
	m_scoreText.setPosition(0,-2);
	m_scoreText.setCharacterSize(15);
	m_scoreText.setFillColor(sf::Color::White);

	// TIMER INIT
	m_timerText.setFont(m_context->m_assets->getFont(MAIN_FONT));
	m_timerText.setString("Time : " + std::to_string(m_time));
	m_timerText.setPosition(604/2, -2);
	m_timerText.setCharacterSize(15);
	m_timerText.setFillColor(sf::Color::White);

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
			sf::Vector2f newDirection = m_playerDirection;
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
				case sf::Keyboard::Space:
				{
					m_player.m_bombPos = m_player.getPosition();
					if (!m_player.m_bomb.isBlasted())
					{
						std::cout << "Pressed Spacebard, and set the placed boolean to true" << std::endl;
						m_player.m_isBombPlaced = true;
					}
				}
				default:
					break;
			}
			if (std::abs(m_playerDirection.x) != std::abs(newDirection.x) || std::abs(m_playerDirection.y) != std::abs(newDirection.y))
			{
				m_playerDirection = newDirection;
				
			}
		}
	}
}

void GamePlay::update(sf::Time deltaTime)
{
	if (!m_isPaused)
	{
		m_elapsedTime += deltaTime;
		
		if (m_elapsedTime.asSeconds() > 1.0)
		{
			m_time--;
			m_timerText.setString("Time : " + std::to_string(m_time));
			m_elapsedTime = sf::Time::Zero;
			if (m_time < 0)
			{
				m_context->m_states->add(std::make_unique<GameOver>(m_context));
			}
		}
		if (m_player.m_isBombPlaced)
		{
			m_player.m_bomb.update(m_player.m_bombPos, deltaTime);

			if (m_player.m_bomb.isBlasted())
			{
				removeWalls(m_player.m_bomb.getPosition());
				m_player.m_isBombPlaced = false;
				m_player.m_bomb.setIsBlasted(false);
				m_player.m_bomb.setPosition(sf::Vector2f(640, 400));
				std::cout << "The time is up and the blast boolean and placed bool ean are set to false" << std::endl;
			}
		}
		

		if (checkCollision(m_player.getPosition() + m_playerDirection))
			m_playerDirection = { 0,0 };
		m_player.update(m_playerDirection, deltaTime);


		m_playerDirection = { 0,0 };
	}
}

void GamePlay::draw()
{
	m_context->m_window->clear();
	m_context->m_window->draw(m_gameMap);

	m_breakableTiles.clear();
	for (int i = 0; i < 30; i++)
	{
		for (int j = 0; j < 40; j++)
		{
			if (collisionMap[i][j] == BREAKABLE_TILE)
			{
				sf::Sprite breakabletile;
				breakabletile.setTexture(m_context->m_assets->getTexture(BREAKABLE));
				breakabletile.setPosition(sf::Vector2f(j * 16, i * 16));
				m_breakableTiles.push_back(breakabletile);
			}
		}
	}

	for (auto& breakable : m_breakableTiles)
	{
		m_context->m_window->draw(breakable);

	}

	
	/*m_context->m_window->draw(m_grass);
	for (auto& wall : m_walls)
	{
		m_context->m_window->draw(wall);

	}
	m_context->m_window->draw(m_food);*/
	m_context->m_window->draw(m_player.m_bomb);

	m_context->m_window->draw(m_player);

	m_context->m_window->draw(m_scoreText);
	m_context->m_window->draw(m_timerText);

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

bool GamePlay::checkCollision(sf::Vector2f pos)
{
	int i = pos.x / 16;
	int j = pos.y / 16;
	if (collisionMap[j][i] == WALL_TILE || collisionMap[j][i] == BREAKABLE_TILE)
		return true;
	return false;
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

void GamePlay::removeWalls(sf::Vector2f pos)
{
	int x = pos.x / 16;
	int y = pos.y / 16;
	if (collisionMap[y - 1][x] == BREAKABLE_TILE)
		collisionMap[y - 1][x] = EMPTY_TILE;
	if (collisionMap[y][x - 1] == BREAKABLE_TILE)
		collisionMap[y][x - 1] = EMPTY_TILE;
	if (collisionMap[y + 1][x] == BREAKABLE_TILE)
		collisionMap[y + 1][x] = EMPTY_TILE;
	if (collisionMap[y][x + 1] == BREAKABLE_TILE)
		collisionMap[y][x + 1] = EMPTY_TILE;
	
}
