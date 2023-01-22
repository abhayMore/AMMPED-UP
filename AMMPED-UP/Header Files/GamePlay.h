#pragma once
#include <memory>
#include <array>

#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Text.hpp"
#include "SFML/Audio/Sound.hpp"
#include "../Header Files/Animation.h"

#include "Game.h"
#include "State.h"
#include "Snake.h"

class GamePlay : public am::State
{
private:
	std::shared_ptr<Context> m_context;
	sf::Sprite m_grass;
	sf::Sprite m_food;
	std::array<sf::Sprite, 4> m_walls;
	Snake m_snake;

	sf::Sprite m_gameMap;

	sf::Vector2f m_snakeDirection;
	sf::Time m_elapsedTime;

	sf::Text m_scoreText;
	int m_score;

	sf::Text m_livesText;
	int m_lives;

	bool m_isPaused;

	sf::Sound m_foodEatSfx;
	sf::Music& m_inGame;

	Animation foodAnimation;

public:
	GamePlay(std::shared_ptr<Context>& context);
	~GamePlay();

	void init() override;
	void processInput() override;
	void update(sf::Time deltaTime) override;

	void draw() override;

	void pause() override;
	void start() override;

	void takeScreenshot(const std::string& filename);
};