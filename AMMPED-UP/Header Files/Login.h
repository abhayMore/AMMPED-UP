#pragma once
#include <memory>
#include "SFML/Graphics/Sprite.hpp"

#include "SFML/Graphics/Text.hpp"
#include "State.h"
#include "Game.h"

class Login : public am::State
{
private:
	std::shared_ptr<Context> m_context;
	sf::Text m_loginButton;
	sf::Text m_registerButton;
	sf::Text m_exitButton;
	sf::Sprite m_loginBackground;
	sf::Sprite m_gameLogo;

	bool m_isRegisterButtonSelected;
	bool m_isRegisterButtonPressed;

	bool m_isLoginButtonSelected;
	bool m_isLoginButtonPressed;

	bool m_isExitButtonSelected;
	bool m_isExitButtonPressed;

public:
	Login(std::shared_ptr<Context>& context);
	~Login();

	void init() override;
	void processInput() override;
	void update(sf::Time deltaTime) override;

	void draw() override;
	void start();
	void pause();

};

