#include "../Header Files/GameOver.h"
#include "SFML/Window/Event.hpp"
#include "../Header Files/GamePlay.h"
#include "../Header Files/MainMenu.h"
#include <iostream>

enum buttonValues
{
	RETRY,
	MAINMENU
};

GameOver::GameOver(std::shared_ptr<Context>& context, std::string currentState) :
	m_context(context),
	m_currentGameState(currentState),
	m_isRetryButtonPressed(false),
	m_isMainmenuButtonPressed(false),
	gui(*m_context->m_window)
{
	theme.load("Resources/Black.txt");
	m_finalScore = ScoreManager::getInstance();
	m_userName = UserNameManager::getInstance();

	AudioManager& audioManager = AudioManager::getInstance(
		m_context->m_assets->getSoundTrack(MAIN_SOUND_TRACK),
		m_context->m_assets->getSoundTrack(IN_GAME_SOUND_TRACK),
		m_context->m_assets->getSoundEffect(DAMAGE_SFX),
		m_context->m_assets->getSoundEffect(BLAST_SFX),
		m_context->m_assets->getSoundEffect(COIN_SFX),
		m_context->m_assets->getSoundEffect(ENEMY_DEATH_SFX)
	);
	m_bgm = &audioManager;

	if (m_currentGameState == "You Won!!") {
			
		int currentScore = m_finalScore->getScore();
		int playerScore = m.findScore(m_userName->getUsername());
		if (currentScore > playerScore)
		{
			m.updateDocument(m_userName->getUsername(),"score", currentScore);
		}
		else
		{
			m_finalScore->setScore(currentScore);
		}
	}
}

GameOver::~GameOver()
{
}

