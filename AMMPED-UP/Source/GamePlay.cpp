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
Enemy& getEnemyValue(std::list<Enemy>& _list, int _index) {
	auto it = _list.begin();
	std::advance(it, _index);
	return *it;
}

GamePlay::GamePlay(std::shared_ptr<Context>& context) :
	m_context(context),
	m_playerDirection(0.0f, 0.0f),
	m_elapsedTime(sf::Time::Zero),
	m_score(0),
	m_lives(3),
	m_isPaused(false),
	m_damageCounter(false),
	blastBool(false),
	m_inGame(m_context->m_assets->getSoundTrack(IN_GAME_SOUND_TRACK)),
	gui(*m_context->m_window),
	m_enemies(6),
	m_coins(75)
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
	m_context->m_assets->addTextures(GAME_BACKGROUND, "Resources/assets/bombmap1.png");

	m_context->m_assets->addTextures(PLAYER, "Resources/assets/yellowPlayer.png");
	m_context->m_assets->addTextures(ENEMY1, "Resources/assets/enemy1.png");
	m_context->m_assets->addTextures(ENEMY2, "Resources/assets/enemy2.png");
	m_context->m_assets->addTextures(ENEMY3, "Resources/assets/enemy3.png");
	m_context->m_assets->addTextures(BREAKABLE_WALL_TEXTURE, "Resources/assets/breakable.png");
	m_context->m_assets->addTextures(VERTICAL_WALL_TEXTURE, "Resources/assets/verticalWall.png");
	m_context->m_assets->addTextures(HORIZONTAL_WALL_TEXTURE, "Resources/assets/HorizontalWall.png");
	m_context->m_assets->addTextures(INNER_COMPARTMENT_WALL_TEXTURE, "Resources/assets/innerWall.png");
	m_context->m_assets->addTextures(COLUMN_WALL_TEXTURE, "Resources/assets/columnWall.png");
	m_context->m_assets->addTextures(HEART_UI, "Resources/assets/heart.png");
	m_context->m_assets->addTextures(BOMB_TRIGGER, "Resources/assets/bombTileset.png");
	m_context->m_assets->addTextures(COIN, "Resources/assets/Coins.png");
	m_context->m_assets->addTextures(POWERUPS, "Resources/assets/PowerUps.png");
	m_context->m_assets->addTextures(EXPLOSION_SPRITE, "Resources/assets/explosionSprite.png");

	//GAME MAP
	//m_context->m_assets->addTextures(MENU_BACKGROUND, "Resources/assets/bombmap.png");
	m_gameMap.setTexture(m_context->m_assets->getTexture(GAME_BACKGROUND));
	m_gameMap.setPosition(m_context->m_window->getSize().x / 2, m_context->m_window->getSize().y / 2);
	m_gameMap.setOrigin(sf::Vector2f(m_gameMap.getTexture()->getSize().x / 2, m_gameMap.getTexture()->getSize().y / 2));
	m_gameMap.setScale({ 2,2 });

	//TILESET SETUP
	for (int i = 0; i < 30; i++)
	{
		for (int j = 0; j < 40; j++)
		{

			if (collisionMap[i][j] == BREAKABLE_TILE)
			{
				sf::Sprite breakabletile;
				breakabletile.setTexture(m_context->m_assets->getTexture(BREAKABLE_WALL_TEXTURE));
				breakabletile.setPosition(sf::Vector2f( j * 32, i * 32 ));
				breakabletile.setScale({ 2,2 });
				m_breakableWalls.push_back(breakabletile);

				//pairTile.push_back(std::make_pair(breakabletile, BREAKABLE_TILE));
			}
			if (collisionMap[i][j] == VERTICAL_WALL_TILE)
			{
				sf::Sprite vWall;
				vWall.setTexture(m_context->m_assets->getTexture(VERTICAL_WALL_TEXTURE));
				vWall.setScale({ 2,2 });

				vWall.setPosition(sf::Vector2f(j * 32, i * 32));
				m_VWalls.push_back(vWall);
			}

			if (collisionMap[i][j] == HORIZONTAL_WALL_TILE)
			{
				sf::Sprite hWall;
				hWall.setTexture(m_context->m_assets->getTexture(HORIZONTAL_WALL_TEXTURE));
				hWall.setScale({ 2,2 });
				hWall.setPosition(sf::Vector2f(j * 32, i * 32));
				m_HWalls.push_back(hWall);
			}
			if (collisionMap[i][j] == INNER_COMPARTMENT_WALL_TILE)
			{
				sf::Sprite iWall;
				iWall.setTexture(m_context->m_assets->getTexture(INNER_COMPARTMENT_WALL_TEXTURE));
				iWall.setScale({ 2,2 });
				iWall.setPosition(sf::Vector2f(j * 32, i * 32));
				m_innerCompartmentWalls.push_back(iWall);
			}
			if (collisionMap[i][j] == COLUMN_WALL1)
			{
				sf::Sprite cWall1;
				cWall1.setTexture(m_context->m_assets->getTexture(COLUMN_WALL_TEXTURE));
				cWall1.setTextureRect({ 0,0,16,16 });
				cWall1.setScale({ 2,2 });
				cWall1.setPosition(sf::Vector2f(j * 32, i * 32));
				m_columnWall.push_back(cWall1);
			}
			if (collisionMap[i][j] == COLUMN_WALL2)
			{
				sf::Sprite cWall2;
				cWall2.setTexture(m_context->m_assets->getTexture(COLUMN_WALL_TEXTURE));
				cWall2.setTextureRect({ 16,0,16,16 });
				cWall2.setScale({ 2,2 });
				cWall2.setPosition(sf::Vector2f(j * 32, i * 32));
				m_columnWall.push_back(cWall2);
			}
			if (collisionMap[i][j] == COLUMN_WALL3)
			{
				sf::Sprite cWall3;
				cWall3.setTexture(m_context->m_assets->getTexture(COLUMN_WALL_TEXTURE));
				cWall3.setTextureRect({ 32,0,16,16 });
				cWall3.setScale({ 2,2 });
				cWall3.setPosition(sf::Vector2f(j * 32, i * 32));
				m_columnWall.push_back(cWall3);
			}
			if (collisionMap[i][j] == COLUMN_WALL4)
			{
				sf::Sprite cWall4;
				cWall4.setTexture(m_context->m_assets->getTexture(COLUMN_WALL_TEXTURE));
				cWall4.setTextureRect({ 48,0,16,16 });
				cWall4.setScale({ 2,2 });
				cWall4.setPosition(sf::Vector2f(j * 32, i * 32));
				m_columnWall.push_back(cWall4);
			}
		}
	}

	//OPEN & BREAKABLE TILE SPACES AVAILABLE
	for (int i = 0; i < 30; i++)
	{
		for (int j = 0; j < 40; j++)
		{
			if (collisionMap[i][j] == EMPTY_TILE)
			{
				openSpaces.push_back(sf::Vector2f(j * 32, i * 32));
			}
			if (collisionMap[i][j] == BREAKABLE_TILE)
			{
				powerUPSpaces.push_back(sf::Vector2f(j * 32, i * 32));
			}
		}
	}
	
	// PLAYER INIT
	m_player.init(m_context->m_assets->getTexture(PLAYER));
	m_player.m_bomb.init(m_context->m_assets->getTexture(BOMB_TRIGGER));

	//AI INIT
	m_directions = { sf::Vector2f(0,-1), sf::Vector2f(0,1), sf::Vector2f(-1,0), sf::Vector2f(1,0) };

	getEnemyValue(m_enemies, 0).setDirection(m_directions[ReturnIntRandom(0, 3)]);
	getEnemyValue(m_enemies, 1).setDirection(m_directions[ReturnIntRandom(0, 3)]);
	getEnemyValue(m_enemies, 2).setDirection(m_directions[ReturnIntRandom(0, 1)]);
	getEnemyValue(m_enemies, 3).setDirection(m_directions[ReturnIntRandom(2, 3)]);
	getEnemyValue(m_enemies, 4).setDirection(m_directions[ReturnIntRandom(2, 3)]);
	getEnemyValue(m_enemies, 5).setDirection(m_directions[ReturnIntRandom(0, 1)]);
	
	getEnemyValue(m_enemies, 0).setPosition(sf::Vector2f(240 * 2, 176 * 2));
	getEnemyValue(m_enemies, 1).setPosition(sf::Vector2f(384 * 2, 288 * 2));
	getEnemyValue(m_enemies, 2).setPosition(sf::Vector2f(560 * 2, 208 * 2));
	getEnemyValue(m_enemies, 3).setPosition(sf::Vector2f(304 * 2, 448 * 2));
	getEnemyValue(m_enemies, 4).setPosition(sf::Vector2f(256 * 2, 16 * 2));
	getEnemyValue(m_enemies, 5).setPosition(sf::Vector2f(96 * 2, 192 * 2));

	getEnemyValue(m_enemies, 0).setPreviousPosition(getEnemyValue(m_enemies, 0).getPosition());
	getEnemyValue(m_enemies, 1).setPreviousPosition(getEnemyValue(m_enemies, 1).getPosition());
	getEnemyValue(m_enemies, 2).setPreviousPosition(getEnemyValue(m_enemies, 2).getPosition());
	getEnemyValue(m_enemies, 3).setPreviousPosition(getEnemyValue(m_enemies, 3).getPosition());
	getEnemyValue(m_enemies, 4).setPreviousPosition(getEnemyValue(m_enemies, 4).getPosition());
	getEnemyValue(m_enemies, 5).setPreviousPosition(getEnemyValue(m_enemies, 5).getPosition());
	
	getEnemyValue(m_enemies, 0).init(m_context->m_assets->getTexture(ENEMY1));
	getEnemyValue(m_enemies, 1).init(m_context->m_assets->getTexture(ENEMY1));
	getEnemyValue(m_enemies, 2).init(m_context->m_assets->getTexture(ENEMY2));
	getEnemyValue(m_enemies, 3).init(m_context->m_assets->getTexture(ENEMY2));
	getEnemyValue(m_enemies, 4).init(m_context->m_assets->getTexture(ENEMY3));
	getEnemyValue(m_enemies, 5).init(m_context->m_assets->getTexture(ENEMY3));
	

	// SCORE INIT
	m_scoreText.setFont(m_context->m_assets->getFont(MAIN_FONT));
	m_scoreText.setString("Score : " + std::to_string(m_score));
	m_scoreText.setPosition(2,-2);
	m_scoreText.setCharacterSize(30);
	m_scoreText.setFillColor(sf::Color::White);
	m_scoreText.setOutlineThickness(1);

	// TIMER INIT
	m_timerText.setFont(m_context->m_assets->getFont(MAIN_FONT));
	m_timerText.setString("Time : " + std::to_string(m_time));
	m_timerText.setPosition(m_context->m_window->getSize().x/2, -2);
	m_timerText.setCharacterSize(30);
	m_timerText.setFillColor(sf::Color::White);
	m_timerText.setOutlineThickness(1);

	// LIVES COUNT INIT
	m_livesText.setFont(m_context->m_assets->getFont(MAIN_FONT));
	m_livesText.setString(std::to_string(m_lives));
	m_livesText.setPosition(m_context->m_window->getSize().x - 234, -2);
	m_livesText.setCharacterSize(22);
	m_livesText.setFillColor(sf::Color::White);
	m_livesText.setOutlineThickness(1);

	m_livesHeartUI.setTexture(m_context->m_assets->getTexture(HEART_UI));
	m_livesHeartUI.setPosition(m_context->m_window->getSize().x - 240, 0);
	m_livesHeartUI.setScale({ 2,2 });

	progressBar = tgui::ProgressBar::create();
	progressBar->setPosition(m_context->m_window->getSize().x - 205, 5);
	progressBar->setSize(200, 20);
	progressBar->setMinimum(0);
	progressBar->setMaximum(100);
	progressBar->setValue(m_player.getHealth());
	gui.add(progressBar);

	// POWER UP INIT
	std::vector<bool> selectedIndicesPowerUP(powerUPSpaces.size(), false);
	for (int i = 0; i < powerUPSpaces.size()/3; i++)
	{
		PowerUPType type = static_cast<PowerUPType>(ReturnIntRandom(0, static_cast<int>(ICE_CREAM)));
		int randomIndex;
		do {
			randomIndex = ReturnIntRandom(0, powerUPSpaces.size() - 1);
		} while (selectedIndicesPowerUP[randomIndex]);
		selectedIndicesPowerUP[randomIndex] = true;
		sf::Vector2f pos = powerUPSpaces[randomIndex];
		PowerUP powerup;
		powerup.init(m_context->m_assets->getTexture(POWERUPS), pos, type);
		m_powerUPs.push_back(powerup);
	}
	
	//COINS INIT
	std::vector<bool> selectedIndicesCoins(openSpaces.size(), false);
	for (auto& i: m_coins)
	{
		int randomIndex;
		do {
			randomIndex = ReturnIntRandom(0, openSpaces.size() - 1);
		} while (selectedIndicesCoins[randomIndex]);
		selectedIndicesCoins[randomIndex] = true;
		sf::Vector2f pos = openSpaces[randomIndex];
		i.init(m_context->m_assets->getTexture(COIN));
		i.setPosition(sf::Vector2f(pos));
	}

	// SOUND EFFECT SETTINGS
	m_coinEatSfx.setBuffer(m_context->m_assets->getSoundEffect(COIN_SFX));
	m_coinEatSfx.setVolume(20);
	
	m_blastSFX.setBuffer(m_context->m_assets->getSoundEffect(BLAST_SFX));
	m_blastSFX.setVolume(80);

	m_damageSFX.setBuffer(m_context->m_assets->getSoundEffect(DAMAGE_SFX));
	m_damageSFX.setVolume(100);

	m_enemyDeathSFX.setBuffer(m_context->m_assets->getSoundEffect(ENEMY_DEATH_SFX));
	m_enemyDeathSFX.setVolume(100);
	//takeScreenshot("../Resources/assets/");
}

