#include "../Header Files/MainMenu.h"
#include "SFML/Window/Event.hpp"
#include "../Header Files/GamePlay.h"
#include "../Header Files/ExitState.h"

#include <memory>

MainMenu::MainMenu(std::shared_ptr<Context>& context) : 
	m_context(context), 
	m_isPlayButtonSelected(true),
	m_isPlayButtonPressed(false),
	m_isExitButtonSelected(false),
	m_isExitButtonPressed(false),
	m_bgm(m_context->m_assets->getSoundTrack(MAIN_SOUND_TRACK))
{
}

MainMenu::~MainMenu()
{

}

void MainMenu::init()
{
	m_context->m_assets->addFont(MAIN_FONT, "Resources/fonts/BOMBERMAN.TTF");

	//MENU BACKGROUND 
	m_context->m_assets->addTextures(MENU_BACKGROUND, "Resources/assets/bombmap.png");
	m_menuBackground.setTexture(m_context->m_assets->getTexture(MENU_BACKGROUND));
	m_menuBackground.setPosition(m_context->m_window->getSize().x / 2, m_context->m_window->getSize().y / 2);
	m_menuBackground.setOrigin(sf::Vector2f(m_menuBackground.getTexture()->getSize().x / 2, m_menuBackground.getTexture()->getSize().y / 2));

	//GAME TITLE
	m_gameTitle.setFont(m_context->m_assets->getFont(MAIN_FONT));
	m_gameTitle.setString("AMMPED-UP");
	m_gameTitle.setCharacterSize(50);
	m_gameTitle.setOrigin(m_gameTitle.getLocalBounds().width / 2, m_gameTitle.getLocalBounds().height / 2);
	m_gameTitle.setPosition(m_context->m_window->getSize().x / 2, m_context->m_window->getSize().y / 2 - 150.0f) ;

	//PLAY BUTTON
	m_playButton.setFont(m_context->m_assets->getFont(MAIN_FONT));
	m_playButton.setString("Play");
	m_playButton.setCharacterSize(35);
	m_playButton.setOrigin(m_playButton.getLocalBounds().width / 2, m_playButton.getLocalBounds().height / 2);
	m_playButton.setPosition(m_context->m_window->getSize().x / 2, m_context->m_window->getSize().y / 2 - 25.0f);
	

	//EXIT BUTTON
	m_exitButton.setFont(m_context->m_assets->getFont(MAIN_FONT));
	m_exitButton.setString("Exit");
	m_exitButton.setCharacterSize(35);
	m_exitButton.setOrigin(m_exitButton.getLocalBounds().width / 2, m_exitButton.getLocalBounds().height / 2);
	m_exitButton.setPosition(m_context->m_window->getSize().x / 2, m_context->m_window->getSize().y / 2 + 25.0f);
	

	
}

void MainMenu::processInput()
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
				if (!m_isPlayButtonSelected)
				{
					m_isPlayButtonSelected = true;
					m_isExitButtonSelected = false;
				}
				break;
			}
			
			case sf::Keyboard::Down :
			{
				if (!m_isExitButtonSelected)
				{
					m_isPlayButtonSelected = false;
					m_isExitButtonSelected = true;
				}
				break;
			}
			case sf::Keyboard::Return :
			{
				m_isPlayButtonPressed = false;
				m_isExitButtonPressed = false;
				if (m_isPlayButtonSelected)
				{
					m_isPlayButtonPressed = true;
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

void MainMenu::update(sf::Time deltaTime)
{
	if (m_isPlayButtonSelected)
	{
		m_playButton.setFillColor(sf::Color::Magenta);
		m_exitButton.setFillColor(::sf::Color::White);

	}
	else
	{
		m_exitButton.setFillColor(::sf::Color::Magenta);
		m_playButton.setFillColor(sf::Color::White);

	}

	if (m_isPlayButtonPressed)
	{
		//TODO
		//Go to Play State
		m_bgm.stop();
		m_context->m_states->add(std::make_unique<GamePlay>(m_context), true);

	}
	else if (m_isExitButtonPressed)
	{
		m_context->m_states->add(std::make_unique<ExitState>(m_context), true);
	}
}

void MainMenu::draw()
{
	m_context->m_window->clear();
	m_context->m_window->draw(m_menuBackground);
	m_context->m_window->draw(m_gameTitle);
	m_context->m_window->draw(m_playButton);
	m_context->m_window->draw(m_exitButton);

	m_context->m_window->display();
}

void MainMenu::start()
{
	m_bgm.play();
}

void MainMenu::pause()
{
}
