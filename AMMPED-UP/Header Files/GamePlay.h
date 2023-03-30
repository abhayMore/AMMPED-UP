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
#include "State.h"
#include "Player.h"
#include "Enemy.h"
#include "PowerUP.h"
#include "Coin.h"

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
	sf::Time m_elaspedTimeForEnemy;
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
	int m_time = 100;

	sf::Text m_scoreText;
	int m_score;


	//PROGRESS BAR
	sf::Text m_livesText;
	int m_lives;
	sf::Sprite m_livesHeartUI;
	tgui::Gui gui;
	tgui::ProgressBar::Ptr progressBar;

	bool is_removed = false;;
	bool m_isPaused;

	//COINS
	std::list<Coin> m_coins;

	//SFX and MUSIC
	sf::Sound m_damageSFX;
	sf::Sound m_blastSFX;
	sf::Sound m_coinEatSfx;
	sf::Music& m_inGame;
	sf::Sound m_enemyDeathSFX;


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

	void draw() override;

	void pause() override;
	void start() override;

	bool checkCollision1(sf::Vector2f pos);
	bool checkCollision2(sf::Vector2f pos);
	bool checkCollision3(sf::Vector2f pos);
	bool checkCollision4(sf::Vector2f pos);
	bool checkCollision5(sf::Vector2f enemyPos, sf::Vector2f bombPos);

	bool checkCollision(sf::Vector2f pos);
	void applyPowerUPEffect(PowerUPType powerUPType);
	int removeWalls(sf::Vector2f pos, int radius); //returns count of removed walls
	
	//REMOVE LATER
	//void explosions(sf::Vector2f bombPos, int radius);
	void takeScreenshot(const std::string& filename);
};