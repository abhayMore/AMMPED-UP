#include "../Header Files/MainMenu.h"
#include "SFML/Window/Event.hpp"
#include "../Header Files/OptionsState.h"
#include "../Header Files/Leaderboard.h"
#include "../Header Files/GamePlay.h"
#include "../Header Files/ExitState.h"
#include <memory>

MainMenu::MainMenu(std::shared_ptr<Context>& context, float Overallvolume, float inGameMusicVolume, float SFXVolume) :
	m_context(context), 
	m_isPlayButtonSelected(true),
	m_isPlayButtonPressed(false),
	m_isLeadershipButtonSelected(false),
	m_isLeadershipButtonPressed(false),
	m_isOptionsButtonSelected(false),
	m_isOptionsButtonPressed(false),
	m_isExitButtonSelected(false),
	m_isExitButtonPressed(false)
{
	AudioManager& audioManager = AudioManager::getInstance(m_context->m_assets->getSoundTrack(MAIN_SOUND_TRACK), 
														m_context->m_assets->getSoundTrack(IN_GAME_SOUND_TRACK),
														m_context->m_assets->getSoundEffect(DAMAGE_SFX),
														m_context->m_assets->getSoundEffect(BLAST_SFX),
														m_context->m_assets->getSoundEffect(COIN_SFX),
														m_context->m_assets->getSoundEffect(ENEMY_DEATH_SFX)
														);

	m_bgm = &audioManager;
	m_bgm->setOverallVolume(Overallvolume);
	m_bgm->setInGameVolume(inGameMusicVolume);
	m_bgm->setSFXVolume(SFXVolume);
}

MainMenu::~MainMenu()
{
}

