#pragma once
#include <memory>
#include "SFML/Graphics/Sprite.hpp"
#include "MongoDB.h"
#include "MongoInstanceManager.h"

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

	//TOP PLAYERS
	sf::Text m_TopTenPlayerNames[10];
	sf::Text m_TopTenPlayerScores[10];


	//MONGODB
	MongoInstance* instance;
	learning::MongoDB m;
	std::vector<std::pair<std::string, int>> m_TopTenScores;
public:
	Leaderboard(std::shared_ptr<Context>& context);
	~Leaderboard();

	void init() override;
	void processInput() override;
	void update(sf::Time deltaTime) override;

	void draw() override;
	void start();
	void pause();


};

