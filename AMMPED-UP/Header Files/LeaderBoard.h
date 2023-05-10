#pragma once
#include <memory>
#include "SFML/Graphics/Sprite.hpp"

#include "SFML/Graphics/Text.hpp"
#include "State.h"
#include "Game.h"

class Leaderboard : public am::State
{
private:
	std::shared_ptr<Context> m_context;
	sf::Text m_gameTitle;
	sf::Sprite m_menuBackground;
	bool m_isExitButtonPressed;
	
	sf::Text m_name;
	sf::Text m_scoreText;

	
	std::string m_username;
	int m_finalScore;
	sf::Music& m_bgm;

public:
	Leaderboard(std::shared_ptr<Context>& context, std::string UID, int score);
	~Leaderboard();

	void init() override;
	void processInput() override;
	void update(sf::Time deltaTime) override;

	void draw() override;
	void start();
	void pause();

};