void GamePlay::processInput()
{
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
				break;
			}
			case sf::Keyboard::Down:
			{
				m_playerDirection = { 0.0f, 1 };
				break;
			}
			case sf::Keyboard::Left:
			{
				m_playerDirection = { -1, 0.0f };
				break;
			}
			case sf::Keyboard::Right:
			{
				m_playerDirection = { 1, 0.0f };
				break;
			}			
			case sf::Keyboard::Escape:
			{
				// INIT PAUSE STATE, ADD PAUSE STATE to m_states
				m_context->m_states->add(std::make_unique<PauseGame>(m_context));
				break;
			}
			case sf::Keyboard::Space:
			{
				if (!m_player.m_isBombPlaced)
				{
					m_player.m_bombPos = m_player.getPosition();
					m_player.m_isBombPlaced = true;
				}
				break;
			}
			//TEMPORARY DEBUGGIN TOOL
			/*case sf::Keyboard::P:
			{
				if (!showPowerUP)
					showPowerUP = true;
				else
					showPowerUP = false;
				break;
			}*/
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
		default:
			break;
		}
	}
}

void GamePlay::update(sf::Time deltaTime)
{
	if (!m_isPaused)
	{
		//ELASPED TIME FOR VARIOUS OPERATIONS
		m_changeDirectionTime += deltaTime;
		m_elapsedTime += deltaTime;

		//COIN ANIMATION UPDATE
		for (auto it = m_coins.begin(); it != m_coins.end(); it++)
		{
			it->update(deltaTime);
		}

		//PLAYER UPDATE AND COLLISION WITH WALLS
		m_player.update(m_playerDirection, deltaTime);
		if (checkCollision1(m_player.getPosition()))
		{
			m_player.setPosition(m_player.getPreviousPosition());
		}
		m_player.setPreviousPosition(m_player.getPosition());

		//COLLISION OF PLAYER WITH ENEMIES
		if (!m_inVulnerability)
		{
			for (auto& it : m_enemies)
			{
				if (checkCollision4(it.getPosition()))
				{
					m_damageSFX.play();
					m_damageCounter = true;
					m_player.setHealth(m_player.getHealth() - 20);
					m_inVulnerability = true;
					break;
				}
			}
		}

		//COINS COLLECTING
		for (auto it = m_coins.begin(); it != m_coins.end(); ++it) {
			if ((*it).playerIsOnCoin(m_player.getSprite())) {
				m_coinEatSfx.play();
				m_score += 5;
				it = m_coins.erase(it);
				if (it == m_coins.end()) {
					break;
				}
			}
		}
		//POWERUP COLLISION AND EFFECT APPLYING (CURRENT NUMBER OF POWERUP = 7)
		for(auto it = m_powerUPs.begin(); it != m_powerUPs.end(); ++it) {
			if ((*it).playerIsOnPowerUP(m_player.getPosition())) {
				applyPowerUPEffect(it->getType());
				it = m_powerUPs.erase(it);
				if (it == m_powerUPs.end()) {
					break;
				}
			}
		}

		//BOMB PLACEMENT & EXPLOSIONS
		if (m_player.m_isBombPlaced)
		{
			sf::Vector2i bombPos = sf::Vector2i((int)((m_player.m_bombPos.x + 8)/ 32) * 32, (int)( (m_player.m_bombPos.y +8) / 32) * 32);
			m_player.m_bomb.update(sf::Vector2f(bombPos), deltaTime);

			if (m_player.m_bomb.isBlasted())
			{
				m_blastSFX.play();
				int tempWall = removeWalls(m_player.m_bomb.getPosition(), m_radius);
				if (tempWall >= 1)
				{
					m_score += tempWall * 5;
				}

				blastBool = true;
				m_player.m_isBombPlaced = false;
				m_player.m_bomb.setIsBlasted(false);
				m_player.m_bomb.setPosition(sf::Vector2f(1280, 960));

				//COLLISION FOR PLAYER IN EXPLOSION OR NOT
				for (auto& explosionSprite : m_explosions)
				{
					if (checkCollision3(explosionSprite.getPosition()))
					{
						m_damageSFX.play();
						m_damageCounter = true;
						m_player.setHealth(m_player.getHealth() - 20);
						break;
					}
				}
				
				//COLLISION OF EXPLOSIONS WITH ENEMIES
				for (auto it = m_enemies.begin(); it!=m_enemies.end(); it++)
				{
					for (auto& explosionSprite : m_explosions)
					{
						if (checkCollision5(it->getPosition(), explosionSprite.getPosition()))
						{
							m_enemyDeathSFX.play();
							it = m_enemies.erase(it);
							if (it == m_enemies.end()) 
							{
								break;
							}
							break;
						}
					}
				}
				m_player.m_isBombPlaced = false;
			}
		}
		//PLAYER DAMAGE EFFEFCT - > BLINK EFFECT
		if (m_damageCounter)
		{
			m_playerDamageCounterTime += deltaTime;
		
			if (m_playerDamageCounterTime.asSeconds() > 0.2f)
			{
				if (m_player.getAlpha() == 255)
				{
					m_player.setPlayerColor(sf::Color(255, 255, 255, 0));
				}
				else
				{
					m_player.setPlayerColor(sf::Color(255, 255, 255, 255));
				}
				if (m_playerDamageCounterTime.asSeconds() >= 1.0f)
				{
					m_damageCounter = false;
					m_player.setPlayerColor(sf::Color(255, 255, 255, 255));
					m_playerDamageCounterTime = sf::Time::Zero;
				}
			}
		}
		// GETS RID OF THE EXPLOSION
		if (blastBool)
		{
			blastTime += deltaTime;
			if (blastTime.asSeconds() > 0.25)
			{
				blastBool = false;
				m_explosions.clear();
				blastTime = sf::Time::Zero;
			}
		}

		//CHANGE DIRECTION OF ENEMIES AFTER PARTICULAR AMOUNT OF TIME
		if (m_changeDirectionTime.asSeconds() >= 4.0)
		{
			for (auto it = m_enemies.begin(); it != m_enemies.end(); ++it)
			{
				it->setDirection(m_directions[ReturnIntRandom(0, 3)]);
				
			}
			m_changeDirectionTime = sf::Time::Zero;
		}
		//COLLISION OF ENEMIES WITH WALLS
		for (auto it = m_enemies.begin(); it != m_enemies.end(); ++it)
		{
			if (checkCollision2(it->getPosition()))
			{
				it->setPosition(it->getPreviousPosition());
				it->setDirection(-it->getDirection());
			}
			it->update(it->getDirection(), deltaTime);
			//PREVIOUS POSITION OF AI IS UPDATED TO CURRENT FOR COLLISION DETECTION
			it->setPreviousPosition(it->getPosition());
		}
		
		////THINGS TO BE UPDATED IN THE END////
		
		//STOP/DELAY THE ENEMY-PLAYER COLLISION FOR SOME TIME
		//IF REMOVED WILL RESULT INTO LOSING HEALTH AND DYING IN AN INSTANT 
		//DUE TO MULTIPLE COLLISIONS WITH ENEMY AT THE SAME TIME
		if (m_inVulnerability)
		{
			m_inVulnerabilityTime += deltaTime;
			if (m_inVulnerabilityTime.asSeconds() >= 1.5f)
			{
				m_inVulnerability = false;
				m_inVulnerabilityTime = sf::Time::Zero;
			}
		}
		if (m_elapsedTime.asSeconds() > 1.0)
		{
			m_time--;
			m_timerText.setString("Time : " + std::to_string(m_time));
			m_elapsedTime = sf::Time::Zero;
		}
		if (progressBar->getValue() <= 0)
		{
			m_lives--;
			m_player.setHealth(100);
			m_livesText.setString(std::to_string(m_lives));
		}
		if (m_lives <= 0 || m_time < 0)
		{
			m_context->m_states->add(std::make_unique<GameOver>(m_context));
		}
		m_scoreText.setString("Score : " + std::to_string(m_score));
		m_livesText.setString(std::to_string(m_lives));
		progressBar->setValue(m_player.getHealth());
	}
}

