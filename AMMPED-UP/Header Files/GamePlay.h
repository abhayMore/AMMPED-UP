#pragma once
#include <memory>
#include <vector>
#include <array>
#include <utility>

#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Text.hpp"
#include "SFML/Audio/Sound.hpp"
#include "../Header Files/Animation.h"
#include "TGUI/TGUI.hpp"

#include "Game.h"
#include "ScoreManager.h"
#include "State.h"
#include "Player.h"
#include "Enemy.h"
#include "PowerUP.h"
#include "Coin.h"
#include "AudioManager.h"

enum CMapTile
{
	EMPTY_TILE = 0,
	WALL_TILE,				//	1 in array
	BREAKABLE_TILE,			//	2 in array
	BREAKABLE_TILE_V2,		//	3 in array
	VERTICAL_WALL_TILE,
	HORIZONTAL_WALL_TILE,
	INNER_COMPARTMENT_WALL_TILE,
	COLUMN_WALL1 = 61,
	COLUMN_WALL2 = 62,
	COLUMN_WALL3 = 63,
	COLUMN_WALL4 = 64
};

class GamePlay : public am::State
{
private:
	std::shared_ptr<Context> m_context;
	Player m_player;
	std::list<Enemy> m_enemies;

	sf::Time m_changeDirectionTime;
	sf::Time m_inVulnerabilityTime;
	bool m_inVulnerability = false;

	//WALLS
	std::vector<sf::Sprite> m_breakableWalls;
	std::vector<sf::Sprite> m_VWalls;
	std::vector<sf::Sprite> m_HWalls;
	std::vector<sf::Sprite> m_innerCompartmentWalls;
	std::vector<sf::Sprite> m_columnWall;

