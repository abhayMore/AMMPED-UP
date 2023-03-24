#include "../Header Files/GamePlay.h"
#include "../Header Files/GameOver.h"
#include "../Header Files/PauseGame.h"
#include <iostream>

#include "SFML/Window/Event.hpp"

#include <algorithm>
#include <stdlib.h>
#include <time.h>

int ReturnIntRandom(int lower, int upper)
{
	return (rand() % (upper - lower + 1)) + lower;
}


GamePlay::GamePlay(std::shared_ptr<Context>& context) :
	//m_enemyAI1(openSpaces[ReturnIntRandom(0,openSpaces.size()-1)]),
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
	m_context->m_assets->addTextures(ENEMY1, "Resources/assets/enemy1.png");
	m_context->m_assets->addTextures(ENEMY2, "Resources/assets/enemy2.png");
	m_context->m_assets->addTextures(ENEMY3, "Resources/assets/enemy3.png");
	m_context->m_assets->addTextures(BREAKABLE, "Resources/assets/breakable.png");
	m_context->m_assets->addTextures(VERTICAL_WALL_TILE, "Resources/assets/verticalWall.png");
	m_context->m_assets->addTextures(HORIZONTAL_WALL_TILE, "Resources/assets/HorizontalWall.png");
	m_context->m_assets->addTextures(INNER_COMPARTMENT_WALL_TILE, "Resources/assets/innerWall.png");

	m_context->m_assets->addTextures(BOMB_TRIGGER, "Resources/assets/bombTileset.png");
	m_context->m_assets->addTextures(EXPLOSION_CENTER, "Resources/assets/ExplosionCenter.png");
	m_context->m_assets->addTextures(EXPLOSION_SIDE, "Resources/assets/ExplosionSide.png");
	m_context->m_assets->addTextures(EXPLOSION_END, "Resources/assets/ExplosionEnd.png");

	//GAME MAP
	//m_context->m_assets->addTextures(MENU_BACKGROUND, "Resources/assets/bombmap.png");
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
				m_allWalls.push_back(breakabletile);

				//pairTile.push_back(std::make_pair(breakabletile, BREAKABLE_TILE));
			}
			if (collisionMap[i][j] == VERTICAL_WALL)
			{
				sf::Sprite vWall;
				vWall.setTexture(m_context->m_assets->getTexture(VERTICAL_WALL_TILE));
				vWall.setPosition(sf::Vector2f(j * 16, i * 16));
				m_VWalls.push_back(vWall);
			}

			if (collisionMap[i][j] == HORIZONTAL_WALL)
			{

				sf::Sprite hWall;
				hWall.setTexture(m_context->m_assets->getTexture(HORIZONTAL_WALL_TILE));
				hWall.setPosition(sf::Vector2f(j * 16, i * 16));
				m_HWalls.push_back(hWall);
			}
			if (collisionMap[i][j] == INNER_COMPARTMENT_WALL)
			{

				sf::Sprite iWall;
				iWall.setTexture(m_context->m_assets->getTexture(INNER_COMPARTMENT_WALL_TILE));
				iWall.setPosition(sf::Vector2f(j * 16, i * 16));
				m_innerCompartmentWalls.push_back(iWall);
			}
		}
	}

	

	m_directions = { sf::Vector2f(0,-1), sf::Vector2f(0,1), sf::Vector2f(-1,0), sf::Vector2f(1,0) };
	enemyDirectionAI1 = m_directions[ReturnIntRandom(0, 3)];
	enemyDirectionAI2 = m_directions[ReturnIntRandom(0, 3)];
	enemyDirectionAI3 = m_directions[ReturnIntRandom(0, 1)];
	enemyDirectionAI4 = m_directions[ReturnIntRandom(2, 3)];

	//OPEN SPACES AVAILABLE
	for (int i = 0; i < 30; i++)
	{
		for (int j = 0; j < 40; j++)
		{
			if (collisionMap[j][i] == EMPTY_TILE)
			{
				openSpaces.push_back(sf::Vector2f(j * 16, i * 16));
			}
		}
	}
	
	// PLAYER INIT
	m_player.init(m_context->m_assets->getTexture(PLAYER));
	m_player.m_bomb.init(m_context->m_assets->getTexture(BOMB_TRIGGER));
	prevPosiition = m_player.getPosition();

	//AI INIT
	m_enemyAI1.setPosition(sf::Vector2f(241,176));
	m_enemyAI2.setPosition(sf::Vector2f(384, 288));
	m_enemyAI3.setPosition(sf::Vector2f(560, 208));
	m_enemyAI4.setPosition(sf::Vector2f(304,448));

	enemyPrevPosition1 = m_enemyAI1.getPosition();
	enemyPrevPosition2 = m_enemyAI2.getPosition();
	enemyPrevPosition3 = m_enemyAI3.getPosition();
	enemyPrevPosition4 = m_enemyAI4.getPosition();

	m_enemyAI1.init(m_context->m_assets->getTexture(ENEMY3));
	m_enemyAI2.init(m_context->m_assets->getTexture(ENEMY3));
	m_enemyAI3.init(m_context->m_assets->getTexture(ENEMY2));
	m_enemyAI4.init(m_context->m_assets->getTexture(ENEMY2));

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
	//float countSpeed = 16.0f;
	sf::Event event;
	while (m_context->m_window->pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
		{
			m_context->m_window->close();

			break;
		}
		case sf::Event::KeyPressed:
		{
			switch (event.key.code)
			{
			case sf::Keyboard::Up:
			{
				m_playerDirection = { 0.0f, -1 };
			}
			break;
			case sf::Keyboard::Down:
			{
				m_playerDirection = { 0.0f, 1 };
			}
			break;
			case sf::Keyboard::Left:
			{
				m_playerDirection = { -1, 0.0f };
			}
			break;
			case sf::Keyboard::Right:
			{
				m_playerDirection = { 1, 0.0f };
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
					m_player.m_isBombPlaced = true;
				}
			}
			default:
				break;
			}
			break;
		}
		case sf::Event::KeyReleased:
		{
			switch (event.key.code)
			{
			case sf::Keyboard::Up:
			{
				if (m_playerDirection.y < 0.f)
					m_playerDirection.y = 0.f;// (m_playerDirection.y == -1.f) ? 0.f : m_playerDirection.y;
				break;
			}
			case sf::Keyboard::Down:
			{
				if (m_playerDirection.y > 0.f)
					m_playerDirection.y = 0.f;// (m_playerDirection.y == 1.f) ? 0.f : m_playerDirection.y;
				break;
			}
			case sf::Keyboard::Left:
			{
				if (m_playerDirection.x < 0.f)
					m_playerDirection.x = 0.f; // (m_playerDirection.x == -1.f) ? 0.f : m_playerDirection.x;
				break;
			}
			case sf::Keyboard::Right:
			{
				if (m_playerDirection.x > 0.f)
					m_playerDirection.x = 0.f; // (m_playerDirection.x == 1.f) ? 0.f : m_playerDirection.x;
				break;
			}
			default:
				break;
			}
			break;
		}
		break;

		default:
			break;
		}
	}
}

