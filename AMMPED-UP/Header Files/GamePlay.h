#pragma once
#include <memory>
#include <array>
#include <utility>

#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Text.hpp"
#include "SFML/Audio/Sound.hpp"
#include "../Header Files/Animation.h"

#include "Game.h"
#include "State.h"
#include "Player.h"
#include "Enemy.h"
#include "PowerUP.h"

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

	Enemy m_enemyAI1; // RANDOM AI
	Enemy m_enemyAI2; // RANDOM AI
	Enemy m_enemyAI3; // RANDOM AI HORIZONTAL
	Enemy m_enemyAI4; // RANDOM AI HORIZONTAL
	Enemy m_enemyAI5; 
	Enemy m_enemyAI6;

	sf::Vector2f enemyAI1Dir;
	sf::Vector2f enemyAI2Dir;
	sf::Vector2f enemyAI3Dir;
	sf::Vector2f enemyAI4Dir;
	sf::Vector2f enemyAI5Dir;
	sf::Vector2f enemyAI6Dir;

	sf::Vector2f enemyDirectionAI1;
	sf::Vector2f enemyDirectionAI2;
	sf::Vector2f enemyDirectionAI3;
	sf::Vector2f enemyDirectionAI4;
	sf::Vector2f enemyDirectionAI5;
	sf::Vector2f enemyDirectionAI6;

	sf::Vector2f enemyPrevPosition1;
	sf::Vector2f enemyPrevPosition2;
	sf::Vector2f enemyPrevPosition3;
	sf::Vector2f enemyPrevPosition4;
	sf::Vector2f enemyPrevPosition5;
	sf::Vector2f enemyPrevPosition6;


	sf::Time m_changeDirectionTime;
	sf::Time m_elaspedTimeForEnemy;

	std::vector<std::pair<sf::Sprite, int>> pairTile;

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

	sf::Text m_livesText;
	int m_lives;
	sf::Sprite m_livesHeartUI;

	bool m_isPaused;

	sf::Sound m_foodEatSfx;
	sf::Music& m_inGame;

	std::vector<sf::Sprite> m_explosions;

	//used for explosions remove
	sf::Time blastTime;
	bool blastBool;
	int m_radius = 1;
	sf::Vector2f prevPosiition;

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
	bool checkCollision(sf::Vector2f pos);
	void applyPowerUPEffect(PowerUPType powerUPType);
	int removeWalls(sf::Vector2f pos, int radius); //returns count of removed walls
	void explosions(sf::Vector2f bombPos, int radius);
	void takeScreenshot(const std::string& filename);
};