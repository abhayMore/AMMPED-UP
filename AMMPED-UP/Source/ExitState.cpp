#include "../Header Files/ExitState.h"
#include "../Header Files/MainMenu.h"

#include "SFML/Window/Event.hpp"
#include "../Header Files/GamePlay.h"
#include "../Header Files/LoginState.h"
#include <memory>

enum buttonValues
{
	LOGOUT,
	LOGOUT_EXIT,
	BACK
};

ExitState::ExitState(std::shared_ptr<Context>& context) :
	m_context(context), 
	m_isLogoutButtonPressed(false),
	m_isLogoutExitButtonPressed(false),
	m_isBackButtonPressed(false),
	gui(*m_context->m_window)
{
	theme.load("Resources/Black.txt");
	AudioManager& audioManager = AudioManager::getInstance(
		m_context->m_assets->getSoundTrack(MAIN_SOUND_TRACK),
		m_context->m_assets->getSoundTrack(IN_GAME_SOUND_TRACK),
		m_context->m_assets->getSoundEffect(DAMAGE_SFX),
		m_context->m_assets->getSoundEffect(BLAST_SFX),
		m_context->m_assets->getSoundEffect(COIN_SFX),
		m_context->m_assets->getSoundEffect(ENEMY_DEATH_SFX)
	);
	m_bgm = &audioManager;
}

ExitState::~ExitState()
{
}

void ExitState::init()
{

	//MENU BACKGROUND 
	m_context->m_assets->addTextures(MENU_BACKGROUND, "Resources/assets/bombmap.png");
	m_exitBackground.setTexture(m_context->m_assets->getTexture(MENU_BACKGROUND));
	m_exitBackground.setPosition(m_context->m_window->getSize().x / 2.f, m_context->m_window->getSize().y / 2.f);
	m_exitBackground.setOrigin(sf::Vector2f(m_exitBackground.getTexture()->getSize().x / 2.f, m_exitBackground.getTexture()->getSize().y / 2.f));
	m_exitBackground.setScale({ 2,2 });

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
		if (i == LOGOUT)
		{
			m_pageButtons[i]->setText("Logout");
			m_pageButtons[i]->setPosition(m_context->m_window->getSize().x / 2 - m_pageButtons[i]->getSize().x / 2, m_context->m_window->getSize().y / 2 - 75.0f);
			m_pageButtons[i]->setFocused(true);
			m_pageButtons[i]->getRenderer()->setTextColorFocused(tgui::Color::Magenta);
			m_pageButtons[i]->getRenderer()->setBorderColorFocused(tgui::Color::Transparent);
		}
		else if (i == LOGOUT_EXIT)
		{
			m_pageButtons[i]->setText("Logout and Exit");
			m_pageButtons[i]->setPosition(m_context->m_window->getSize().x / 2 - m_pageButtons[i]->getSize().x / 2, m_context->m_window->getSize().y / 2);
			m_pageButtons[i]->getRenderer()->setTextColorFocused(tgui::Color::Magenta);
			m_pageButtons[i]->getRenderer()->setBorderColorFocused(tgui::Color::Transparent);
		}
		else if (i == BACK)
		{
			m_pageButtons[i]->setText("Back");
			m_pageButtons[i]->setPosition(m_context->m_window->getSize().x / 2 - m_pageButtons[i]->getSize().x / 2, m_context->m_window->getSize().y / 2 + 75.0f);
			m_pageButtons[i]->getRenderer()->setTextColorFocused(tgui::Color::Magenta);
			m_pageButtons[i]->getRenderer()->setBorderColorFocused(tgui::Color::Transparent);
		}
		m_pageButtons[i]->getRenderer()->setTextOutlineThickness(1);
		gui.add(m_pageButtons[i]);
	}
}

void ExitState::processInput()
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
					m_isLogoutButtonPressed = true;
				}
				if (m_pageButtons[1]->isMouseOnWidget({ mouseX, mouseY })
					&& m_pageButtons[1]->isFocused())
				{
					m_isLogoutExitButtonPressed = true;
				}
				if (m_pageButtons[2]->isMouseOnWidget({ mouseX, mouseY })
					&& m_pageButtons[2]->isFocused())
				{
					m_isBackButtonPressed = true;
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
					m_isLogoutButtonPressed = true;
				}
				else if (m_pageButtons[1]->isFocused())
				{
					m_isLogoutExitButtonPressed = true;
				}
				else if (m_pageButtons[2]->isFocused())
				{
					m_isBackButtonPressed = true;
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

void ExitState::update(sf::Time deltaTime)
{
	if (m_isLogoutExitButtonPressed)
	{
		//TODO
		//Close
		m_context->m_window->close();
		m_isLogoutExitButtonPressed = false;
	}
	else if (m_isLogoutButtonPressed)
	{
		//GOTO LOGIN STATE
		m_bgm->stopMainMenuMusic();
		//GO TO LOGIN STATE
		m_context->m_states->add(std::make_unique<LoginState>(m_context), true);
		m_isLogoutButtonPressed = false;
	}
	else if (m_isBackButtonPressed)
	{
		m_context->m_states->add(std::make_unique<MainMenu>(m_context, m_bgm->getOverallVolume(), m_bgm->getInGameVolume(), m_bgm->getSFXVolume()), true);
		m_isBackButtonPressed = false;
	}
}

void ExitState::draw()
{
	m_context->m_window->clear();
	m_context->m_window->draw(m_exitBackground);
	m_context->m_window->draw(m_gameTitle);
	gui.draw();

	m_context->m_window->display();
}

void ExitState::start()
{
}

void ExitState::pause()
{
}