void GamePlay::update(sf::Time deltaTime)
{
	if (!m_isPaused)
	{
		m_changeDirectionTime += deltaTime;
		m_elapsedTime += deltaTime;
		m_elaspedTimeForEnemy += deltaTime;

		m_player.update(m_playerDirection, deltaTime);
		if (checkCollision1(m_player.getPosition()))
			m_player.setPosition(prevPosiition);
		prevPosiition = m_player.getPosition();




		if (m_elapsedTime.asSeconds() > 1.0)
		{
			m_time--;
			m_timerText.setString("Time : " + std::to_string(m_time));
			m_elapsedTime = sf::Time::Zero;
		}
		if (m_player.m_isBombPlaced)
		{
			sf::Vector2i bombPos = sf::Vector2i((int)((m_player.m_bombPos.x + 8)/ 16) * 16, (int)( (m_player.m_bombPos.y +8) / 16) * 16);
			m_player.m_bomb.update(sf::Vector2f(bombPos), deltaTime);

			if (m_player.m_bomb.isBlasted())
			{
				

				removeWalls(m_player.m_bomb.getPosition(),3);
				//explosions(m_player.m_bomb.getPosition(), 1);
				blastBool = true;
				m_player.m_isBombPlaced = false;
				m_player.m_bomb.setIsBlasted(false);
				m_player.m_bomb.setPosition(sf::Vector2f(640, 400));
				for (auto& explosionSprite : m_explosions)
				{
					if (m_player.playerCollisionIsOn(explosionSprite))
					{
						std::cout << "True" << std::endl;
						m_lives--;
						m_livesText.setString("Lives : " + std::to_string(m_lives));
						break;
					}
				}
			}
		}
		// explosion clear
		if (blastBool)
		{
			blastTime += deltaTime;
		}
		
		if (blastTime.asSeconds() > 0.25)
		{
			blastBool = false;
			m_explosions.clear();
			blastTime = sf::Time::Zero;
		}
			

		
		

		//if (m_elaspedTimeForEnemy.asSeconds() > 0.4)
		{
			if (m_changeDirectionTime.asSeconds() >= 4.0)
			{
				enemyDirectionAI1 = m_directions[ReturnIntRandom(0, 3)];
				enemyDirectionAI2 = m_directions[ReturnIntRandom(0, 3)];
				enemyDirectionAI3 = m_directions[ReturnIntRandom(0, 1)];
				enemyDirectionAI4 = m_directions[ReturnIntRandom(2, 3)];
				m_changeDirectionTime = sf::Time::Zero;
			}
			if (checkCollision2(m_enemyAI1.getPosition()))
			{
				m_enemyAI1.setPosition(enemyPrevPosition1);
				enemyDirectionAI1 = -enemyDirectionAI1;
			}

			if (checkCollision2(m_enemyAI2.getPosition()))
			{
				m_enemyAI2.setPosition(enemyPrevPosition2);
				enemyDirectionAI2 = -enemyDirectionAI2;
			}

			if (checkCollision2(m_enemyAI3.getPosition()))
			{
				m_enemyAI3.setPosition(enemyPrevPosition3);
				enemyDirectionAI3 = -enemyDirectionAI3;
			}

			if (checkCollision2(m_enemyAI4.getPosition()))
			{
				m_enemyAI4.setPosition(enemyPrevPosition4);
				enemyDirectionAI4 = -enemyDirectionAI4;
			}
			m_enemyAI1.update(enemyDirectionAI1, deltaTime);
			m_enemyAI2.update(enemyDirectionAI2, deltaTime);
			m_enemyAI3.update(enemyDirectionAI3, deltaTime);
			m_enemyAI4.update(enemyDirectionAI4, deltaTime);

			m_elaspedTimeForEnemy = sf::Time::Zero;
		}

		

		enemyPrevPosition1 = m_enemyAI1.getPosition();
		enemyPrevPosition2 = m_enemyAI2.getPosition();
		enemyPrevPosition3 = m_enemyAI3.getPosition();
		enemyPrevPosition4 = m_enemyAI4.getPosition();
		if (m_lives <= 0 || m_time < 0)
		{
			m_context->m_states->add(std::make_unique<GameOver>(m_context));
		}

	}
}

