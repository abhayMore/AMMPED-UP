#pragma once
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Text.hpp"
#include "State.h"
#include "Game.h"
#include "Button.h"
#include "TextBox.h"
#include "MongoDB.h"
#include "TextPrompt.h"

#include <iostream>
#include <regex>


class RegisterPageState : public am::State
{
private:
	std::shared_ptr<Context> m_context;
	sf::Sprite m_loginBackground;
	sf::Time m_elapsedTime;

	//TITLES
	sf::Text m_signUpTitle;
	sf::Text m_userNameTitle;
	sf::Text m_emailIDTitle;
	sf::Text m_confirmEmailIDTitle;
	sf::Text m_passwordTitle;
	sf::Text m_confirmPasswordTitle;

	//TEXTBOXES
	tgui::Theme theme;
	tgui::Gui gui;
	tgui::EditBox::Ptr m_editTextBoxes[5]; //Username, EmailID, ConfirmEmailID, Password, ConfrimPassword

	TextPrompt m_errorPrompt;
	//BUTTONS
	tgui::Button::Ptr m_pageButtons[2]; //REGISTER & BACK

	//BOOLEANS
	bool m_isRegisterButtonPressed = false;
	bool m_isBackButtonPressed = false;
	bool registered = false;

	bool isUsernameTaken = false;
	bool isEmailRegistered = false;
	bool isUserExists = false;

	//MONGODB
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
