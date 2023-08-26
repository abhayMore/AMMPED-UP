#include "../Header Files/PauseGame.h"
#include "../Header Files/MainMenu.h"
#include "SFML/Window/Event.hpp"
#include "../Header Files/GamePlay.h"
#include <memory>

enum buttonValues
{
	RESUME,
	RESTART,
	MAINMENU
};

PauseGame::PauseGame(std::shared_ptr<Context>& context) : 
	m_context(context), 
	m_isResumeButtonPressed(false),
	m_isRestartButtonPressed(false),
	m_isMainMenuButtonPressed(false),
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

PauseGame::~PauseGame()
{
}
void PauseGame::init()
{
	//PAUSE TITLE
	m_pauseTitle.setFont(m_context->m_assets->getFont(MAIN_FONT));
	m_pauseTitle.setString("Paused!!");
	m_pauseTitle.setCharacterSize(50);
	m_pauseTitle.setPosition(static_cast<float>(m_context->m_window->getSize().x / 2), static_cast<float>(m_context->m_window->getSize().y / 2) - 150.0f);
	m_pauseTitle.setOrigin(m_pauseTitle.getLocalBounds().width / 2, m_pauseTitle.getLocalBounds().height / 2);

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
		if (i == RESUME)
		{
			m_pageButtons[i]->setText("RESUME");
			m_pageButtons[i]->setPosition(m_context->m_window->getSize().x / 2 - m_pageButtons[i]->getSize().x / 2, m_context->m_window->getSize().y / 2 - 75.0f);
			m_pageButtons[i]->setFocused(true);
			m_pageButtons[i]->getRenderer()->setTextColorFocused(tgui::Color::Magenta);
			m_pageButtons[i]->getRenderer()->setBorderColorFocused(tgui::Color::Transparent);
		}
		else if (i == RESTART)
		{
			m_pageButtons[i]->setText("RESTART");
			m_pageButtons[i]->setPosition(m_context->m_window->getSize().x / 2 - m_pageButtons[i]->getSize().x / 2, m_context->m_window->getSize().y / 2);
			m_pageButtons[i]->getRenderer()->setTextColorFocused(tgui::Color::Magenta);
			m_pageButtons[i]->getRenderer()->setBorderColorFocused(tgui::Color::Transparent);
		}
		else if (i == MAINMENU)
		{
			m_pageButtons[i]->setText("MAINMENU");

			m_pageButtons[i]->setPosition(m_context->m_window->getSize().x / 2 - m_pageButtons[i]->getSize().x / 2, m_context->m_window->getSize().y / 2 + 75.0f);
			m_pageButtons[i]->getRenderer()->setTextColorFocused(tgui::Color::Magenta);
			m_pageButtons[i]->getRenderer()->setBorderColorFocused(tgui::Color::Transparent);
		}
		m_pageButtons[i]->getRenderer()->setTextOutlineThickness(1);
		gui.add(m_pageButtons[i]);
	}
}

void PauseGame::processInput()
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
					m_isResumeButtonPressed = true;
				}
				if (m_pageButtons[1]->isMouseOnWidget({ mouseX, mouseY })
					&& m_pageButtons[1]->isFocused())
				{
					m_isRestartButtonPressed = true;
				}
				if (m_pageButtons[2]->isMouseOnWidget({ mouseX, mouseY })
					&& m_pageButtons[2]->isFocused())
				{
					m_isMainMenuButtonPressed = true;
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
			case sf::Keyboard::Escape:
			{
				m_isResumeButtonPressed = true;
				break;
			}
			case sf::Keyboard::Return:
			{
				if (m_pageButtons[0]->isFocused())
				{
					m_isResumeButtonPressed = true;
				}
				else if (m_pageButtons[1]->isFocused())
				{
					m_isRestartButtonPressed = true;
				}
				else if (m_pageButtons[2]->isFocused())
				{
					m_isMainMenuButtonPressed = true;
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

void PauseGame::update(sf::Time deltaTime)
{	
	
	if (m_isResumeButtonPressed)
	{
		//TODO
		//Go to Play State
		m_bgm->stopMainMenuMusic();
		m_context->m_states->popCurrent();
		m_isResumeButtonPressed = false;
	}
	else if (m_isRestartButtonPressed)
	{
		m_bgm->stopMainMenuMusic();
		m_context->m_states->popCurrent();
		m_context->m_states->add(std::make_unique<GamePlay>(m_context), true);
		m_isRestartButtonPressed = false;
	}
	else if (m_isMainMenuButtonPressed)
	{
		m_context->m_states->popCurrent();
		m_context->m_states->popCurrent();

		m_context->m_states->add(std::make_unique<MainMenu>(m_context, m_bgm->getOverallVolume(), m_bgm->getInGameVolume(), m_bgm->getSFXVolume()), true);
		m_isMainMenuButtonPressed = false;
	}
}

void PauseGame::draw()
{
	m_context->m_window->draw(m_pauseTitle);
	gui.draw();
	m_context->m_window->display();
}

void PauseGame::start()
{
	m_bgm->startMainMenuMusic();
}