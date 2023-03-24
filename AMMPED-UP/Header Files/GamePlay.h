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

enum CMapTile
{
	EMPTY_TILE = 0,
	WALL_TILE,				//	1 in array
	BREAKABLE_TILE,			//	2 in array
	BREAKABLE_TILE_V2,		//	3 in array
	VERTICAL_WALL,
	HORIZONTAL_WALL,
	COLUMN_WALL,
	INNER_COMPARTMENT_WALL
};

class GamePlay : public am::State
{
private:
	std::shared_ptr<Context> m_context;
	sf::Sprite m_grass;
	sf::Sprite m_food;
	Player m_player;

	Enemy m_enemyAI1; // RANDOM AI
	Enemy m_enemyAI2; // RANDOM AI
	Enemy m_enemyAI3; // RANDOM AI HORIZONTAL
	Enemy m_enemyAI4; // RANDOM AI HORIZONTAL

	sf::Vector2f enemyAI1Dir;
	sf::Vector2f enemyAI2Dir;
	sf::Vector2f enemyAI3Dir;
	sf::Vector2f enemyAI4Dir;

	sf::Vector2f enemyDirectionAI1;
	sf::Vector2f enemyDirectionAI2;
	sf::Vector2f enemyDirectionAI3;
	sf::Vector2f enemyDirectionAI4;

	sf::Vector2f enemyPrevPosition1;
	sf::Vector2f enemyPrevPosition2;
	sf::Vector2f enemyPrevPosition3;
	sf::Vector2f enemyPrevPosition4;


	sf::Time m_changeDirectionTime;
	sf::Time m_elaspedTimeForEnemy;

	std::vector<std::pair<sf::Sprite, int>> pairTile;

	std::vector<sf::Sprite> m_allWalls;
	std::vector<sf::Sprite> m_VWalls;
	std::vector<sf::Sprite> m_HWalls;
	std::vector<sf::Sprite> m_innerCompartmentWalls;


