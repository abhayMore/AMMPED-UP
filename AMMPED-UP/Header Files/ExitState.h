#pragma once
#include <memory>
#include "SFML/Graphics/Sprite.hpp"

#include "SFML/Graphics/Text.hpp"
#include "State.h"
#include "Game.h"

class ExitState : public am::State
{
private:
	std::shared_ptr<Context> m_context;
	sf::Text m_gameTitle;
	sf::Text m_logoutExit;
	sf::Text m_logout;
	sf::Sprite m_exitBackground;

	bool m_isLogoutExitButtonSelected;
	bool m_isLogoutExitButtonPressed;

	bool m_isLogoutSelected;
	bool m_isLogoutButtonPressed;

	sf::Music& m_bgm;


public:
	ExitState(std::shared_ptr<Context>& context);
	~ExitState();

	void init() override;
	void processInput() override;
	void update(sf::Time deltaTime) override;

	void draw() override;
	void start();
	void pause();

};

