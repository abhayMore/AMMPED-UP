#include "../Header Files/LoginState.h"
#include "../Header Files/MainMenu.h"
#include "SFML/Window/Event.hpp"
#include "../Header Files/GamePlay.h"
#include "../Header Files/LoginPageState.h"
#include "../Header Files/RegisterPageState.h"
#include <memory>

enum buttonValues
{
	LOGIN,
	REGISTER,
	EXIT
};

LoginState::LoginState(std::shared_ptr<Context>& context) :
	m_context(context), 
	m_isLoginButtonPressed(false),
	m_isRegisterButtonPressed(false),
	m_isExitButtonPressed(false),
	gui(*m_context->m_window)
{
	theme.load("Resources/Black.txt");

}

LoginState::~LoginState()
{
}

void LoginState::init()
{
	m_context->m_assets->addFont(MAIN_FONT, "Resources/fonts/BungeeSpice-Regular.TTF");

	//LOGIN BACKGROUND
	m_context->m_assets->addTextures(MENU_BACKGROUND, "Resources/assets/login.png");
	m_loginBackground.setTexture(m_context->m_assets->getTexture(MENU_BACKGROUND));
	m_loginBackground.setPosition(static_cast<float>(m_context->m_window->getSize().x / 2), static_cast<float>(m_context->m_window->getSize().y / 2));
	m_loginBackground.setOrigin(sf::Vector2f(static_cast<float>(m_loginBackground.getTexture()->getSize().x / 2), static_cast<float>(m_loginBackground.getTexture()->getSize().y / 2)));
	m_loginBackground.setScale({ 2,2 });

	//GAME LOGO
	m_context->m_assets->addTextures(GAME_LOGO, "Resources/assets/gameName.png");
	m_gameLogo.setTexture(m_context->m_assets->getTexture(GAME_LOGO));
	m_gameLogo.setPosition(static_cast<float>(m_context->m_window->getSize().x / 2), static_cast<float>(m_context->m_window->getSize().y / 2) - 150.0f);
	m_gameLogo.setOrigin(sf::Vector2f(static_cast<float>(m_gameLogo.getTexture()->getSize().x / 2), static_cast<float>(m_gameLogo.getTexture()->getSize().y / 2)));
	m_gameLogo.setScale({ 0.5,0.5 });

	///////////////////////////////////////////////////
	m_context->m_assets->addGuiFont(MAIN_FONT, "Resources/fonts/BungeeSpice-Regular.TTF");
	
	for (int i = 0; i < 3; i++)
	{
		m_pageButtons[i] = tgui::Button::create();
		m_pageButtons[i]->getRenderer()->setBackgroundColor(tgui::Color::Transparent);
		m_pageButtons[i]->getRenderer()->setBorderColor(tgui::Color::Transparent);
		m_pageButtons[i]->getRenderer()->setTextColor(tgui::Color::White);
		m_pageButtons[i]->getRenderer()->setFont(tgui::Font(m_context->m_assets->getGuiFont(MAIN_FONT).getId()));
		m_pageButtons[i]->setTextSize(35);
		if (i == LOGIN)
		{
			m_pageButtons[i]->setText("LOGIN");
			m_pageButtons[i]->setPosition(m_context->m_window->getSize().x / 2 - m_pageButtons[i]->getSize().x / 2, m_context->m_window->getSize().y / 2 - 75.0f);
			m_pageButtons[i]->setFocused(true);
			m_pageButtons[i]->getRenderer()->setTextColorFocused(tgui::Color::Magenta);
			m_pageButtons[i]->getRenderer()->setBorderColorFocused(tgui::Color::Transparent);
		}
		else if (i == REGISTER)
		{
			m_pageButtons[i]->setText("REGISTER");
			m_pageButtons[i]->setPosition(m_context->m_window->getSize().x / 2 - m_pageButtons[i]->getSize().x / 2, m_context->m_window->getSize().y / 2);
			m_pageButtons[i]->getRenderer()->setTextColorFocused(tgui::Color::Magenta);
			m_pageButtons[i]->getRenderer()->setBorderColorFocused(tgui::Color::Transparent);
		}
		else if (i == EXIT)
		{
			m_pageButtons[i]->setText("EXIt");

			m_pageButtons[i]->setPosition(m_context->m_window->getSize().x / 2 - m_pageButtons[i]->getSize().x / 2, m_context->m_window->getSize().y / 2 + 75.0f);
			m_pageButtons[i]->getRenderer()->setTextColorFocused(tgui::Color::Magenta);
			m_pageButtons[i]->getRenderer()->setBorderColorFocused(tgui::Color::Transparent);
		}
		m_pageButtons[i]->getRenderer()->setTextOutlineThickness(1);
		gui.add(m_pageButtons[i]);
	}
	

}
void LoginState::processInput()
{
	sf::Event event;
	while (m_context->m_window->pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
		{
			m_context->m_window->close();
			break;
		}
		case sf::Event::MouseButtonPressed:
		{
			switch (event.key.code)
			{
			case sf::Mouse::Left:
			{
				float mouseX = static_cast<float>(sf::Mouse::getPosition(*m_context->m_window).x);
				float mouseY = static_cast<float>(sf::Mouse::getPosition(*m_context->m_window).y);
				if (m_pageButtons[0]->isMouseOnWidget({ mouseX, mouseY }) 
					&& m_pageButtons[0]->isFocused())
				{
					m_isLoginButtonPressed = true;
				}
				if (m_pageButtons[1]->isMouseOnWidget({ mouseX, mouseY })
					&& m_pageButtons[1]->isFocused())
				{
					m_isRegisterButtonPressed = true;
				}
				if (m_pageButtons[2]->isMouseOnWidget({ mouseX, mouseY })
					&& m_pageButtons[2]->isFocused())
				{
					m_isExitButtonPressed = true;
				}
				break;
			}
			default:
				break;
			}
			break;
		}
		case sf::Event::MouseMoved:
		{
			float mouseX = static_cast<float>(sf::Mouse::getPosition(*m_context->m_window).x);
			float mouseY = static_cast<float>(sf::Mouse::getPosition(*m_context->m_window).y);
			if (m_pageButtons[0]->isMouseOnWidget({ mouseX, mouseY }))
			{
				m_pageButtons[0]->setFocused(true);
				m_pageButtons[1]->setFocused(false);
				m_pageButtons[2]->setFocused(false);
			}
			else if (m_pageButtons[1]->isMouseOnWidget({ mouseX, mouseY }))
			{
				m_pageButtons[1]->setFocused(true);
				m_pageButtons[0]->setFocused(false);
				m_pageButtons[2]->setFocused(false);
			}
			else if (m_pageButtons[2]->isMouseOnWidget({ mouseX, mouseY }))
			{
				m_pageButtons[2]->setFocused(true);
				m_pageButtons[0]->setFocused(false);
				m_pageButtons[1]->setFocused(false);
			}
			break;
		}
		case sf::Event::KeyPressed:
		{
			switch (event.key.code)
			{
			case sf::Keyboard::Up:
			{
				if (m_pageButtons[2]->isFocused())
				{
					m_pageButtons[1]->setFocused(true);
					m_pageButtons[1]->getRenderer()->setTextColorFocused(tgui::Color::Magenta);
					m_pageButtons[1]->getRenderer()->setBorderColorFocused(tgui::Color::Transparent);
					m_pageButtons[2]->setFocused(false);
				}
				else if (m_pageButtons[1]->isFocused())
				{
					m_pageButtons[0]->setFocused(true);
					m_pageButtons[0]->getRenderer()->setTextColorFocused(tgui::Color::Magenta);
					m_pageButtons[0]->getRenderer()->setBorderColorFocused(tgui::Color::Transparent);
					m_pageButtons[1]->setFocused(false);
				}
				break;
			}
			case sf::Keyboard::Down:
			{
				if (m_pageButtons[0]->isFocused())
				{
					m_pageButtons[1]->setFocused(true);
					m_pageButtons[1]->getRenderer()->setTextColorFocused(tgui::Color::Magenta);
					m_pageButtons[1]->getRenderer()->setBorderColorFocused(tgui::Color::Transparent);
					m_pageButtons[0]->setFocused(false);
				}
				else if (m_pageButtons[1]->isFocused())
				{
					m_pageButtons[2]->setFocused(true);
					m_pageButtons[2]->getRenderer()->setTextColorFocused(tgui::Color::Magenta);
					m_pageButtons[2]->getRenderer()->setBorderColorFocused(tgui::Color::Transparent);
					m_pageButtons[1]->setFocused(false);
				}
				break;
			}
			case sf::Keyboard::Enter:
			{
				if (m_pageButtons[0]->isFocused())
				{
					m_isLoginButtonPressed = true;
				}
				else if (m_pageButtons[1]->isFocused())
				{
					m_isRegisterButtonPressed = true;
				}
				else if (m_pageButtons[2]->isFocused())
				{
					m_isExitButtonPressed = true;
				}
				break;
			}
			default:
				break;
			}
			break;
		}
		default:
			break;
		}
	}
}

void LoginState::update(sf::Time deltaTime)
{
	if (m_isLoginButtonPressed)
	{
		//TODO
		//Go to Play State
		m_context->m_states->add(std::make_unique<LoginPageState>(m_context), true);
		//m_context->m_states->add(std::make_unique<MainMenu>(m_context), true);
		m_isLoginButtonPressed = false;

	}
	else if (m_isRegisterButtonPressed)
	{
		m_context->m_states->add(std::make_unique<RegisterPageState>(m_context), true);
		m_isRegisterButtonPressed = false;
	}
	else if (m_isExitButtonPressed)
	{
		m_context->m_window->close();
		m_isExitButtonPressed = false;
	}
}

void LoginState::draw()
{
	m_context->m_window->clear();
	m_context->m_window->draw(m_loginBackground);
	m_context->m_window->draw(m_gameLogo);

	gui.draw();
	m_context->m_window->display();
}

void LoginState::start()
{
}

void LoginState::pause()
{
}