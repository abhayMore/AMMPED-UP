#pragma once
#include <memory>

#include "SFML/Graphics/Text.hpp"
#include "State.h"
#include "Game.h"

class PauseGame : public am::State
{
private:
	std::shared_ptr<Context> m_context;
	sf::Text m_pauseTitle;
	sf::Text m_resumeButton;
	sf::Text m_mainMenuButton;
	sf::Text m_restartButton;

	bool m_isResumeButtonSelected;
	bool m_isResumeButtonPressed;

	bool m_isRestartButtonSelected;
	bool m_isRestartButtonPressed;

	bool m_isMainMenuButtonSelected;
	bool m_isMainMenuButtonPressed;


	sf::Music& m_bgm;

public:
	PauseGame(std::shared_ptr<Context>& context);
	~PauseGame();

	void init() override;
	void processInput() override;
	void update(sf::Time deltaTime) override;

	void draw() override;
	void start();
};

