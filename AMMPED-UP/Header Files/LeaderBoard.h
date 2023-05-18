#pragma once
#include <memory>
#include <fstream>
#include "SFML/Graphics/Sprite.hpp"
#include "nlohmann/json.hpp"

#include "SFML/Graphics/Text.hpp"
#include "State.h"
#include "ScoreManager.h"
#include "Game.h"
#include "UserNameManager.h"
#include "AudioManager.h"

class Leaderboard : public am::State
{
private:
	std::shared_ptr<Context> m_context;
	sf::Text m_gameTitle;
	sf::Sprite m_menuBackground;
	bool m_isExitButtonPressed;
	
	AudioManager* m_bgm;

	sf::Text m_name;
	sf::Text m_scoreText;

	UserNameManager* username;


	std::ifstream inputFile;
	std::ofstream outputFile;
	nlohmann::json jsonFile;
	bool isInputFileEmpty = false;
	bool foundPlayerData = false;

public:
	Leaderboard(std::shared_ptr<Context>& context);
	~Leaderboard();

	void init() override;
	void processInput() override;
	void update(sf::Time deltaTime) override;

	void draw() override;
	void start();
	void pause();

	void writeToFile();
};

