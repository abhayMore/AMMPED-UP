#pragma once
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Text.hpp"
#include "State.h"
#include "Game.h"
#include "Button.h"
#include "TextBox.h"
#include "MongoDB.h"
#include "MongoInstanceManager.h"

#include <iostream>
#include <regex>


class RegisterPageState : public am::State
{
private:
	std::shared_ptr<Context> m_context;
	sf::Sprite m_loginBackground;

	//TITLES
	sf::Text m_signUpTitle;
	sf::Text m_userNameTitle;
	sf::Text m_emailIDTitle;
	sf::Text m_confirmEmailIDTitle;
	sf::Text m_passwordTitle;
	sf::Text m_confirmPasswordTitle;

	//TEXTBOXES
	Textbox m_allTextBoxes[5]; //Username, EmailID, ConfirmEmailID, Password, ConfrimPassword

	sf::Text m_errorPrompt;
	//BUTTONS
	Button m_registerButton;
	Button m_backButton;

	//BOOLEANS
	bool m_isBackButtonPressed = false;
	bool registered = false;

	bool isUsernameTaken = false;
	bool isEmailRegistered = false;
	bool isUserExists = false;

	
	
	//MONGODB
	mongocxx::instance& instance;
	learning::MongoDB m;

public:
	RegisterPageState(std::shared_ptr<Context>& context);
	~RegisterPageState();

	void init() override;
	void processInput() override;
	void update(sf::Time deltaTime) override;

	void draw() override;
	void start();
	void pause();

	void registerUser();
	void resetTextboxes();
	bool anyTextboxEmpty();
};
