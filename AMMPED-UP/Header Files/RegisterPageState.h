#pragma once
#include "SFML/Graphics/Sprite.hpp"
#include <fstream>
#include "SFML/Graphics/Text.hpp"
#include "State.h"
#include "Game.h"
#include "Button.h"
#include "TextBox.h"
#include "nlohmann/json.hpp"

struct scn3
{
	bool email = false;
	bool confirmEmail = false;
	bool password = false;
	bool confirmPassword = false;
};

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

	//REGISTER BUTTON
	Button m_registerButton;
	
	//account acc[100];

	//FILE
	std::ofstream file;
	nlohmann::json jsonFile;

public:
	RegisterPageState(std::shared_ptr<Context>& context);
	~RegisterPageState();

	void init() override;
	void processInput() override;
	void update(sf::Time deltaTime) override;

	void draw() override;
	void start();
	void pause();

	void input();
};