	int collisionMap[30][40] = {
		{4, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 4, },
		{4, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 4, },
		{4, 0, 61, 62, 61, 62, 2, 2, 61, 62, 0, 0, 61, 62, 2, 0, 61, 62, 0, 61, 62, 0, 6, 6, 2, 2, 6, 6, 0, 0, 6, 6, 0, 2, 6, 6, 6, 6, 0, 4, },
		{4, 0, 63, 64, 63, 64, 0, 0, 63, 64, 0, 0, 63, 64, 0, 0, 63, 64, 0, 63, 64, 0, 6, 6, 0, 0, 6, 6, 0, 2, 6, 6, 0, 0, 6, 6, 6, 6, 0, 4, },
		{4, 0, 61, 62, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 2, 2, 0, 2, 0, 0, 0, 2, 2, 0, 0, 0, 2, 2, 0, 0, 2, 2, 0, 0, 6, 6, 0, 4, },
		{4, 0, 63, 64, 2, 0, 2, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 2, 0, 2, 0, 0, 0, 0, 2, 0, 0, 0, 0, 2, 0, 0, 6, 6, 0, 4, },
		{4, 2, 2, 0, 2, 0, 2, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 2, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 4, },
		{4, 2, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 2, 0, 2, 2, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 2, 2, 2, 0, 2, 2, 0, 0, 2, 2, 4, },
		{4, 0, 6, 6, 0, 0, 0, 0, 6, 6, 6, 6, 0, 0, 0, 2, 0, 0, 2, 2, 0, 0, 0, 0, 0, 2, 2, 0, 6, 6, 6, 6, 0, 0, 2, 0, 6, 6, 0, 4, },
		{4, 0, 6, 6, 2, 2, 0, 0, 6, 6, 6, 6, 0, 0, 0, 0, 0, 0, 0, 2, 0, 2, 2, 2, 0, 0, 2, 2, 6, 6, 6, 6, 0, 0, 2, 2, 6, 6, 0, 4, },
		{4, 0, 0, 0, 2, 0, 0, 0, 6, 6, 6, 6, 0, 0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0, 0, 6, 6, 6, 6, 0, 0, 0, 0, 0, 0, 0, 4, },
		{4, 0, 0, 0, 0, 2, 2, 2, 6, 6, 6, 6, 2, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 6, 6, 6, 6, 0, 0, 2, 0, 0, 0, 0, 4, },
		{4, 0, 6, 6, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 2, 0, 0, 0, 0, 2, 2, 6, 6, 0, 4, },
		{4, 0, 6, 6, 2, 0, 0, 0, 2, 2, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 2, 2, 0, 0, 2, 2, 0, 0, 6, 6, 0, 4, },
		{4, 2, 2, 0, 2, 0, 0, 0, 2, 0, 0, 6, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 6, 0, 0, 0, 0, 2, 0, 0, 0, 2, 2, 4, },
		{4, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 6, 0, 0, 2, 0, 0, 0, 0, 0, 0, 2, 4, },
		{4, 0, 6, 6, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 2, 2, 0, 0, 2, 2, 0, 0, 0, 0, 6, 6, 0, 4, },
		{4, 0, 6, 6, 2, 0, 0, 2, 2, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 2, 2, 0, 0, 0, 0, 2, 2, 0, 0, 6, 6, 0, 4, },
		{4, 2, 2, 0, 0, 0, 0, 0, 6, 6, 6, 6, 2, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 6, 6, 6, 6, 2, 0, 0, 0, 2, 0, 2, 4, },
		{4, 0, 2, 2, 0, 0, 0, 0, 6, 6, 6, 6, 2, 0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0, 0, 6, 6, 6, 6, 0, 0, 0, 0, 0, 2, 0, 4, },
		{4, 0, 6, 6, 0, 2, 0, 0, 6, 6, 6, 6, 2, 0, 0, 0, 2, 2, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 6, 6, 6, 6, 0, 0, 0, 0, 6, 6, 0, 4, },
		{4, 0, 6, 6, 2, 0, 0, 0, 6, 6, 6, 6, 0, 0, 0, 0, 0, 2, 0, 2, 2, 0, 0, 0, 0, 2, 0, 0, 6, 6, 6, 6, 2, 2, 2, 0, 6, 6, 0, 4, },
		{4, 0, 0, 2, 0, 0, 0, 0, 2, 0, 0, 2, 2, 0, 2, 2, 0, 0, 0, 2, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 2, 2, 4, },
		{4, 2, 2, 0, 0, 0, 0, 2, 2, 0, 0, 2, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 2, 2, 0, 0, 0, 2, 2, 0, 4, },
		{4, 0, 6, 6, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 2, 2, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 6, 6, 0, 4, },
		{4, 0, 6, 6, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 2, 0, 0, 2, 0, 0, 2, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 6, 6, 0, 4, },
		{4, 0, 6, 6, 6, 6, 0, 2, 6, 6, 2, 2, 6, 6, 2, 2, 6, 6, 2, 6, 6, 0, 6, 6, 0, 2, 6, 6, 0, 0, 6, 6, 0, 2, 6, 6, 6, 6, 0, 4, },
		{4, 0, 6, 6, 6, 6, 2, 2, 6, 6, 0, 0, 6, 6, 0, 0, 6, 6, 0, 6, 6, 0, 6, 6, 0, 0, 6, 6, 2, 2, 6, 6, 2, 2, 6, 6, 6, 6, 0, 4, },
		{4, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 4, },
		{5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, }

	};

	sf::Sprite m_gameMap;

	std::vector<sf::Vector2f> openSpaces;
	
	
	std::vector<sf::Vector2f> m_directions;

	sf::Vector2f m_playerDirection;
	sf::Time m_elapsedTime;

	sf::Text m_timerText;
	int m_time = 100;

	sf::Text m_scoreText;
	int m_score;

	sf::Text m_livesText;
	int m_lives;

	bool m_isPaused;

	sf::Sound m_foodEatSfx;
	sf::Music& m_inGame;

	std::vector<sf::Sprite> m_explosions;

	//used for explosions remove
	sf::Time blastTime;
	bool blastBool;
	sf::Vector2f prevPosiition;

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
	void removeWalls(sf::Vector2f pos, int radius);
	void explosions(sf::Vector2f bombPos, int radius);
	void takeScreenshot(const std::string& filename);
};