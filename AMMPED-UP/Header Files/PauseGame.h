#pragma once
#include <memory>
#include "SFML/Graphics/Text.hpp"
#include "State.h"
#include "Game.h"
#include "AudioManager.h"

class PauseGame : public am::State
{
private:
	std::shared_ptr<Context> m_context;
	sf::Text m_pauseTitle;

	tgui::Theme theme;
	tgui::Gui gui;
	tgui::Button::Ptr m_pageButtons[3];

	bool m_isResumeButtonPressed;
	bool m_isRestartButtonPressed;
	bool m_isMainMenuButtonPressed;
	AudioManager* m_bgm;

public:
	PauseGame(std::shared_ptr<Context>& context);
	~PauseGame();

	void init() override;
	void processInput() override;
	void update(sf::Time deltaTime) override;

	void draw() override;
	void start();
};