#include "../Header Files/ExitState.h"
#include "SFML/Window/Event.hpp"
#include "../Header Files/GamePlay.h"
#include "../Header Files/LoginState.h"
#include "../Header Files/MainMenu.h"
#include <memory>

ExitState::ExitState(std::shared_ptr<Context>& context) :
	m_context(context), 
	m_isLogoutExitButtonSelected(false),
	m_isLogoutExitButtonPressed(false),
	m_isLogoutSelected(true),
	m_isLogoutButtonPressed(false),
	m_isBackButtonSelected(false),
	m_isBackButtonPressed(false),
	m_bgm(m_context->m_assets->getSoundTrack(MAIN_SOUND_TRACK))
{
}

ExitState::~ExitState()
{
}

void ExitState::init()
{
	m_context->m_assets->addFont(MAIN_FONT, "Resources/fonts/BOMBERMAN.TTF");

	//MENU BACKGROUND 
	m_context->m_assets->addTextures(MENU_BACKGROUND, "Resources/assets/bombmap.png");
	m_exitBackground.setTexture(m_context->m_assets->getTexture(MENU_BACKGROUND));
	m_exitBackground.setPosition(m_context->m_window->getSize().x / 2, m_context->m_window->getSize().y / 2);
	m_exitBackground.setOrigin(sf::Vector2f(m_exitBackground.getTexture()->getSize().x / 2, m_exitBackground.getTexture()->getSize().y / 2));
	m_exitBackground.setScale({ 2,2 });

	//LOGOUT AND EXIT BUTTON
	m_logoutExit.setFont(m_context->m_assets->getFont(MAIN_FONT));
	m_logoutExit.setString("Logout and Exit");
	m_logoutExit.setCharacterSize(35);
	m_logoutExit.setOrigin(m_logoutExit.getLocalBounds().width / 2, m_logoutExit.getLocalBounds().height / 2);
	m_logoutExit.setPosition(m_context->m_window->getSize().x / 2, m_context->m_window->getSize().y / 2 + 25.0f);
	
	//LOGOUT BUTTON
	m_logout.setFont(m_context->m_assets->getFont(MAIN_FONT));
	m_logout.setString("Logout");
	m_logout.setCharacterSize(35);
	m_logout.setOrigin(m_logout.getLocalBounds().width / 2, m_logout.getLocalBounds().height / 2);
	m_logout.setPosition(m_context->m_window->getSize().x / 2, m_context->m_window->getSize().y / 2 - 25.0f);
	
	//BACK BUTTON
	m_backButton.setFont(m_context->m_assets->getFont(MAIN_FONT));
	m_backButton.setString("Back");
	m_backButton.setCharacterSize(35);
	m_backButton.setOrigin(m_backButton.getLocalBounds().width / 2, m_backButton.getLocalBounds().height / 2);
	m_backButton.setPosition(m_context->m_window->getSize().x / 2, m_context->m_window->getSize().y / 2 +75.0f);
}

void ExitState::processInput()
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
				if (!m_isLogoutExitButtonSelected && !m_isLogoutSelected)
				{
					m_isLogoutSelected = false;
					m_isLogoutExitButtonSelected = true;
					m_isBackButtonSelected = false;
				}
				else if (!m_isLogoutSelected)
				{
					m_isLogoutSelected = true;
					m_isLogoutExitButtonSelected = false;
					m_isBackButtonSelected = false;
				}
				else if (!m_isBackButtonSelected && !m_isLogoutSelected)
				{
					m_isLogoutSelected = false;
					m_isLogoutExitButtonSelected = false;
					m_isBackButtonSelected = true;
				}
				break;
			}
			case sf::Keyboard::Down :
			{
				if (!m_isLogoutExitButtonSelected && !m_isBackButtonSelected)
				{
					m_isLogoutSelected = false;
					m_isLogoutExitButtonSelected = true;
					m_isBackButtonSelected = false;
				}
				else if (!m_isBackButtonSelected)
				{
					m_isLogoutSelected = false;
					m_isLogoutExitButtonSelected = false;
					m_isBackButtonSelected = true;
				}
				else if (!m_isLogoutSelected && !m_isBackButtonSelected)
				{
					m_isLogoutSelected = true;
					m_isLogoutExitButtonSelected = false;
					m_isBackButtonSelected = false;
				}
				break;
			}
			case sf::Keyboard::Return :
			{
				m_isLogoutButtonPressed = false;
				m_isLogoutExitButtonPressed = false;
				m_isBackButtonPressed = false;
				if (m_isLogoutSelected)
				{
					m_isLogoutButtonPressed = true;
				}
				else if (m_isLogoutExitButtonSelected)
				{
					m_isLogoutExitButtonPressed = true;
				}
				else
				{
					m_isBackButtonPressed = true;
				}
				break;
			}
			case sf::Keyboard::Escape:
			{
				m_isBackButtonPressed = true;
				break;
			}
			default:
				break;
			}
		}
	}
}

void ExitState::update(sf::Time deltaTime)
{
	if (m_isLogoutSelected)
	{
		m_logout.setFillColor(sf::Color::Magenta);
		m_logoutExit.setFillColor(::sf::Color::White);
		m_backButton.setFillColor(::sf::Color::White);
	}
	else if (m_isLogoutExitButtonSelected)
	{
		m_logout.setFillColor(sf::Color::White);
		m_logoutExit.setFillColor(::sf::Color::Magenta);
		m_backButton.setFillColor(::sf::Color::White);
	}
	else
	{
		m_logout.setFillColor(sf::Color::White);
		m_logoutExit.setFillColor(::sf::Color::White);
		m_backButton.setFillColor(::sf::Color::Magenta);
	}
	if (m_isLogoutExitButtonPressed)
	{
		//TODO
		//Close
		m_context->m_window->close();
	}
	else if (m_isLogoutButtonPressed)
	{
		//GOTO LOGIN STATE
		m_bgm.stop();
		//GO TO LOGIN STATE
		m_context->m_states->add(std::make_unique<LoginState>(m_context), true);
	}
	else if (m_isBackButtonPressed)
	{
		m_context->m_states->popCurrent();
		m_context->m_states->add(std::make_unique<MainMenu>(m_context), true);
		m_isBackButtonPressed = false;
	}
}

void ExitState::draw()
{
	m_context->m_window->clear();
	m_context->m_window->draw(m_exitBackground);
	m_context->m_window->draw(m_gameTitle);
	m_context->m_window->draw(m_logoutExit);
	m_context->m_window->draw(m_logout);
	m_context->m_window->draw(m_backButton);

	m_context->m_window->display();
}

void ExitState::start()
{
}

void ExitState::pause()
{
}