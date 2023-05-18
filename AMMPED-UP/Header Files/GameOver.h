#pragma once
#include <fstream>
#include "SFML/Graphics/Text.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Audio/Sound.hpp"
#include "nlohmann/json.hpp"
#include "State.h"
#include "Game.h"
#include "ScoreManager.h"
#include "UserNameManager.h"

class GameOver : public am::State
{
private:
	std::shared_ptr<Context> m_context;
	sf::Sprite m_gameOverBackground;


	sf::Text m_gameOverTitle;

	sf::Text m_currentGameStateTitle;
	std::string m_currentGameState; //WON, DIED, TIME's UP??
	sf::Text m_scoreText;
	ScoreManager *m_finalScore;

	sf::Text m_retryButton;
	sf::Text m_exitButton;

	bool m_isRetryButtonSelected;
	bool m_isRetryButtonPressed;

	bool m_isExitButtonSelected;
	bool m_isExitButtonPressed;

	sf::Sound m_deathSfx;
	sf::Music& m_bgm;

	//FILE SYSTEM FOR SCORE SAVING
	UserNameManager* m_userName;
	std::ifstream inputFile;
	std::ofstream outputFile;
	nlohmann::json jsonFile;
	bool isInputFileEmpty = false;
	bool foundPlayerData = false;

public:
	GameOver(std::shared_ptr<Context>& context, std::string currentState);
	~GameOver();

	void init() override;
	void processInput() override;
	void update(sf::Time deltaTime) override;
	void draw() override;
	void start() override;

	void writeToFile();
};