void MainMenu::init()
{

	//MENU BACKGROUND 
	m_context->m_assets->addTextures(MENU_BACKGROUND, "Resources/assets/bombmap.png");
	m_menuBackground.setTexture(m_context->m_assets->getTexture(MENU_BACKGROUND));
	m_menuBackground.setPosition(m_context->m_window->getSize().x / 2, m_context->m_window->getSize().y / 2);
	m_menuBackground.setOrigin(sf::Vector2f(m_menuBackground.getTexture()->getSize().x / 2, m_menuBackground.getTexture()->getSize().y / 2));
	m_menuBackground.setScale({ 2,2 });
	
	//GAME TITLE
	m_context->m_assets->addFont(TITLE_FONT, "Resources/fonts/VT323-Regular.TTF");

	m_gameTitle.setFont(m_context->m_assets->getFont(TITLE_FONT));
	m_gameTitle.setString("AMMPED-UP");
	m_gameTitle.setCharacterSize(200);
	m_gameTitle.setOrigin(m_gameTitle.getLocalBounds().width / 2, m_gameTitle.getLocalBounds().height / 2);
	m_gameTitle.setPosition(m_context->m_window->getSize().x / 2, m_context->m_window->getSize().y / 2 - 350.0f) ;
	m_gameTitle.setOutlineThickness(1);

	//PLAY BUTTON
	m_playButton.setFont(m_context->m_assets->getFont(MAIN_FONT));
	m_playButton.setString("Play");
	m_playButton.setCharacterSize(50);
	m_playButton.setOrigin(m_playButton.getLocalBounds().width / 2, m_playButton.getLocalBounds().height / 2);
	m_playButton.setPosition(m_context->m_window->getSize().x / 2, m_context->m_window->getSize().y / 2 - 100.0f);
	m_playButton.setOutlineThickness(1);

	//LEADERSHIP BUTTON
	m_leadershipButton.setFont(m_context->m_assets->getFont(MAIN_FONT));
	m_leadershipButton.setString("Leaderboard");
	m_leadershipButton.setCharacterSize(50);
	m_leadershipButton.setOrigin(m_leadershipButton.getLocalBounds().width / 2, m_leadershipButton.getLocalBounds().height / 2);
	m_leadershipButton.setPosition(m_context->m_window->getSize().x / 2, m_context->m_window->getSize().y / 2 - 25.0f);
	m_leadershipButton.setOutlineThickness(1);

	//OPTIONS BUTTON
	m_optionsButton.setFont(m_context->m_assets->getFont(MAIN_FONT));
	m_optionsButton.setString("Options");
	m_optionsButton.setCharacterSize(50);
	m_optionsButton.setOrigin(m_optionsButton.getLocalBounds().width / 2, m_optionsButton.getLocalBounds().height / 2);
	m_optionsButton.setPosition(m_context->m_window->getSize().x / 2, m_context->m_window->getSize().y / 2 + 50.0f);
	m_optionsButton.setOutlineThickness(1);

	//EXIT BUTTON
	m_exitButton.setFont(m_context->m_assets->getFont(MAIN_FONT));
	m_exitButton.setString("Exit");
	m_exitButton.setCharacterSize(50);
	m_exitButton.setOrigin(m_exitButton.getLocalBounds().width / 2, m_exitButton.getLocalBounds().height / 2);
	m_exitButton.setPosition(m_context->m_window->getSize().x / 2, m_context->m_window->getSize().y / 2 + 125.0f);
	m_exitButton.setOutlineThickness(1);
	
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
				if (!m_isLeadershipButtonSelected && !m_isExitButtonSelected && !m_isPlayButtonSelected)
				{
					m_isPlayButtonSelected = false;
					m_isLeadershipButtonSelected = true;
					m_isOptionsButtonSelected = false;
					m_isExitButtonSelected = false;
				}
				else if(!m_isPlayButtonSelected && !m_isExitButtonSelected)
				{
					m_isPlayButtonSelected = true;
					m_isLeadershipButtonSelected = false;
					m_isOptionsButtonSelected = false;
					m_isExitButtonSelected = false;
				} 
				else if (!m_isOptionsButtonSelected && !m_isPlayButtonSelected)
				{
					m_isPlayButtonSelected = false;
					m_isLeadershipButtonSelected = false;
					m_isOptionsButtonSelected = true;
					m_isExitButtonSelected = false;
				}
				else if (!m_isExitButtonSelected && !m_isPlayButtonSelected)
				{
					m_isPlayButtonSelected = false;
					m_isLeadershipButtonSelected = false;
					m_isOptionsButtonSelected = false;
					m_isExitButtonSelected = true;
				}
				break;
			}
			
			case sf::Keyboard::Down :
			{
				if (!m_isLeadershipButtonSelected && !m_isOptionsButtonSelected && !m_isExitButtonSelected)
				{
					m_isPlayButtonSelected = false;
					m_isLeadershipButtonSelected = true;
					m_isOptionsButtonSelected = false;
					m_isExitButtonSelected = false;
				}
				else if (!m_isOptionsButtonSelected && !m_isExitButtonSelected)
				{
					m_isPlayButtonSelected = false;
					m_isLeadershipButtonSelected = false;
					m_isOptionsButtonSelected = true;
					m_isExitButtonSelected = false;
				}
				
				else if (!m_isExitButtonSelected )
				{
					m_isPlayButtonSelected = false;
					m_isLeadershipButtonSelected = false;
					m_isOptionsButtonSelected = false;
					m_isExitButtonSelected = true;
				}
				else if (!m_isPlayButtonSelected && !m_isExitButtonSelected)
				{
					m_isPlayButtonSelected = true;
					m_isLeadershipButtonSelected = false;
					m_isOptionsButtonSelected = false;
					m_isExitButtonSelected = false;
				}
				break;
			}
			case sf::Keyboard::Return :
			{
				m_isPlayButtonPressed = false;
				m_isExitButtonPressed = false;
				m_isLeadershipButtonPressed = false;
				m_isOptionsButtonPressed = false;
				if (m_isPlayButtonSelected)
				{
					m_isPlayButtonPressed = true;
				}
				else if (m_isLeadershipButtonSelected)
				{
					m_isLeadershipButtonPressed = true;
				}
				else if (m_isOptionsButtonSelected)
				{
					m_isOptionsButtonPressed = true;
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
		m_leadershipButton.setFillColor(sf::Color::White);
		m_optionsButton.setFillColor(sf::Color::White);
		m_exitButton.setFillColor(sf::Color::White);
	}
	else if (m_isLeadershipButtonSelected)
	{
		m_playButton.setFillColor(sf::Color::White);
		m_leadershipButton.setFillColor(sf::Color::Magenta);
		m_optionsButton.setFillColor(sf::Color::White);
		m_exitButton.setFillColor(sf::Color::White);
	}
	else if (m_isOptionsButtonSelected)
	{
		m_playButton.setFillColor(sf::Color::White);
		m_leadershipButton.setFillColor(sf::Color::White);
		m_optionsButton.setFillColor(sf::Color::Magenta);
		m_exitButton.setFillColor(sf::Color::White);
	}
	else 
	{
		m_exitButton.setFillColor(sf::Color::Magenta);
		m_playButton.setFillColor(sf::Color::White);
		m_leadershipButton.setFillColor(sf::Color::White);
		m_optionsButton.setFillColor(sf::Color::White);
	}
	if (m_isPlayButtonPressed)
	{
		//TODO
		//Go to Play State
		m_bgm->stopMainMenuMusic();
		m_context->m_states->add(std::make_unique<GamePlay>(m_context), true);
	}
	else if (m_isLeadershipButtonPressed)
	{
		m_context->m_states->add(std::make_unique<Leaderboard>(m_context), true);
	}
	else if (m_isOptionsButtonPressed)
	{
		m_context->m_states->add(std::make_unique<OptionsState>(m_context), true);
	}
	else if (m_isExitButtonPressed)
	{
		m_context->m_states->add(std::make_unique<ExitState>(m_context), true);
	}
	if (m_bgm->isMenuMusicPlaying() == sf::SoundStream::Status::Stopped && !m_isPlayButtonPressed)
	{
		m_bgm->startMainMenuMusic();
	}
}

void MainMenu::draw()
{
	m_context->m_window->clear();
	m_context->m_window->draw(m_menuBackground);
	m_context->m_window->draw(m_gameTitle);
	m_context->m_window->draw(m_playButton);
	m_context->m_window->draw(m_leadershipButton);
	m_context->m_window->draw(m_optionsButton);
	m_context->m_window->draw(m_exitButton);

	m_context->m_window->display();
}

void MainMenu::start()
{
}

void MainMenu::pause()
{
}