	int collisionMap[30][40] = {
		{04, 05, 05, 05, 05, 05, 05, 05, 05, 05, 05, 05, 05, 05, 05, 05, 05, 05, 05, 05, 05, 05, 05, 05, 05, 05, 05, 05, 05, 05, 05, 05, 05, 05, 05, 05, 05, 05, 05, 04, },
		{04, 00, 00, 00, 00, 00, 02, 00, 00, 00, 00, 00, 00, 00, 02, 02, 00, 00, 00, 00, 00, 00, 00, 00, 00, 02, 00, 00, 00, 00, 00, 00, 02, 02, 00, 00, 00, 00, 00, 04, },
		{04, 00, 61, 62, 61, 62, 02, 02, 61, 62, 00, 00, 61, 62, 02, 00, 61, 62, 00, 61, 62, 00, 61, 62, 02, 02, 61, 62, 00, 00, 61, 62, 00, 02, 61, 62, 61, 62, 00, 04, },
		{04, 00, 63, 64, 63, 64, 00, 00, 63, 64, 00, 00, 63, 64, 00, 00, 63, 64, 00, 63, 64, 00, 63, 64, 00, 00, 63, 64, 00, 02, 63, 64, 00, 00, 63, 64, 63, 64, 00, 04, },
		{04, 00, 61, 62, 00, 00, 00, 00, 00, 02, 02, 00, 00, 00, 00, 00, 02, 02, 00, 02, 00, 00, 00, 02, 02, 00, 00, 00, 02, 02, 00, 00, 02, 02, 00, 00, 61, 62, 00, 04, },
		{04, 00, 63, 64, 02, 00, 02, 00, 00, 02, 00, 00, 00, 00, 00, 00, 00, 02, 02, 00, 00, 02, 00, 02, 00, 00, 00, 00, 02, 00, 00, 00, 00, 02, 00, 00, 63, 64, 00, 04, },
		{04, 02, 02, 00, 02, 00, 02, 00, 00, 00, 00, 02, 02, 00, 00, 00, 00, 00, 00, 00, 00, 02, 00, 02, 00, 00, 00, 02, 02, 00, 00, 00, 00, 00, 00, 00, 00, 00, 02, 04, },
		{04, 02, 00, 00, 00, 00, 02, 00, 00, 00, 00, 00, 02, 00, 02, 02, 00, 00, 00, 00, 00, 02, 02, 02, 00, 00, 00, 00, 00, 02, 02, 02, 00, 02, 02, 00, 00, 02, 02, 04, },
		{04, 00, 61, 62, 00, 00, 00, 00, 61, 62, 61, 62, 00, 00, 00, 02, 00, 00, 02, 02, 00, 00, 00, 00, 00, 02, 02, 00, 61, 62, 61, 62, 00, 00, 02, 00, 61, 62, 00, 04, },
		{04, 00, 63, 64, 02, 02, 00, 00, 63, 64, 63, 64, 00, 00, 00, 00, 00, 00, 00, 02, 00, 02, 02, 02, 00, 00, 02, 02, 63, 64, 63, 64, 00, 00, 02, 02, 63, 64, 00, 04, },
		{04, 00, 00, 00, 02, 00, 00, 00, 61, 62, 61, 62, 00, 00, 06, 06, 06, 06, 06, 06, 06, 06, 06, 06, 06, 06, 00, 00, 61, 62, 61, 62, 00, 00, 00, 00, 00, 00, 00, 04, },
		{04, 00, 00, 00, 00, 02, 02, 02, 63, 64, 63, 64, 02, 00, 06, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 06, 00, 00, 63, 64, 63, 64, 00, 00, 02, 00, 00, 00, 00, 04, },
		{04, 00, 61, 62, 00, 00, 00, 00, 00, 00, 00, 00, 02, 02, 06, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 06, 00, 00, 00, 02, 00, 00, 00, 00, 02, 02, 61, 62, 00, 04, },
		{04, 00, 63, 64, 02, 00, 00, 00, 02, 02, 00, 00, 00, 00, 06, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 06, 00, 00, 02, 02, 00, 00, 02, 02, 00, 00, 63, 64, 00, 04, },
		{04, 02, 02, 00, 02, 00, 00, 00, 02, 00, 00, 61, 62, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 61, 62, 00, 00, 00, 00, 02, 00, 00, 00, 02, 02, 04, },
		{04, 02, 00, 00, 00, 00, 00, 00, 00, 00, 00, 63, 64, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 63, 64, 00, 00, 02, 00, 00, 00, 00, 00, 00, 02, 04, },
		{04, 00, 61, 62, 02, 00, 00, 02, 02, 00, 00, 00, 00, 00, 06, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 06, 02, 02, 00, 00, 00, 00, 02, 02, 00, 00, 61, 62, 00, 04, },
		{04, 00, 63, 64, 02, 00, 00, 00, 00, 00, 00, 00, 00, 00, 06, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 06, 02, 02, 00, 00, 02, 02, 00, 00, 00, 00, 63, 64, 00, 04, },
		{04, 02, 02, 00, 00, 00, 00, 00, 61, 62, 61, 62, 02, 00, 06, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 06, 00, 00, 61, 62, 61, 62, 02, 00, 00, 00, 02, 00, 02, 04, },
		{04, 00, 02, 02, 00, 00, 00, 00, 63, 64, 63, 64, 02, 00, 06, 06, 06, 06, 06, 06, 06, 06, 06, 06, 06, 06, 00, 00, 63, 64, 63, 64, 00, 00, 00, 00, 00, 02, 00, 04, },
		{04, 00, 61, 62, 00, 02, 00, 00, 61, 62, 61, 62, 02, 00, 00, 00, 02, 02, 00, 00, 00, 02, 02, 02, 00, 00, 00, 00, 61, 62, 61, 62, 00, 00, 00, 00, 61, 62, 00, 04, },
		{04, 00, 63, 64, 02, 00, 00, 00, 63, 64, 63, 64, 00, 00, 00, 00, 00, 02, 00, 02, 02, 00, 00, 00, 00, 02, 00, 00, 63, 64, 63, 64, 02, 02, 02, 00, 63, 64, 00, 04, },
		{04, 00, 00, 02, 00, 00, 00, 00, 02, 00, 00, 02, 02, 00, 02, 02, 00, 00, 00, 02, 00, 00, 00, 00, 02, 02, 00, 00, 00, 00, 00, 02, 00, 00, 00, 00, 00, 02, 02, 04, },
		{04, 02, 02, 00, 00, 00, 00, 02, 02, 00, 00, 02, 00, 00, 00, 02, 02, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 02, 02, 00, 00, 02, 02, 00, 00, 00, 02, 02, 00, 04, },
		{04, 00, 61, 62, 02, 02, 02, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 02, 00, 02, 02, 00, 00, 00, 00, 00, 02, 00, 00, 00, 00, 00, 00, 00, 00, 61, 62, 00, 04, },
		{04, 00, 63, 64, 00, 00, 00, 00, 00, 00, 02, 00, 00, 00, 00, 02, 00, 00, 02, 00, 00, 02, 00, 00, 02, 02, 00, 00, 00, 00, 00, 00, 02, 00, 00, 00, 63, 64, 00, 04, },
		{04, 00, 61, 62, 61, 62, 00, 02, 61, 62, 02, 02, 61, 62, 02, 02, 61, 62, 02, 61, 62, 00, 61, 62, 00, 02, 61, 62, 00, 00, 61, 62, 00, 02, 61, 62, 61, 62, 00, 04, },
		{04, 00, 63, 64, 63, 64, 02, 02, 63, 64, 00, 00, 63, 64, 00, 00, 63, 64, 00, 63, 64, 00, 63, 64, 00, 00, 63, 64, 02, 02, 63, 64, 02, 02, 63, 64, 63, 64, 00, 04, },
		{04, 00, 00, 00, 00, 00, 00, 02, 00, 00, 00, 00, 00, 00, 00, 00, 02, 02, 02, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 02, 00, 00, 00, 02, 00, 00, 00, 00, 00, 04, },
		{05, 05, 05, 05, 05, 05, 05, 05, 05, 05, 05, 05, 05, 05, 05, 05, 05, 05, 05, 05, 05, 05, 05, 05, 05, 05, 05, 05, 05, 05, 05, 05, 05, 05, 05, 05, 05, 05, 05, 05, }

	};

