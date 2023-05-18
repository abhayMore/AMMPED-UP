#pragma once
#include <memory>
#include <fstream>
#include "SFML/Graphics/Sprite.hpp"
#include "TGUI/TGUI.hpp"
#include "SFML/Graphics/Text.hpp"
#include "State.h"
#include "Game.h"
#include "AudioManager.h"
#include "UsernameManager.h"
#include "nlohmann/json.hpp"
#include "TGUI/TGUI.hpp"

class OptionsState : public am::State
{
private:
	std::shared_ptr<Context> m_context;
	sf::Text m_optionsTitle;
	sf::Text m_resetHighScoreButton;
	sf::Text m_exitButton;
	sf::Sprite m_menuBackground;


	//DISPLAYS GENERAL CONTROLS
	sf::Text m_controlDirections[5];

	bool m_isResetHighScoreButtonSelected;
	bool m_isResetHighScoreButtonPressed;
	
	bool m_isExitButtonSelected;
	bool m_isExitButtonPressed;

	//SLIDERS
	tgui::Theme theme;
	tgui::Gui gui;
	tgui::Slider::Ptr m_audioControls[3];
	sf::Text m_overallMusic;
	sf::Text m_inGameMusic;
	sf::Text m_sfx;

	//BOOLEANS
	bool m_isOverallMusicSliderMove;
	bool m_isInGameMusicSliderMove;
	bool m_isSFXSliderMove;

	AudioManager* m_bgm;

	//Reset HighScore Warning
	sf::Text m_errorPrompt;

	//Reset Highscore
	UserNameManager* username;
	std::ifstream inputFile;
	std::ofstream outputFile;
	nlohmann::json jsonFile;
	bool isInputFileEmpty = false;
	bool foundPlayerData = false;
	sf::Time m_elapsedTime;

public:
	OptionsState(std::shared_ptr<Context>& context);
	~OptionsState();

	void init() override;
	void processInput() override;
	void update(sf::Time deltaTime) override;

	void draw() override;
	void start();
	void pause();

	void writeToFile();
};

