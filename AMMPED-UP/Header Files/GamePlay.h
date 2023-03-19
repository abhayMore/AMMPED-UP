#pragma once
#include <memory>
#include <array>

#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Text.hpp"
#include "SFML/Audio/Sound.hpp"
#include "../Header Files/Animation.h"

#include "Game.h"
#include "State.h"
#include "Player.h"

enum CMapTile
{
	EMPTY_TILE = 0,		
	WALL_TILE,				//	1 in array
	BREAKABLE_TILE,			//	2 in array
	BREAKABLE_TILE_V2		//	3 in array
	
};

class GamePlay : public am::State
{
private:
	std::shared_ptr<Context> m_context;
	sf::Sprite m_grass;
	sf::Sprite m_food;
	std::array<sf::Sprite, 4> m_walls;
	Player m_player;

	std::vector<sf::Sprite> m_breakableTiles;

	int collisionMap[30][40] = {
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, },
		{1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 1, },
		{1, 0, 1, 1, 1, 1, 2, 2, 1, 1, 0, 0, 1, 1, 2, 0, 1, 1, 0, 1, 1, 0, 1, 1, 2, 2, 1, 1, 0, 0, 1, 1, 0, 2, 1, 1, 1, 1, 0, 1, },
		{1, 0, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 2, 1, 1, 0, 0, 1, 1, 1, 1, 0, 1, },
		{1, 0, 1, 1, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 2, 2, 0, 2, 0, 0, 0, 2, 2, 0, 0, 0, 2, 2, 0, 0, 2, 2, 0, 0, 1, 1, 0, 1, },
		{1, 0, 1, 1, 2, 0, 2, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 2, 0, 2, 0, 0, 0, 0, 2, 0, 0, 0, 0, 2, 0, 0, 1, 1, 0, 1, },
		{1, 2, 2, 0, 2, 0, 2, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 2, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 1, },
		{1, 2, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 2, 0, 2, 2, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 2, 2, 2, 0, 2, 2, 0, 0, 2, 2, 1, },
		{1, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 2, 0, 0, 2, 2, 0, 0, 0, 0, 0, 2, 2, 0, 1, 1, 1, 1, 0, 0, 2, 0, 1, 1, 0, 1, },
		{1, 0, 1, 1, 2, 2, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 2, 0, 2, 2, 2, 0, 0, 2, 2, 1, 1, 1, 1, 0, 0, 2, 2, 1, 1, 0, 1, },
		{1, 0, 0, 0, 2, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, },
		{1, 0, 0, 0, 0, 2, 2, 2, 1, 1, 1, 1, 2, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 0, 0, 2, 0, 0, 0, 0, 1, },
		{1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 2, 0, 0, 0, 0, 2, 2, 1, 1, 0, 1, },
		{1, 0, 1, 1, 2, 0, 0, 0, 2, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 2, 2, 0, 0, 2, 2, 0, 0, 1, 1, 0, 1, },
		{1, 2, 2, 0, 2, 0, 0, 0, 2, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 2, 1, },
		{1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 2, 1, },
		{1, 0, 1, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 2, 0, 0, 2, 2, 0, 0, 0, 0, 1, 1, 0, 1, },
		{1, 0, 1, 1, 2, 0, 0, 2, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 2, 0, 0, 0, 0, 2, 2, 0, 0, 1, 1, 0, 1, },
		{1, 2, 2, 0, 0, 0, 0, 0, 1, 1, 1, 1, 2, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 2, 0, 0, 0, 2, 0, 2, 1, },
		{1, 0, 2, 2, 0, 0, 0, 0, 1, 1, 1, 1, 2, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 2, 0, 2, 0, 1, },
		{1, 0, 1, 1, 0, 2, 0, 0, 1, 1, 1, 1, 2, 0, 0, 0, 2, 2, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 1, },
		{1, 0, 1, 1, 2, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 2, 0, 2, 2, 0, 0, 0, 0, 2, 0, 0, 1, 1, 1, 1, 2, 2, 2, 0, 1, 1, 0, 1, },
		{1, 0, 0, 2, 0, 0, 0, 0, 2, 0, 0, 2, 2, 0, 2, 2, 0, 0, 0, 2, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 2, 2, 1, },
		{1, 2, 2, 0, 0, 0, 0, 2, 2, 0, 0, 2, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 2, 2, 0, 0, 0, 2, 2, 0, 1, },
		{1, 0, 1, 1, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 2, 2, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, },
		{1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 2, 0, 0, 2, 0, 0, 2, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 1, 1, 0, 1, },
		{1, 0, 1, 1, 1, 1, 0, 2, 1, 1, 2, 2, 1, 1, 2, 2, 1, 1, 2, 1, 1, 0, 1, 1, 0, 2, 1, 1, 0, 0, 1, 1, 0, 2, 1, 1, 1, 1, 0, 1, },
		{1, 0, 1, 1, 1, 1, 2, 2, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 2, 2, 1, 1, 2, 2, 1, 1, 1, 1, 0, 1, },
		{1, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 1, },
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, }
	
	};

	sf::Sprite m_gameMap;

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

public:
	GamePlay(std::shared_ptr<Context>& context);
	~GamePlay();

	void init() override;
	void processInput() override;
	void update(sf::Time deltaTime) override;

	void draw() override;

	void pause() override;
	void start() override;

	bool checkCollision(sf::Vector2f pos);
	void removeWalls(sf::Vector2f pos, int radius);
	void explosions(sf::Vector2f bombPos, int radius);
	void takeScreenshot(const std::string& filename);
};