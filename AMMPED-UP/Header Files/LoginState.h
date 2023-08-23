#pragma once
#include <memory>
#include "SFML/Graphics/Sprite.hpp"
#include "TGUI/TGUI.hpp"

#include "SFML/Graphics/Text.hpp"
#include "State.h"
#include "Game.h"

class LoginState : public am::State
{
private:
	std::shared_ptr<Context> m_context;

	tgui::Theme theme;
	tgui::Gui gui;
	tgui::Button::Ptr m_pageButtons[3];

	sf::Sprite m_loginBackground;
	sf::Sprite m_gameLogo;

	bool m_isRegisterButtonPressed;
	bool m_isLoginButtonPressed;
	bool m_isExitButtonPressed;

public:
	LoginState(std::shared_ptr<Context>& context);
	~LoginState();

	void init() override;
	void processInput() override;
	void update(sf::Time deltaTime) override;

	void draw() override;
	void start();
	void pause();
};