#pragma once
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Text.hpp"
#include "State.h"
#include "Game.h"
#include "Button.h"
#include "TextBox.h"
#include "UserNameManager.h"
#include "MongoInstanceManager.h"
#include "MongoDB.h"

class LoginPageState : public am::State
{
private:
	std::shared_ptr<Context> m_context;

	sf::Sprite m_loginBackground;

	//TITLES
	sf::Text m_signInTitle;
	sf::Text m_userNameTitle;
	sf::Text m_emailIDTitle;
	sf::Text m_passwordTitle;

	//TEXTBOXES
	Textbox m_allTextBoxes[2]; //Username, EmailID, Password
	sf::Text m_errorPrompt;

	//SIGN IN BUTTON
	Button m_signInButton;
	Button m_backButton;

	bool m_isSignInButtonPressed = false;
	bool m_isBackButtonPressed = false;
	//FILE SYSTEM
	

	bool verified = false;

	UserNameManager* m_username;

	//MONGODB
	mongocxx::instance& instance;
	learning::MongoDB m;

public:
	LoginPageState(std::shared_ptr<Context>& context);
	~LoginPageState();

	void init() override;
	void processInput() override;
	void update(sf::Time deltaTime) override;

	void draw() override;
	void start();
	void pause();

};