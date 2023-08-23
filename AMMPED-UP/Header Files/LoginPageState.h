#pragma once
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Text.hpp"
#include "State.h"
#include "Game.h"
#include "Button.h"
#include "TextBox.h"
#include "UserNameManager.h"
#include "MongoDB.h"
#include "TextPrompt.h"

class LoginPageState : public am::State
{
private:
	std::shared_ptr<Context> m_context;

	sf::Sprite m_loginBackground;
	sf::Time m_elapsedTime;

	//TITLES
	sf::Text m_signInTitle;
	sf::Text m_userNameTitle;
	sf::Text m_emailIDTitle;
	sf::Text m_passwordTitle;

	//TEXTBOXES
	//Textbox m_allTextBoxes[2]; //Username or EmailID, Password
	tgui::EditBox::Ptr m_editTextBoxes[2];

	//Error visual showing at top left corner
	TextPrompt m_errorPrompt;


	//SIGN IN BUTTON
	tgui::Theme theme;
	tgui::Gui gui;
	tgui::Button::Ptr m_pageButtons[2];


	bool m_isSignInButtonPressed = false;
	bool m_isBackButtonPressed = false;

	//FILE SYSTEM
	bool verified = false;

	UserNameManager* m_username;

	//MONGODB
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
	bool anyTextboxEmpty();

};