#include "../Header Files/MainMenu.h"
#include "SFML/Window/Event.hpp"
#include "../Header Files/SettingsState.h"
#include "../Header Files/Leaderboard.h"
#include "../Header Files/GamePlay.h"
#include "../Header Files/ExitState.h"
#include <memory>

enum buttonValues
{
	PLAY,
	LEADERBOARD,
	SETTINGS,
	EXIT
};

MainMenu::MainMenu(std::shared_ptr<Context>& context, float Overallvolume, float inGameMusicVolume, float SFXVolume) :
	m_context(context), 
	m_isPlayButtonPressed(false),
	m_isLeaderboardButtonPressed(false),
	m_isSettingsButtonPressed(false),
	m_isExitButtonPressed(false),
	gui(*m_context->m_window)
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

	theme.load("Resources/Black.txt");

}

MainMenu::~MainMenu()
{
	std::cout << "desc called" << std::endl;
	m_bgm->stopMainMenuMusic();

}

void MainMenu::init()
{
	//MENU BACKGROUND 
	m_context->m_assets->addTextures(MENU_BACKGROUND, "Resources/assets/bombmap.png");
	m_menuBackground.setTexture(m_context->m_assets->getTexture(MENU_BACKGROUND));
	m_menuBackground.setPosition(static_cast<float>(m_context->m_window->getSize().x / 2), static_cast<float>(m_context->m_window->getSize().y / 2));
	m_menuBackground.setOrigin(sf::Vector2f(static_cast<float>(m_menuBackground.getTexture()->getSize().x / 2), static_cast<float>(m_menuBackground.getTexture()->getSize().y / 2)));
	m_menuBackground.setScale({ 2,2 });
	
	//GAME TITLE
	m_context->m_assets->addFont(TITLE_FONT, "Resources/fonts/VT323-Regular.TTF");

	m_gameTitle.setFont(m_context->m_assets->getFont(TITLE_FONT));
	m_gameTitle.setString("AMMPED-UP");
	m_gameTitle.setCharacterSize(200);
	m_gameTitle.setOrigin(m_gameTitle.getLocalBounds().width / 2, m_gameTitle.getLocalBounds().height / 2);
	m_gameTitle.setPosition(static_cast<float>(m_context->m_window->getSize().x / 2), static_cast<float>(m_context->m_window->getSize().y / 2) - 350.0f) ;
	m_gameTitle.setOutlineThickness(1);

	//////////////////////////////////////////////////
	m_context->m_assets->addGuiFont(MAIN_FONT, "Resources/fonts/BungeeSpice-Regular.TTF");

	for (int i = 0; i < 4; i++)
	{
		m_pageButtons[i] = tgui::Button::create();
		m_pageButtons[i]->getRenderer()->setBackgroundColor(tgui::Color::Transparent);
		m_pageButtons[i]->getRenderer()->setBorderColor(tgui::Color::Transparent);
		m_pageButtons[i]->getRenderer()->setTextColor(tgui::Color::White);
		m_pageButtons[i]->getRenderer()->setFont(tgui::Font(m_context->m_assets->getGuiFont(MAIN_FONT).getId()));
		m_pageButtons[i]->setTextSize(50);
		if (i == PLAY)
		{
			m_pageButtons[i]->setText("PLAY");
			m_pageButtons[i]->setPosition(m_context->m_window->getSize().x / 2 - m_pageButtons[i]->getSize().x / 2, m_context->m_window->getSize().y / 2 - 150.0f);
			m_pageButtons[i]->setFocused(true);
			m_pageButtons[i]->getRenderer()->setTextColorFocused(tgui::Color::Magenta);
			m_pageButtons[i]->getRenderer()->setBorderColorFocused(tgui::Color::Transparent);
		}
		else if (i == LEADERBOARD)
		{
			m_pageButtons[i]->setText("LEADERBOARD");
			m_pageButtons[i]->setPosition(m_context->m_window->getSize().x / 2 - m_pageButtons[i]->getSize().x / 2, m_context->m_window->getSize().y / 2 - 75.0f);
			m_pageButtons[i]->getRenderer()->setTextColorFocused(tgui::Color::Magenta);
			m_pageButtons[i]->getRenderer()->setBorderColorFocused(tgui::Color::Transparent);
		}
		else if (i == SETTINGS)
		{
			m_pageButtons[i]->setText("SETTINGS");
			m_pageButtons[i]->setPosition(m_context->m_window->getSize().x / 2 - m_pageButtons[i]->getSize().x / 2, m_context->m_window->getSize().y / 2);
			m_pageButtons[i]->getRenderer()->setTextColorFocused(tgui::Color::Magenta);
			m_pageButtons[i]->getRenderer()->setBorderColorFocused(tgui::Color::Transparent);
		}
		else if (i == EXIT)
		{
			m_pageButtons[i]->setText("EXIT");
			m_pageButtons[i]->setPosition(m_context->m_window->getSize().x / 2 - m_pageButtons[i]->getSize().x / 2, m_context->m_window->getSize().y / 2 + 75.0f);
			m_pageButtons[i]->getRenderer()->setTextColorFocused(tgui::Color::Magenta);
			m_pageButtons[i]->getRenderer()->setBorderColorFocused(tgui::Color::Transparent);
		}
		m_pageButtons[i]->getRenderer()->setTextOutlineThickness(1);
		gui.add(m_pageButtons[i]);
	}
}