void GamePlay::draw()
{
	m_context->m_window->clear();
	m_context->m_window->draw(m_gameMap);

	// use std::vector<std::pair<sf::Sprite, int>> breakableTiles
	m_allWalls.clear();
	for (int i = 0; i < 30; i++)
	{
		for (int j = 0; j < 40; j++)
		{
			if (collisionMap[i][j] == BREAKABLE_TILE)
			{
				sf::Sprite breakabletile;
				breakabletile.setTexture(m_context->m_assets->getTexture(BREAKABLE));
				breakabletile.setPosition(sf::Vector2f(j * 16, i * 16));
				m_allWalls.push_back(breakabletile);
			}
		}
	}

	for (auto& walls : m_allWalls)
	{
		m_context->m_window->draw(walls);
	}

	for (auto& walls : m_VWalls)
	{
		m_context->m_window->draw(walls);

	}
	for (auto& walls : m_HWalls)
	{
		m_context->m_window->draw(walls);

	}

	for (auto& walls : m_innerCompartmentWalls)
	{
		m_context->m_window->draw(walls);

	}
	m_context->m_window->draw(m_player.m_bomb);
	
	for (auto& explo : m_explosions)
	{
		m_context->m_window->draw(explo);

	}
	
	m_context->m_window->draw(m_player);

	m_context->m_window->draw(m_enemyAI1);
	m_context->m_window->draw(m_enemyAI2);
	m_context->m_window->draw(m_enemyAI3);
	m_context->m_window->draw(m_enemyAI4);


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

bool GamePlay::checkCollision1(sf::Vector2f pos)
{
	for (int i = 0; i < 30; i++)
	{
		for (int j = 0; j < 40; j++)
		{
			if (collisionMap[i][j] == HORIZONTAL_WALL || collisionMap[i][j] == VERTICAL_WALL || collisionMap[i][j] == COLUMN_WALL || collisionMap[i][j] == BREAKABLE_TILE || collisionMap[i][j] == INNER_COMPARTMENT_WALL)
			{
				if (pos.x + 16 > j * 16 &&
					pos.x + 1 <= j * 16 + 14 &&
					pos.y + 16 > i * 16 &&
					pos.y + 1 <= i * 16 + 14)
				
					return true;
			}
		}
	}
	return false;
}

bool GamePlay::checkCollision2(sf::Vector2f pos)
{
	for (int i = 0; i < 30; i++)
	{
		for (int j = 0; j < 40; j++)
		{
			if (collisionMap[i][j] == HORIZONTAL_WALL || collisionMap[i][j] == VERTICAL_WALL || collisionMap[i][j] == COLUMN_WALL || collisionMap[i][j] == BREAKABLE_TILE)
			{
				if (pos.x + 16 > j * 16 &&
					pos.x + 1<= j * 16 + 16 &&
					pos.y + 16 > i * 16 &&
					pos.y + 1 <= i * 16 + 16)
					return true;
			}
		}
	}
	return false;
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

void GamePlay::removeWalls(sf::Vector2f pos, int radius)
{
	int x = pos.x / 16;
	int y = pos.y / 16;

	sf::Sprite center;
	center.setTexture(m_context->m_assets->getTexture(EXPLOSION_CENTER));
	center.setPosition(pos);
	m_explosions.push_back(center);

	sf::Sprite end[4];
	for (int i = 0; i < 4; i++)
	{
		end[i].setTexture(m_context->m_assets->getTexture(EXPLOSION_END));
	}

	//UPWARD
	for (int i = 1; i <= radius; i++)
	{
		if (collisionMap[y - i][x] == BREAKABLE_TILE)
		{
			collisionMap[y - i][x] = EMPTY_TILE;
			end[0].setPosition(sf::Vector2f(pos.x, pos.y - 16 * i));
			m_explosions.push_back(end[0]);
			std::cout << radius << "out of upward loop" << i << std::endl;
			break;
		}
		else if (collisionMap[y - i][x] == HORIZONTAL_WALL || collisionMap[y - i][x] == VERTICAL_WALL || collisionMap[y - i][x] == COLUMN_WALL)
			break;
		else if (collisionMap[y - i][x] == EMPTY_TILE && i !=radius)
		{
			sf::Sprite sprite1;
			sprite1.setTexture(m_context->m_assets->getTexture(EXPLOSION_SIDE));
			sprite1.setPosition(sf::Vector2f(pos.x, pos.y - 16 * i));
			m_explosions.push_back(sprite1);
			std::cout << "upward loop 2nd last if" << i << std::endl;


		}
		else if (collisionMap[y - i][x] == EMPTY_TILE && i == radius)
		{
			end[0].setPosition(sf::Vector2f(pos.x, pos.y - 16 * radius));
			m_explosions.push_back(end[0]);
			std::cout << "upward loop last if" << i << std::endl;


		}
	}
	//DOWNWARD
	for (int i = 1; i <= radius; i++)
	{
		if (collisionMap[y + i][x] == BREAKABLE_TILE)
		{
			collisionMap[y + i][x] = EMPTY_TILE;
			end[1].setPosition(sf::Vector2f(pos.x, pos.y + 16 * i));
			end[1].setOrigin(8, 8);
			end[1].setRotation(180.0f);
			end[1].setOrigin(0, 0);
			end[1].setPosition(end[1].getPosition() + sf::Vector2f(16, 16));
			m_explosions.push_back(end[1]);

			break;
		}
		else if (collisionMap[y + i][x] == HORIZONTAL_WALL || collisionMap[y + i][x] == VERTICAL_WALL || collisionMap[y + i][x] == COLUMN_WALL)
			break;
		else if (collisionMap[y + i][x] == EMPTY_TILE && i != radius)
		{
			sf::Sprite sprite2;
			sprite2.setTexture(m_context->m_assets->getTexture(EXPLOSION_SIDE));
			sprite2.setPosition(sf::Vector2f(pos.x, pos.y + 16 * i));
			m_explosions.push_back(sprite2);

		}
		else if (collisionMap[y + i][x] == EMPTY_TILE && i == radius)
		{
			end[1].setPosition(sf::Vector2f(pos.x, pos.y + 16 * i));
			end[1].setOrigin(8, 8);
			end[1].setRotation(180.0f);
			end[1].setOrigin(0, 0);
			end[1].setPosition(end[1].getPosition() + sf::Vector2f(16, 16));
			m_explosions.push_back(end[1]);

		}
	}
	//LEFTWARD
	for (int i = 1; i <= radius; i++)
	{
		if (collisionMap[y ][x - i] == BREAKABLE_TILE)
		{
			collisionMap[y][x - i] = EMPTY_TILE;
			end[2].setPosition(sf::Vector2f(pos.x - 16 * i, pos.y));
			end[2].setOrigin(8, 8);
			end[2].setRotation(-90.0f);
			end[2].setOrigin(0, 0);
			end[2].setPosition(end[2].getPosition() + sf::Vector2f(0, 16));
			m_explosions.push_back(end[2]);

			break;
		}
		else if (collisionMap[y][x - i] == HORIZONTAL_WALL || collisionMap[y][x - i] == VERTICAL_WALL || collisionMap[y][x - i] == COLUMN_WALL)
			break;
		else if (collisionMap[y][x - i] == EMPTY_TILE && i != radius)
		{
			sf::Sprite sprite3;
			sprite3.setTexture(m_context->m_assets->getTexture(EXPLOSION_SIDE));
			sprite3.setPosition(sf::Vector2f(pos.x - 16 * i, pos.y));
			sprite3.setOrigin(8, 8);
			sprite3.setRotation(-90);
			sprite3.setOrigin(0, 0);
			sprite3.setPosition(sprite3.getPosition() + sf::Vector2f(0, 16));
			m_explosions.push_back(sprite3);

		}
		else if (collisionMap[y][x - i] == EMPTY_TILE && i == radius)
		{
			end[2].setPosition(sf::Vector2f(pos.x - 16 * i, pos.y));
			end[2].setOrigin(8, 8);
			end[2].setRotation(-90.0f);
			end[2].setOrigin(0, 0);
			end[2].setPosition(end[2].getPosition() + sf::Vector2f(0, 16));
			m_explosions.push_back(end[2]);

		}
	}

	//RIGHTWARD
	for (int i = 1; i <= radius; i++)
	{
		if (collisionMap[y][x + i] == BREAKABLE_TILE)
		{
			collisionMap[y][x + i] = EMPTY_TILE;
			end[3].setPosition(sf::Vector2f(pos.x + 16 * i, pos.y));
			end[3].setOrigin(8, 8);
			end[3].setRotation(90.0f);
			end[3].setOrigin(0, 0);
			end[3].setPosition(end[3].getPosition() + sf::Vector2f(16, 0));
			m_explosions.push_back(end[3]);

			break;
		}
		else if (collisionMap[y][x + i] == HORIZONTAL_WALL || collisionMap[y][x + i] == VERTICAL_WALL || collisionMap[y][x + i] == COLUMN_WALL)
			break;
		else if (collisionMap[y][x + i] == EMPTY_TILE && i != radius)
		{
			sf::Sprite sprite4;
			sprite4.setTexture(m_context->m_assets->getTexture(EXPLOSION_SIDE));
			sprite4.setPosition(sf::Vector2f(pos.x + 16 * i, pos.y));
			sprite4.setOrigin(8, 8);
			sprite4.setRotation(90);
			sprite4.setOrigin(0, 0);
			sprite4.setPosition(sprite4.getPosition() + sf::Vector2f(16, 0));
			m_explosions.push_back(sprite4);

		}
		else if (collisionMap[y][x + i] == EMPTY_TILE && i == radius)
		{
			end[3].setPosition(sf::Vector2f(pos.x + 16 * i, pos.y));
			end[3].setOrigin(8, 8);
			end[3].setRotation(90.0f);
			end[3].setOrigin(0, 0);
			end[3].setPosition(end[3].getPosition() + sf::Vector2f(16, 0));
			m_explosions.push_back(end[3]);

		}
	}

	
}
//REMOVE LATER
/*
void GamePlay::explosions(sf::Vector2f bombPos, int radius)
{
	sf::Sprite center;
	center.setTexture(m_context->m_assets->getTexture(EXPLOSION_CENTER));
	center.setPosition(bombPos);
	m_explosions.push_back(center);

	//i = 1 i < radius for middle piece
	for (int i = 1; i < radius; i++)
	{
		sf::Sprite sprite1;
		sprite1.setTexture(m_context->m_assets->getTexture(EXPLOSION_SIDE));
		sprite1.setPosition(sf::Vector2f(bombPos.x, bombPos.y - 16 * i));

		sf::Sprite sprite2;
		sprite2.setTexture(m_context->m_assets->getTexture(EXPLOSION_SIDE));
		sprite2.setPosition(sf::Vector2f(bombPos.x, bombPos.y + 16 * i));

		sf::Sprite sprite3;
		sprite3.setTexture(m_context->m_assets->getTexture(EXPLOSION_SIDE));
		sprite3.setPosition(sf::Vector2f(bombPos.x - 16 * i, bombPos.y));
		sprite3.setOrigin(8, 8);
		sprite3.setRotation(-90);
		sprite3.setOrigin(0, 0);
		sprite3.setPosition(sprite3.getPosition() + sf::Vector2f(0, 16));

		sf::Sprite sprite4;
		sprite4.setTexture(m_context->m_assets->getTexture(EXPLOSION_SIDE));
		sprite4.setPosition(sf::Vector2f(bombPos.x + 16 * i, bombPos.y));
		sprite4.setOrigin(8, 8);
		sprite4.setRotation(90);
		sprite4.setOrigin(0, 0);
		sprite4.setPosition(sprite4.getPosition() + sf::Vector2f(16, 0));

		m_explosions.push_back(sprite1);
		m_explosions.push_back(sprite2);
		m_explosions.push_back(sprite3);
		m_explosions.push_back(sprite4);

	}
	sf::Sprite end[4];
	for (int i = 0; i < 4; i++)
	{
		end[i].setTexture(m_context->m_assets->getTexture(EXPLOSION_END));
	}

	end[0].setPosition(sf::Vector2f(bombPos.x, bombPos.y - 16 * radius));

	end[1].setPosition(sf::Vector2f(bombPos.x, bombPos.y + 16 * radius));
	end[1].setOrigin(8, 8);
	end[1].setRotation(180.0f);
	end[1].setOrigin(0, 0);
	end[1].setPosition(end[1].getPosition() + sf::Vector2f(16, 16));

	end[2].setPosition(sf::Vector2f(bombPos.x - 16 * radius, bombPos.y));
	end[2].setOrigin(8, 8);
	end[2].setRotation(-90.0f);
	end[2].setOrigin(0, 0);
	end[2].setPosition(end[2].getPosition() + sf::Vector2f(0, 16));

	end[3].setPosition(sf::Vector2f(bombPos.x + 16 * radius, bombPos.y));
	end[3].setOrigin(8, 8);
	end[3].setRotation(90.0f);
	end[3].setOrigin(0, 0);
	end[3].setPosition(end[3].getPosition() + sf::Vector2f(16, 0));

	m_explosions.push_back(end[0]);
	m_explosions.push_back(end[1]);
	m_explosions.push_back(end[2]);
	m_explosions.push_back(end[3]);
}*/
