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
	
	sf::Sprite m_exitBackground;
	sf::Text m_gameTitle;

	tgui::Theme theme;
	tgui::Gui gui;
	tgui::Button::Ptr m_pageButtons[3];




	bool m_isLogoutButtonPressed;
	bool m_isLogoutExitButtonPressed;
	bool m_isBackButtonPressed;

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