void GameOver::init()
{
	//GAME OVER BACKGROUND
	m_context->m_assets->addTextures(MENU_BACKGROUND, "Resources/assets/bombmap.png");
	m_gameOverBackground.setTexture(m_context->m_assets->getTexture(MENU_BACKGROUND));
	m_gameOverBackground.setPosition(static_cast<float>(m_context->m_window->getSize().x / 2), static_cast<float>(m_context->m_window->getSize().y / 2));
	m_gameOverBackground.setOrigin(sf::Vector2f(static_cast<float>(m_gameOverBackground.getTexture()->getSize().x / 2), static_cast<float>(m_gameOverBackground.getTexture()->getSize().y / 2)));
	m_gameOverBackground.setScale({ 2,2 });

	//GAME TITLE
	m_gameOverTitle.setFont(m_context->m_assets->getFont(MAIN_FONT));
	m_gameOverTitle.setString("Game Over");
	m_gameOverTitle.setCharacterSize(50);
	m_gameOverTitle.setOrigin(m_gameOverTitle.getLocalBounds().width / 2, m_gameOverTitle.getLocalBounds().height / 2);
	m_gameOverTitle.setPosition(static_cast<float>(m_context->m_window->getSize().x / 2), static_cast<float>(m_context->m_window->getSize().y / 2) - 300.0f);
	m_gameOverTitle.setOutlineThickness(1);

	//CURRENT GAME STATE TEXT -> WON, TIME's UP, DIED..
	m_currentGameStateTitle.setFont(m_context->m_assets->getFont(MAIN_FONT));
	m_currentGameStateTitle.setString(m_currentGameState);
	if (m_currentGameState == "You Won!!")
	{
		m_currentGameStateTitle.setFillColor(sf::Color(255, 215, 0));
		m_currentGameStateTitle.setOutlineColor(sf::Color(255, 255, 0));

	}
	else if (m_currentGameState == "Time's Up!!")
	{
		m_currentGameStateTitle.setFillColor(sf::Color(8, 143, 143));
		m_currentGameStateTitle.setOutlineColor(sf::Color(255, 255, 0));


	}
	else if (m_currentGameState == "You Died!!")
	{
		m_currentGameStateTitle.setFillColor(sf::Color(255, 36, 0));
		m_currentGameStateTitle.setOutlineColor(sf::Color(255, 255, 0));

	}
	m_currentGameStateTitle.setCharacterSize(45);
	m_currentGameStateTitle.setOrigin(m_currentGameStateTitle.getLocalBounds().width / 2, m_currentGameStateTitle.getLocalBounds().height / 2);
	m_currentGameStateTitle.setPosition(static_cast<float>(m_context->m_window->getSize().x / 2), static_cast<float>(m_context->m_window->getSize().y / 2) - 200.0f);
	m_currentGameStateTitle.setOutlineThickness(1);
;

	//SCORE TEXT AFTER GAME OVER
	m_scoreText.setFont(m_context->m_assets->getFont(MAIN_FONT));
	auto tempFinalScore = m_finalScore->getScore();
	m_scoreText.setString("Score : " + std::to_string(tempFinalScore));
	m_scoreText.setCharacterSize(35);
	m_scoreText.setOrigin(m_scoreText.getLocalBounds().width / 2, m_scoreText.getLocalBounds().height / 2);
	m_scoreText.setPosition(static_cast<float>(m_context->m_window->getSize().x / 2), static_cast<float>(m_context->m_window->getSize().y / 2) - 75.0f);
	m_scoreText.setOutlineThickness(1);

	m_highScoreText.setFont(m_context->m_assets->getFont(MAIN_FONT));
	m_highScoreText.setString("High Score : " + std::to_string(m.findScore(m_userName->getUsername())));
	m_highScoreText.setCharacterSize(35);
	m_highScoreText.setOrigin(m_highScoreText.getLocalBounds().width / 2, m_highScoreText.getLocalBounds().height / 2);
	m_highScoreText.setPosition(static_cast<float>(m_context->m_window->getSize().x / 2), static_cast<float>(m_context->m_window->getSize().y / 2) - 25.0f);
	m_highScoreText.setOutlineThickness(1);


	///////////////////////////////////////////////////
	m_context->m_assets->addGuiFont(MAIN_FONT, "Resources/fonts/BungeeSpice-Regular.TTF");

	for (int i = 0; i < 2; i++)
	{
		m_pageButtons[i] = tgui::Button::create();
		m_pageButtons[i]->getRenderer()->setBackgroundColor(tgui::Color::Transparent);
		m_pageButtons[i]->getRenderer()->setBorderColor(tgui::Color::Transparent);
		m_pageButtons[i]->getRenderer()->setTextColor(tgui::Color::White);
		m_pageButtons[i]->getRenderer()->setFont(tgui::Font(m_context->m_assets->getGuiFont(MAIN_FONT).getId()));
		m_pageButtons[i]->setTextSize(35);
		if (i == RETRY)
		{
			m_pageButtons[i]->setText("RETRY");
			m_pageButtons[i]->setPosition(m_context->m_window->getSize().x / 2 - m_pageButtons[i]->getSize().x / 2, m_context->m_window->getSize().y / 2 + 25.0f);
			m_pageButtons[i]->setFocused(true);
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


	
	m_deathSfx.setBuffer(m_context->m_assets->getSoundEffect(DEATH_SFX));
	m_deathSfx.setVolume(10);

	
}

void GameOver::processInput()
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
					m_isRetryButtonPressed = true;
				}
				if (m_pageButtons[1]->isMouseOnWidget({ mouseX, mouseY })
					&& m_pageButtons[1]->isFocused())
				{
					m_isMainmenuButtonPressed = true;
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
			}
			else if (m_pageButtons[1]->isMouseOnWidget({ mouseX, mouseY }))
			{
				m_pageButtons[1]->setFocused(true);
				m_pageButtons[0]->setFocused(false);
			}
			break;
		}
		case sf::Event::KeyPressed:
		{
			switch (event.key.code)
			{
			case sf::Keyboard::Up:
			{
				if (m_pageButtons[1]->isFocused())
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
				break;
			}
			case sf::Keyboard::Enter:
			{
				if (m_pageButtons[0]->isFocused())
				{
					m_isRetryButtonPressed = true;
				}
				else if (m_pageButtons[1]->isFocused())
				{
					m_isMainmenuButtonPressed = true;
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

void GameOver::update(sf::Time deltaTime)
{
	if (m_isRetryButtonPressed)
	{
		//TODO
		//Go to Play State
		m_finalScore->setScore(0);
		m_bgm->stopMainMenuMusic();
		m_context->m_states->add(std::make_unique<GamePlay>(m_context), true);
		m_isRetryButtonPressed = false;
	}
	else if (m_isMainmenuButtonPressed)
	{
		m_context->m_states->add(std::make_unique<MainMenu>(m_context, m_bgm->getOverallVolume(), m_bgm->getInGameVolume(), m_bgm->getSFXVolume()), true);
		m_isMainmenuButtonPressed = false;

	}
}

void GameOver::draw()
{
	m_context->m_window->clear();
	m_context->m_window->draw(m_gameOverBackground);
	m_context->m_window->draw(m_gameOverTitle);
	m_context->m_window->draw(m_currentGameStateTitle);
	m_context->m_window->draw(m_scoreText);
	m_context->m_window->draw(m_highScoreText);

	gui.draw();

	m_context->m_window->display();
}

void GameOver::start()
{
	m_bgm->startMainMenuMusic();
	if (m_currentGameState != "You Won!!")
	{
		m_bgm->startSFXMusic(ENEMY_DEATH_SFX_SOUND);
	}
}