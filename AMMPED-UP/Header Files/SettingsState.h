#pragma once
#include <memory>
#include "SFML/Graphics/Sprite.hpp"
#include "TGUI/TGUI.hpp"
#include "SFML/Graphics/Text.hpp"
#include "State.h"
#include "Game.h"
#include "AudioManager.h"
#include "UsernameManager.h"
#include "MongoDB.h"
#include "TextPrompt.h"

class SettingsState : public am::State
{
private:
	std::shared_ptr<Context> m_context;
	sf::Text m_settingsTitle;
	sf::Sprite m_menuBackground;
	//DISPLAYS GENERAL CONTROLS
	sf::Text m_controlDirections[5];

	bool m_isResetHighScoreButtonPressed;
	bool m_isMainmenuButtonPressed;

	//SLIDERS
	tgui::Theme theme;
	tgui::Gui gui;
	tgui::Slider::Ptr m_audioControls[3];
	tgui::Button::Ptr m_pageButtons[2];
	sf::Text m_overallMusic;
	sf::Text m_inGameMusic;
	sf::Text m_sfx;

	//BOOLEANS
	bool m_isOverallMusicSliderMove;
	bool m_isInGameMusicSliderMove;
	bool m_isSFXSliderMove;

	AudioManager* m_bgm;

	//Reset HighScore Warning
	TextPrompt m_errorPrompt;

	//Reset Highscore
	UserNameManager* username;
	
	sf::Time m_elapsedTime;

	//MONGODB
	learning::MongoDB m;

public:
	SettingsState(std::shared_ptr<Context>& context);
	~SettingsState();

	void init() override;
	void processInput() override;
	void update(sf::Time deltaTime) override;

	void draw() override;
	void start();
	void pause();

};

