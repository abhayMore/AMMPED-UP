#include "../Header Files/LoginState.h"
#include "../Header Files/MainMenu.h"

#include "SFML/Window/Event.hpp"
#include "../Header Files/GamePlay.h"
#include "../Header Files/LoginPageState.h"
#include "../Header Files/RegisterPageState.h"

#include <memory>

LoginState::LoginState(std::shared_ptr<Context>& context) :
	m_context(context), 
	m_isLoginButtonSelected(true),
	m_isLoginButtonPressed(false),
	m_isRegisterButtonSelected(false),
	m_isRegisterButtonPressed(false),
	m_isExitButtonSelected(false),
	m_isExitButtonPressed(false)
{
}

LoginState::~LoginState()
{
}

void LoginState::init()
{
	m_context->m_assets->addFont(MAIN_FONT, "Resources/fonts/BOMBERMAN.TTF");

	m_context->m_assets->addTextures(GAME_LOGO, "Resources/assets/gameName.png");
	m_gameLogo.setTexture(m_context->m_assets->getTexture(GAME_LOGO));
	m_gameLogo.setPosition(m_context->m_window->getSize().x / 2, m_context->m_window->getSize().y / 2 - 150.0f);
	m_gameLogo.setOrigin(sf::Vector2f(m_gameLogo.getTexture()->getSize().x / 2, m_gameLogo.getTexture()->getSize().y / 2 ));
	m_gameLogo.setScale({0.5,0.5}); 
	//LOGIN BACKGROUND
	m_context->m_assets->addTextures(MENU_BACKGROUND, "Resources/assets/login.png");
	m_loginBackground.setTexture(m_context->m_assets->getTexture(MENU_BACKGROUND));
	m_loginBackground.setPosition(m_context->m_window->getSize().x / 2, m_context->m_window->getSize().y / 2);
	m_loginBackground.setOrigin(sf::Vector2f(m_loginBackground.getTexture()->getSize().x / 2, m_loginBackground.getTexture()->getSize().y / 2));

	//LOGIN BUTTON
	m_loginButton.setFont(m_context->m_assets->getFont(MAIN_FONT));
	m_loginButton.setString("LOGIN");
	m_loginButton.setCharacterSize(35);
	m_loginButton.setOrigin(m_loginButton.getLocalBounds().width / 2, m_loginButton.getLocalBounds().height / 2);
	m_loginButton.setPosition(m_context->m_window->getSize().x / 2, m_context->m_window->getSize().y / 2 - 75.0f) ;

	//REGISTER BUTTON
	m_registerButton.setFont(m_context->m_assets->getFont(MAIN_FONT));
	m_registerButton.setString("Register");
	m_registerButton.setCharacterSize(35);
	m_registerButton.setOrigin(m_registerButton.getLocalBounds().width / 2, m_registerButton.getLocalBounds().height / 2);
	m_registerButton.setPosition(m_context->m_window->getSize().x / 2, m_context->m_window->getSize().y / 2 - 25.0f);
	

	//EXIT BUTTON
	m_exitButton.setFont(m_context->m_assets->getFont(MAIN_FONT));
	m_exitButton.setString("Exit");
	m_exitButton.setCharacterSize(35);
	m_exitButton.setOrigin(m_exitButton.getLocalBounds().width / 2, m_exitButton.getLocalBounds().height / 2);
	m_exitButton.setPosition(m_context->m_window->getSize().x / 2, m_context->m_window->getSize().y / 2 + 25.0f);
	

	
}

void LoginState::processInput()
{
	sf::Event event;
	while (m_context->m_window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			m_context->m_window->close();
		else if (event.type == sf::Event::KeyPressed)
		{
			switch (event.key.code)
			{
			case sf::Keyboard::Up:
			{
				if (!m_isRegisterButtonSelected && !m_isLoginButtonSelected)
				{
					m_isLoginButtonSelected = false;
					m_isRegisterButtonSelected = true;
					m_isExitButtonSelected = false;
				}
				else if (!m_isLoginButtonSelected)
				{
					m_isLoginButtonSelected = true;
					m_isRegisterButtonSelected = false;
					m_isExitButtonSelected = false;
				}
				else if (!m_isExitButtonSelected && !m_isLoginButtonSelected)
				{
					m_isLoginButtonSelected = false;
					m_isRegisterButtonSelected = false;
					m_isExitButtonSelected = true;
				}

				break;
			}
			
			case sf::Keyboard::Down :
			{
				if (!m_isRegisterButtonSelected && !m_isExitButtonSelected)
				{
					m_isLoginButtonSelected = false;
					m_isRegisterButtonSelected = true;
					m_isExitButtonSelected = false;
				}
				else if (!m_isExitButtonSelected)
				{
					m_isLoginButtonSelected = false;
					m_isRegisterButtonSelected = false;
					m_isExitButtonSelected = true;
				}
				else if (!m_isLoginButtonSelected && !m_isExitButtonSelected)
				{
					m_isLoginButtonSelected = true;
					m_isRegisterButtonSelected = false;
					m_isExitButtonSelected = false;
				}
				break;
			}
			case sf::Keyboard::Return :
			{
				m_isLoginButtonPressed = false;
				m_isRegisterButtonPressed = false;
				m_isExitButtonPressed = false;
				if (m_isLoginButtonSelected)
				{
					m_isLoginButtonPressed = true;
				}
				else if(m_isRegisterButtonSelected)
				{
					m_isRegisterButtonPressed = true;
				}
				else
				{
					m_isExitButtonPressed = true;
				}
				break;
			}
			default:
				break;
			}
		}
	}
}

void LoginState::update(sf::Time deltaTime)
{
	if (m_isLoginButtonSelected)
	{
		m_loginButton.setFillColor(sf::Color::Magenta);
		m_registerButton.setFillColor(::sf::Color::White);
		m_exitButton.setFillColor(::sf::Color::White);

	}
	else if(m_isRegisterButtonSelected)
	{
		m_loginButton.setFillColor(sf::Color::White);
		m_registerButton.setFillColor(::sf::Color::Magenta);
		m_exitButton.setFillColor(::sf::Color::White);

	}
	else
	{
		m_loginButton.setFillColor(sf::Color::White);
		m_registerButton.setFillColor(::sf::Color::White);
		m_exitButton.setFillColor(::sf::Color::Magenta);
	}

	if (m_isLoginButtonPressed)
	{
		//TODO
		//Go to Play State
		m_context->m_states->add(std::make_unique<LoginPageState>(m_context), true);

		//m_context->m_states->add(std::make_unique<MainMenu>(m_context), true);

	}
	else if (m_isRegisterButtonPressed)
	{
		m_context->m_states->add(std::make_unique<RegisterPageState>(m_context), true);


	}
	else if (m_isExitButtonPressed)
	{
		m_context->m_window->close();
	}
}

void LoginState::draw()
{
	m_context->m_window->clear();
	m_context->m_window->draw(m_loginBackground);
	m_context->m_window->draw(m_gameLogo);

	m_context->m_window->draw(m_loginButton);
	m_context->m_window->draw(m_registerButton);
	m_context->m_window->draw(m_exitButton);

	m_context->m_window->display();
}

void LoginState::start()
{
}

void LoginState::pause()
{
}
