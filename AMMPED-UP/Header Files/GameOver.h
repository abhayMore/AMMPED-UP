#pragma once
#include "SFML/Graphics/Text.hpp"
#include "SFML/Audio/Sound.hpp"
#include "State.h"
#include "Game.h"

class GameOver : public am::State
{
private:
	std::shared_ptr<Context> m_context;
	sf::Text m_gameOverTitle;
	sf::Text m_retryButton;
	sf::Text m_exitButton;

	bool m_isRetryButtonSelected;
	bool m_isRetryButtonPressed;

	bool m_isExitButtonSelected;
	bool m_isExitButtonPressed;

	sf::Sound m_deathSfx;
	sf::Music& m_bgm;

public:
	GameOver(std::shared_ptr<Context>& context);
	~GameOver();

	void init() override;
	void processInput() override;
	void update(sf::Time deltaTime) override;
	void draw() override;
	void start() override;
};