void GamePlay::draw()
{
	m_context->m_window->clear();
	
	//DRAW GAME MAP
	m_context->m_window->draw(m_gameMap);

	//CLEAR BREAKABLE VECTOR TO ADD ONLY TILES THAT ARE YET TO BREAK SO IT WILL DRAW ONLY THOSE
	m_breakableWalls.clear();
	for (int i = 0; i < 30; i++)
	{
		for (int j = 0; j < 40; j++)
		{
			if (collisionMap[i][j] == BREAKABLE_TILE)
			{
				sf::Sprite breakabletile;
				breakabletile.setTexture(m_context->m_assets->getTexture(BREAKABLE_WALL_TEXTURE));
				breakabletile.setScale({ 2,2 });
				breakabletile.setPosition(sf::Vector2f(j * 32, i * 32));
				m_breakableWalls.push_back(breakabletile);
			}
		}
	}
	//DRAW POWERUPS BEFORE BREAKABLE WALLS TO HIDE IT UNDER THEM
	if (!showPowerUP) {
		for (auto& powerup : m_powerUPs)
		{
			m_context->m_window->draw(powerup);
		}
	}
	for (auto& coin : m_coins)
	{
		m_context->m_window->draw(coin);
	}

	//DRAW BREAKABLE WALLS
	for (auto& walls : m_breakableWalls)
	{
		m_context->m_window->draw(walls);
	}
	//DRAW PERMANENT VERTICAL WALLS
	for (auto& walls : m_VWalls)
	{
		m_context->m_window->draw(walls);

	}
	//DRAW PERMANENT HORIZONTAL WALLS
	for (auto& walls : m_HWalls)
	{
		m_context->m_window->draw(walls);

	}
	//DRAW PERMANENT INNER ROOM WALLS
	for (auto& walls : m_innerCompartmentWalls)
	{
		m_context->m_window->draw(walls);

	}
	//DRAW PERMANENT COLUMN WALLS (LOOKS GREY/CEMENTED)
	for (auto& walls : m_columnWall)
	{
		m_context->m_window->draw(walls);

	}
	if (showPowerUP) {
		for (auto& powerup : m_powerUPs)
		{
			m_context->m_window->draw(powerup);
		}
	}
	//DRAW COINS
	for (auto it = m_coins.begin(); it!= m_coins.end(); it++)
	{
		m_context->m_window->draw(*it);
	}
	//DRAW BOMB
	if(m_player.m_isBombPlaced) m_context->m_window->draw(m_player.m_bomb);

	//DRAW EXPLOSION
	for (auto& explo : m_explosions)
	{
		m_context->m_window->draw(explo);

	}

	//PLAYER AND ENEMIES
	m_context->m_window->draw(m_player);
	for (auto it = m_enemies.begin(); it!= m_enemies.end(); ++it)
	{
		m_context->m_window->draw(*it);
	}
	
	//SCORE, TEXT & LIVES
	m_context->m_window->draw(m_scoreText);
	m_context->m_window->draw(m_timerText);
	m_context->m_window->draw(m_livesHeartUI);
	m_context->m_window->draw(m_livesText);
	gui.draw();
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

//COLLISION FOR PLAYER WITH WALLS
bool GamePlay::checkCollision1(sf::Vector2f pos) 
{
	/*for (auto& walls : m_breakableWalls)
	{
		if (m_player.playerCollisionIsOn(walls))
		{
			return true;
		}

	}
	for (auto& walls : m_VWalls)
	{
		if (m_player.playerCollisionIsOn(walls))
		{
			return true;
		}
	}
	for (auto& walls : m_HWalls)
	{
		if (m_player.playerCollisionIsOn(walls))
		{
			return true;
		}
	}
	for (auto& walls : m_innerCompartmentWalls)
	{
		if (m_player.playerCollisionIsOn(walls))
		{
			return true;
		}
	}
	for (auto& walls : m_columnWall)
	{
		if (m_player.playerCollisionIsOn(walls))
		{
			return true;
		}
	}*/

	for (int i = 0; i < 30; i++)
	{
		for (int j = 0; j < 40; j++)
		{
			if (collisionMap[i][j] == HORIZONTAL_WALL_TILE || collisionMap[i][j] == VERTICAL_WALL_TILE || collisionMap[i][j] == COLUMN_WALL1 || collisionMap[i][j] == COLUMN_WALL2 || collisionMap[i][j] == COLUMN_WALL3 || collisionMap[i][j] == COLUMN_WALL4 || collisionMap[i][j] == BREAKABLE_TILE || collisionMap[i][j] == INNER_COMPARTMENT_WALL_TILE)
			{
				if (pos.x + 28 > j * 32 + 1 &&
					pos.x + 1 <= j * 32 + 28 &&
					pos.y + 28 > i * 32 + 1 &&
					pos.y + 1 <= i * 32 + 28)
					return true;
			}
		}
	}
	return false;
}
//COLLISION FOR ENEMY AI WITH WALLS
bool GamePlay::checkCollision2(sf::Vector2f pos) 
{
	for (int i = 0; i < 30; i++)
	{
		for (int j = 0; j < 40; j++)
		{
			if (collisionMap[i][j] == HORIZONTAL_WALL_TILE || collisionMap[i][j] == VERTICAL_WALL_TILE || collisionMap[i][j] == COLUMN_WALL1 || collisionMap[i][j] == COLUMN_WALL2 || collisionMap[i][j] == COLUMN_WALL3 || collisionMap[i][j] == COLUMN_WALL4 || collisionMap[i][j] == BREAKABLE_TILE || collisionMap[i][j] == INNER_COMPARTMENT_WALL_TILE)
			{
				if (pos.x + 30 > j * 32 &&
					pos.x + 1 <= j * 32 + 32 &&
					pos.y + 30 > i * 32 &&
					pos.y + 1 <= i * 32 + 32)
					return true;
			}
		}
	}
	return false;
}

//PLAYER COLLISION WITH BOMB EXPLOSIONS 
bool GamePlay::checkCollision3(sf::Vector2f pos)
{
	if (m_player.getPosition().x + 28	> pos.x + 6 &&
		m_player.getPosition().x 	<= pos.x + 26 &&
		m_player.getPosition().y + 28	> pos.y + 6&&
		m_player.getPosition().y 	<= pos.y + 26)
	{
		return true;
	}
	return false;
}

//ENEMY AI AND PLAYER COLLISION
bool GamePlay::checkCollision4(sf::Vector2f pos)
{
	if (m_player.getPosition().x + 28 > pos.x + 6 &&
		m_player.getPosition().x <= pos.x + 26 &&
		m_player.getPosition().y + 28 > pos.y + 6 &&
		m_player.getPosition().y <= pos.y + 26)
	{
		return true;
	}
	return false;
}
//ENEMY AI & BOMB COLLISION
bool GamePlay::checkCollision5(sf::Vector2f enemyPos, sf::Vector2f bombPos)
{
	if (bombPos.x + 28	>	enemyPos.x + 2 &&
		bombPos.x + 1	<=	enemyPos.x + 28 &&
		bombPos.y + 28	>	enemyPos.y + 2 &&
		bombPos.y + 1	<=	enemyPos.y + 28)
	{
		return true;
	}
	return false;
}

// INDEX BASED TILE COLLISION FOR FRAMERATE DEPENDENT MOVEMENT
bool GamePlay::checkCollision(sf::Vector2f pos)
{
	int i = pos.x / 32;
	int j = pos.y / 32;
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

void GamePlay::applyPowerUPEffect(PowerUPType powerUPType)
{
	switch (powerUPType)
	{
	case HEART:
	{
		m_player.setHealth(progressBar->getMaximum());
	}
		break;
	case TIMER:
	{
		m_time += 25;
	}
		break;
	case SPEED: 
	{
		m_player.setVelocity(m_player.getVelocity() + 10);
		powerUpTime = true;
	}
		break;
	case LIVES:
	{
		m_lives += 1;
		m_livesText.setString(std::to_string(m_lives));
	}
		break;
	case EXPLOSION_RADIUS_INCREASE:
	{
		m_radius += 2;
	}
		break;
	case EXPLOSION_RADIUS_DECREASE:
	{
		if (m_radius >= 3)
		{
			m_radius -= 2;
		}
	}
		break;
	case ICE_CREAM:
		{
			m_score += 25;
			m_scoreText.setString("Score : " + std::to_string(m_score));
		}
		break;
	case APPLE:
	{
		if (m_player.getHealth() < progressBar->getMaximum())
		{
			m_player.setHealth(m_player.getHealth() + 10);
		}
	}
	default:
		break;
	}
}

//REMOVES THE WALLS THAT ARE IN EXPLOSION RADIUS AND RETURNS THE NUMBER OF EXPLODED WALLS FOR SCORE CALCULATION
int GamePlay::removeWalls(sf::Vector2f pos, int radius)
{
	int explodeTileCount = 0;
	int x = pos.x / 32;
	int y = pos.y / 32;

	sf::Sprite center;
	center.setTexture(m_context->m_assets->getTexture(EXPLOSION_SPRITE));
	center.setTextureRect({ 0,0,16,16 });
	center.setPosition(pos);
	center.setScale({ 2,2 });
	m_explosions.push_back(center);

	sf::Sprite end[4];
	for (int i = 0; i < 4; i++)
	{
		end[i].setTexture(m_context->m_assets->getTexture(EXPLOSION_SPRITE));
		end[i].setScale({ 2,2 });
	}
	//UPWARD
	for (int i = 1; i <= radius; i++)
	{
		if (collisionMap[y - i][x] == BREAKABLE_TILE)
		{
			collisionMap[y - i][x] = EMPTY_TILE;
			end[0].setTextureRect({ 16,0,16,16 });
			end[0].setPosition(sf::Vector2f(pos.x, pos.y - 32 * i));
			m_explosions.push_back(end[0]);
			explodeTileCount += 1;
			break;
		}
		else if (collisionMap[y - i][x] == HORIZONTAL_WALL_TILE || collisionMap[y - i][x] == VERTICAL_WALL_TILE || collisionMap[y - i][x] == COLUMN_WALL1 || collisionMap[y - i][x] == COLUMN_WALL2 || collisionMap[y - i][x] == COLUMN_WALL3 || collisionMap[y - i][x] == COLUMN_WALL4 || collisionMap[y - i][x] == INNER_COMPARTMENT_WALL_TILE)
			break;
		else if (collisionMap[y - i][x] == EMPTY_TILE && i !=radius)
		{
			sf::Sprite sprite1;
			sprite1.setTexture(m_context->m_assets->getTexture(EXPLOSION_SPRITE));
			sprite1.setTextureRect({ 80,0,16,16 });
			sprite1.setScale({ 2,2 });
			sprite1.setPosition(sf::Vector2f(pos.x, pos.y - 32 * i));
			m_explosions.push_back(sprite1);
		}
		else if (collisionMap[y - i][x] == EMPTY_TILE && i == radius)
		{
			end[0].setTextureRect({ 16,0,16,16 });
			end[0].setPosition(sf::Vector2f(pos.x, pos.y - 32 * i));
			m_explosions.push_back(end[0]);
		}
	}
	//DOWNWARD
	for (int i = 1; i <= radius; i++)
	{
		if (collisionMap[y + i][x] == BREAKABLE_TILE)
		{
			collisionMap[y + i][x] = EMPTY_TILE;
			end[1].setTextureRect({ 64,0,16,16 });
			end[1].setPosition(sf::Vector2f(pos.x, pos.y + (32 * i)));
			m_explosions.push_back(end[1]);
			explodeTileCount += 1;
			break;
		}
		else if (collisionMap[y + i][x] == HORIZONTAL_WALL_TILE || collisionMap[y + i][x] == VERTICAL_WALL_TILE || collisionMap[y + i][x] == COLUMN_WALL1 || collisionMap[y + i][x] == COLUMN_WALL2 || collisionMap[y + i][x] == COLUMN_WALL3 || collisionMap[y + i][x] == COLUMN_WALL4 || collisionMap[y + i][x] == INNER_COMPARTMENT_WALL_TILE)
			break;
		else if (collisionMap[y + i][x] == EMPTY_TILE && i != radius)
		{
			sf::Sprite sprite2;
			sprite2.setTexture(m_context->m_assets->getTexture(EXPLOSION_SPRITE));
			sprite2.setTextureRect({112,0,16,16});
			sprite2.setPosition(sf::Vector2f(pos.x, pos.y + 32 * i));
			sprite2.setScale({ 2,2 });
			m_explosions.push_back(sprite2);
		}
		else if (collisionMap[y + i][x] == EMPTY_TILE && i == radius)
		{
			end[1].setTextureRect({ 64,0,16,16 });
			end[1].setPosition(sf::Vector2f(pos.x, pos.y + 32 * i));
			m_explosions.push_back(end[1]);
		}
	}
	//LEFTWARD
	for (int i = 1; i <= radius; i++)
	{
		if (collisionMap[y][x - i] == BREAKABLE_TILE)
		{
			collisionMap[y][x - i] = EMPTY_TILE;
			end[2].setTextureRect({ 32,0,16,16 });
			end[2].setPosition(sf::Vector2f(pos.x - 32 * i, pos.y));
			m_explosions.push_back(end[2]);
			explodeTileCount += 1;
			break;
		}
		else if (collisionMap[y][x - i] == HORIZONTAL_WALL_TILE || collisionMap[y][x - i] == VERTICAL_WALL_TILE || collisionMap[y][x - i] == COLUMN_WALL1 || collisionMap[y][x - i] == COLUMN_WALL2 || collisionMap[y][x - i] == COLUMN_WALL3 || collisionMap[y][x - i] == COLUMN_WALL4 || collisionMap[y][x - i] == INNER_COMPARTMENT_WALL_TILE)
			break;
		else if (collisionMap[y][x - i] == EMPTY_TILE && i != radius)
		{
			sf::Sprite sprite3;
			sprite3.setTexture(m_context->m_assets->getTexture(EXPLOSION_SPRITE));
			sprite3.setTextureRect({96, 0, 16, 16});
			sprite3.setPosition(sf::Vector2f(pos.x - 32 * i, pos.y));
			sprite3.setScale({ 2,2 });
			m_explosions.push_back(sprite3);
		}
		else if (collisionMap[y][x - i] == EMPTY_TILE && i == radius)
		{
			end[2].setTextureRect({ 32,0,16,16 });
			end[2].setPosition(sf::Vector2f(pos.x - 32 * i , pos.y));
			m_explosions.push_back(end[2]);
		}
	}
	//RIGHTWARD
	for (int i = 1; i <= radius; i++)
	{
		if (collisionMap[y][x + i] == BREAKABLE_TILE)
		{
			collisionMap[y][x + i] = EMPTY_TILE;
			end[3].setPosition(sf::Vector2f(pos.x + 32 * i, pos.y));
			end[3].setTextureRect({48,0,16,16});
			m_explosions.push_back(end[3]);
			explodeTileCount += 1;
			break;
		}
		else if (collisionMap[y][x + i] == HORIZONTAL_WALL_TILE || collisionMap[y][x + i] == VERTICAL_WALL_TILE || collisionMap[y][x + i] == COLUMN_WALL1 || collisionMap[y][x + i] == COLUMN_WALL2 || collisionMap[y][x + i] == COLUMN_WALL3 || collisionMap[y][x + i] == COLUMN_WALL4 || collisionMap[y][x + i] == INNER_COMPARTMENT_WALL_TILE)
			break;
		else if (collisionMap[y][x + i] == EMPTY_TILE && i != radius)
		{
			sf::Sprite sprite4;
			sprite4.setTexture(m_context->m_assets->getTexture(EXPLOSION_SPRITE));
			sprite4.setTextureRect({ 128,0,16,16 });
			sprite4.setScale({ 2,2 });
			sprite4.setPosition(sf::Vector2f(pos.x + 32 * i, pos.y));
			m_explosions.push_back(sprite4);
		}
		else if (collisionMap[y][x + i] == EMPTY_TILE && i == radius)
		{
			end[3].setTextureRect({ 48,0,16,16 });
			end[3].setPosition(sf::Vector2f(pos.x + 32 * i, pos.y));
			m_explosions.push_back(end[3]);
		}
	}
	return explodeTileCount;
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