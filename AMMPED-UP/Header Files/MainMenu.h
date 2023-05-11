#pragma once
#include <memory>
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Text.hpp"
#include "State.h"
#include "Game.h"

class MainMenu : public am::State
{
private:
	std::shared_ptr<Context> m_context;
	sf::Text m_gameTitle;
	sf::Text m_playButton;
	sf::Text m_leadershipButton;
	sf::Text m_optionsButton;
	sf::Text m_exitButton;
	

	sf::Sprite m_menuBackground;

	bool m_isPlayButtonSelected;
	bool m_isPlayButtonPressed;

	bool m_isLeadershipButtonSelected;
	bool m_isLeadershipButtonPressed;

	bool m_isOptionsButtonSelected;
	bool m_isOptionsButtonPressed;

	bool m_isExitButtonSelected;
	bool m_isExitButtonPressed;

	sf::Music& m_bgm;

public:
	MainMenu(std::shared_ptr<Context>& context);
	~MainMenu();

	void init() override;
	void processInput() override;
	void update(sf::Time deltaTime) override;

	void draw() override;
	void start();
	void pause();
};