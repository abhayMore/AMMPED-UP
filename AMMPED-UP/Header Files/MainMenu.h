#pragma once
#include <memory>
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Text.hpp"
#include "State.h"
#include "Game.h"
#include "AudioManager.h"

class MainMenu : public am::State
{
private:
	std::shared_ptr<Context> m_context;
	sf::Sprite m_menuBackground;
	sf::Text m_gameTitle;
	
	tgui::Theme theme;
	tgui::Gui gui;
	tgui::Button::Ptr m_pageButtons[4];

	bool m_isPlayButtonPressed;
	bool m_isLeaderboardButtonPressed;
	bool m_isSettingsButtonPressed;
	bool m_isExitButtonPressed;

	//sf::Music& m_bgm;
	AudioManager* m_bgm;

public:
	MainMenu(std::shared_ptr<Context>& context, float Overallvolume = 50, float inGameMusicVolume = 50, float SFXVolume = 50);
	~MainMenu();

	void init() override;
	void processInput() override;
	void update(sf::Time deltaTime) override;

	void draw() override;
	void start();
	void pause();
};