	sf::Sprite m_gameMap;
	std::vector<sf::Vector2f> openSpaces;
	std::vector<sf::Vector2f> powerUPSpaces;
	std::vector<sf::Vector2f> m_directions;

	sf::Vector2f m_playerDirection;
	sf::Time m_elapsedTime;

	std::list<PowerUP> m_powerUPs;
	bool powerUpTime = false;

	sf::Text m_timerText;
	int m_time = 200;

	sf::Text m_scoreText;
	int m_currentScore;
	ScoreManager* m_scoreManager;

	std::string m_currentGameState; //WON, DIED, TIME's UP?
	bool m_shiftToGameOver;

	//PROGRESS BAR
	tgui::Theme m_theme;
	sf::Text m_livesText;
	int m_lives;
	sf::Sprite m_livesHeartUI;
	tgui::Gui gui;
	tgui::ProgressBar::Ptr progressBar;

	bool m_isPaused;

	//COINS
	std::list<Coin> m_coins;

	AudioManager* m_sound;

	//EXPLOSIONS 
	std::vector<sf::Sprite> m_explosions;

	//PLAYER DAMAGE TIMER 
	sf::Time m_playerDamageCounterTime;
	bool m_damageCounter;

	//used for explosions remove
	sf::Time blastTime;
	bool blastBool;
	int m_radius = 1;

	//DEBUGGING TOOL INFO
	bool showPowerUP = false;

public:
	GamePlay(std::shared_ptr<Context>& context);
	~GamePlay();

	void init() override;
	void processInput() override;
	void update(sf::Time deltaTime) override;

	void pause() override;
	void start() override;

	//Why so many funtions? every function has its own offsets depending upon what they are colliding to
	bool checkCollision1(sf::Vector2f pos);
	bool checkCollision2(sf::Vector2f pos);
	bool checkCollision3(sf::Vector2f pos);
	bool checkCollision4(sf::Vector2f pos);
	bool checkCollision5(sf::Vector2f enemyPos, sf::Vector2f bombPos);	

	bool checkCollision(sf::Vector2f pos);								//Index based tile collision 
	void applyPowerUPEffect(PowerUPType powerUPType);					//aplies the powerup to the players' attributes
	int removeWalls(sf::Vector2f pos, int radius);						//Returns count of removed walls for score update
	
	void draw() override;
	void takeScreenshot(const std::string& filename);
};