void MainMenu::processInput()
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
					m_isPlayButtonPressed = true;
				}
				if (m_pageButtons[1]->isMouseOnWidget({ mouseX, mouseY })
					&& m_pageButtons[1]->isFocused())
				{
					m_isLeaderboardButtonPressed = true;
				}
				if (m_pageButtons[2]->isMouseOnWidget({ mouseX, mouseY })
					&& m_pageButtons[2]->isFocused())
				{
					m_isSettingsButtonPressed = true;
				}
				if (m_pageButtons[3]->isMouseOnWidget({ mouseX, mouseY })
					&& m_pageButtons[3]->isFocused())
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
				m_pageButtons[3]->setFocused(false);
			}
			else if (m_pageButtons[1]->isMouseOnWidget({ mouseX, mouseY }))
			{
				m_pageButtons[1]->setFocused(true);
				m_pageButtons[0]->setFocused(false);
				m_pageButtons[2]->setFocused(false);
				m_pageButtons[3]->setFocused(false);
			}
			else if (m_pageButtons[2]->isMouseOnWidget({ mouseX, mouseY }))
			{
				m_pageButtons[2]->setFocused(true);
				m_pageButtons[0]->setFocused(false);
				m_pageButtons[1]->setFocused(false);
				m_pageButtons[3]->setFocused(false);
			}
			else if (m_pageButtons[3]->isMouseOnWidget({ mouseX, mouseY }))
			{
				m_pageButtons[3]->setFocused(true);
				m_pageButtons[0]->setFocused(false);
				m_pageButtons[1]->setFocused(false);
				m_pageButtons[2]->setFocused(false);
			}
			break;
		}
		case sf::Event::KeyPressed:
		{
			switch (event.key.code)
			{
			case sf::Keyboard::Up:
			{
				if (m_pageButtons[3]->isFocused())
				{
					m_pageButtons[2]->setFocused(true);
					m_pageButtons[2]->getRenderer()->setTextColorFocused(tgui::Color::Magenta);
					m_pageButtons[2]->getRenderer()->setBorderColorFocused(tgui::Color::Transparent);
					m_pageButtons[3]->setFocused(false);
				}
				else if (m_pageButtons[2]->isFocused())
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
				else if (m_pageButtons[2]->isFocused())
				{
					m_pageButtons[3]->setFocused(true);
					m_pageButtons[3]->getRenderer()->setTextColorFocused(tgui::Color::Magenta);
					m_pageButtons[3]->getRenderer()->setBorderColorFocused(tgui::Color::Transparent);
					m_pageButtons[2]->setFocused(false);
				}
				break;
			}
			case sf::Keyboard::Return:
			{
				if (m_pageButtons[0]->isFocused())
				{
					m_isPlayButtonPressed = true;
				}
				else if (m_pageButtons[1]->isFocused())
				{
					m_isLeaderboardButtonPressed = true;
				}
				else if (m_pageButtons[2]->isFocused())
				{
					m_isSettingsButtonPressed = true;
				}
				else if (m_pageButtons[3]->isFocused())
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

void MainMenu::update(sf::Time deltaTime)
{
	if (m_isPlayButtonPressed)
	{
		//TODO
		//Go to Play State
		m_bgm->stopMainMenuMusic();
		m_context->m_states->add(std::make_unique<GamePlay>(m_context), true);
		m_isPlayButtonPressed = false;
	}
	else if (m_isLeaderboardButtonPressed)
	{
		m_context->m_states->add(std::make_unique<Leaderboard>(m_context));
		m_isLeaderboardButtonPressed = false;
	}
	else if (m_isSettingsButtonPressed)
	{
		m_context->m_states->add(std::make_unique<SettingsState>(m_context));
		m_isSettingsButtonPressed = false;
	}
	else if (m_isExitButtonPressed)
	{
		m_context->m_states->add(std::make_unique<ExitState>(m_context));
		m_isExitButtonPressed = false;
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
	gui.draw();
	m_context->m_window->display();
}

void MainMenu::start()
{
}

void MainMenu::pause()
{
}