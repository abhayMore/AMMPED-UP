#include "../Header Files/PauseGame.h"
#include "../Header Files/MainMenu.h"
#include "SFML/Window/Event.hpp"
#include "../Header Files/GamePlay.h"
#include <memory>

PauseGame::PauseGame(std::shared_ptr<Context>& context) : m_context(context), m_bgm(m_context->m_assets->getSoundTrack(MAIN_SOUND_TRACK)),
m_isResumeButtonSelected(true),
m_isResumeButtonPressed(false),
m_isRestartButtonSelected(false),
m_isRestartButtonPressed(false),
m_isMainMenuButtonSelected(false),
m_isMainMenuButtonPressed(false)
{
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
	m_pauseTitle.setPosition(m_context->m_window->getSize().x / 2, m_context->m_window->getSize().y / 2 - 150.0f);
	m_pauseTitle.setOrigin(m_pauseTitle.getLocalBounds().width / 2, m_pauseTitle.getLocalBounds().height / 2);

	//RESUME
	m_resumeButton.setFont(m_context->m_assets->getFont(MAIN_FONT));
	m_resumeButton.setString("Resume");
	m_resumeButton.setCharacterSize(35);
	m_resumeButton.setOrigin(m_resumeButton.getLocalBounds().width / 2, m_resumeButton.getLocalBounds().height / 2);
	m_resumeButton.setPosition(m_context->m_window->getSize().x / 2, m_context->m_window->getSize().y / 2 - 75.0f);

	//RESTART TITLE
	m_restartButton.setFont(m_context->m_assets->getFont(MAIN_FONT));
	m_restartButton.setString("Restart");
	m_restartButton.setCharacterSize(35);
	m_restartButton.setOrigin(m_restartButton.getLocalBounds().width / 2, m_restartButton.getLocalBounds().height / 2);
	m_restartButton.setPosition(m_context->m_window->getSize().x / 2, m_context->m_window->getSize().y / 2 - 25.0f);

	//MAINMENU TITLE
	m_mainMenuButton.setFont(m_context->m_assets->getFont(MAIN_FONT));
	m_mainMenuButton.setString("Main Menu");
	m_mainMenuButton.setCharacterSize(35);
	m_mainMenuButton.setOrigin(m_mainMenuButton.getLocalBounds().width / 2, m_mainMenuButton.getLocalBounds().height / 2);
	m_mainMenuButton.setPosition(m_context->m_window->getSize().x / 2, m_context->m_window->getSize().y / 2 + 25.0f);
}

void PauseGame::processInput()
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
			case sf::Keyboard::Escape:
			{
				m_bgm.stop();
				m_context->m_states->popCurrent();
				break;
			}
			case sf::Keyboard::Up:
			{
				if (!m_isRestartButtonSelected && !m_isResumeButtonSelected)
				{
					m_isResumeButtonSelected = false;
					m_isRestartButtonSelected = true;
					m_isMainMenuButtonSelected = false;
				}
				else if (!m_isResumeButtonSelected)
				{
					m_isResumeButtonSelected = true;
					m_isRestartButtonSelected = false;
					m_isMainMenuButtonSelected = false;
				}
				else if (!m_isMainMenuButtonSelected && !m_isResumeButtonSelected)
				{
					m_isResumeButtonSelected = false;
					m_isRestartButtonSelected = false;
					m_isMainMenuButtonSelected = true;
				}
				break;
			}

			case sf::Keyboard::Down:
			{
				if (!m_isRestartButtonSelected && !m_isMainMenuButtonSelected)
				{
					m_isResumeButtonSelected = false;
					m_isRestartButtonSelected = true;
					m_isMainMenuButtonSelected = false;
				}
				else if (!m_isMainMenuButtonSelected)
				{
					m_isResumeButtonSelected = false;
					m_isRestartButtonSelected = false;
					m_isMainMenuButtonSelected = true;
				}
				else if (!m_isResumeButtonSelected && !m_isMainMenuButtonSelected)
				{
					m_isResumeButtonSelected = true;
					m_isRestartButtonSelected = false;
					m_isMainMenuButtonSelected = false;
				}
				break;
			}
			case sf::Keyboard::Return:
			{
				m_isResumeButtonPressed = false;
				m_isRestartButtonPressed = false;
				m_isMainMenuButtonPressed = false;
				if (m_isResumeButtonSelected)
				{
					m_isResumeButtonPressed = true;
				}
				else if (m_isRestartButtonSelected)
				{
					m_isRestartButtonPressed = true;
				}
				else
				{
					m_isMainMenuButtonPressed = true;
				}
				break;
			}
			default:
				break;
			}
		}
	}
}

void PauseGame::update(sf::Time deltaTime)
{	
	if (m_isResumeButtonSelected)
	{
		m_resumeButton.setFillColor(sf::Color::Magenta);
		m_restartButton.setFillColor(::sf::Color::White);
		m_mainMenuButton.setFillColor(::sf::Color::White);
	}
	else if (m_isRestartButtonSelected)
	{
		m_resumeButton.setFillColor(sf::Color::White);
		m_restartButton.setFillColor(::sf::Color::Magenta);
		m_mainMenuButton.setFillColor(::sf::Color::White);
	}
	else
	{
		m_resumeButton.setFillColor(sf::Color::White);
		m_restartButton.setFillColor(::sf::Color::White);
		m_mainMenuButton.setFillColor(::sf::Color::Magenta);
	}
	if (m_isResumeButtonPressed)
	{
		//TODO
		//Go to Play State
		m_bgm.stop();
		m_context->m_states->popCurrent();
	}
	else if (m_isRestartButtonPressed)
	{
		m_bgm.stop();
		m_context->m_states->popCurrent();
		m_context->m_states->add(std::make_unique<GamePlay>(m_context), true);
	}
	else if (m_isMainMenuButtonPressed)
	{
		m_bgm.stop();
		m_context->m_states->popCurrent();
		m_context->m_states->popCurrent();
		m_context->m_states->add(std::make_unique<MainMenu>(m_context), true);
	}
}

void PauseGame::draw()
{
	m_context->m_window->draw(m_pauseTitle);
	m_context->m_window->draw(m_resumeButton);

	m_context->m_window->draw(m_restartButton);
	m_context->m_window->draw(m_mainMenuButton);

	m_context->m_window->display();
}

void PauseGame::start()
{
	m_bgm.play();
}