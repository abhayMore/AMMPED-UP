#include "../Header Files/GameOver.h"
#include "SFML/Window/Event.hpp"
#include "../Header Files/GamePlay.h"

GameOver::GameOver(std::shared_ptr<Context>& context) :
	m_context(context),
	m_isRetryButtonSelected(true),
	m_isRetryButtonPressed(false),
	m_isExitButtonSelected(false),
	m_isExitButtonPressed(false),
	m_bgm(m_context->m_assets->getSoundTrack(MAIN_SOUND_TRACK))
{
}

GameOver::~GameOver()
{
}

void GameOver::init()
{
	//GAME TITLE
	m_gameOverTitle.setFont(m_context->m_assets->getFont(MAIN_FONT));
	m_gameOverTitle.setString("Game Over");
	m_gameOverTitle.setCharacterSize(50);
	m_gameOverTitle.setOrigin(m_gameOverTitle.getLocalBounds().width / 2, m_gameOverTitle.getLocalBounds().height / 2);
	m_gameOverTitle.setPosition(m_context->m_window->getSize().x / 2, m_context->m_window->getSize().y / 2 - 150.0f);

	//PLAY BUTTON
	m_retryButton.setFont(m_context->m_assets->getFont(MAIN_FONT));
	m_retryButton.setString("Retry");
	m_retryButton.setCharacterSize(35);
	m_retryButton.setOrigin(m_retryButton.getLocalBounds().width / 2, m_retryButton.getLocalBounds().height / 2);
	m_retryButton.setPosition(m_context->m_window->getSize().x / 2, m_context->m_window->getSize().y / 2 - 25.0f);

	//EXIT BUTTON
	m_exitButton.setFont(m_context->m_assets->getFont(MAIN_FONT));
	m_exitButton.setString("Exit");
	m_exitButton.setCharacterSize(35);
	m_exitButton.setOrigin(m_exitButton.getLocalBounds().width / 2, m_exitButton.getLocalBounds().height / 2);
	m_exitButton.setPosition(m_context->m_window->getSize().x / 2, m_context->m_window->getSize().y / 2 + 25.0f);

	
	m_deathSfx.setBuffer(m_context->m_assets->getSoundEffect(DEATH_SFX));
	m_deathSfx.setVolume(10);

}

void GameOver::processInput()
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
				if (!m_isRetryButtonSelected)
				{
					m_isRetryButtonSelected = true;
					m_isExitButtonSelected = false;
				}
				break;
			}

			case sf::Keyboard::Down:
			{
				if (!m_isExitButtonSelected)
				{
					m_isRetryButtonSelected = false;
					m_isExitButtonSelected = true;
				}
				break;
			}
			case sf::Keyboard::Return:
			{
				m_isRetryButtonPressed = false;
				m_isExitButtonPressed = false;
				if (m_isRetryButtonSelected)
				{
					m_isRetryButtonPressed = true;
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

void GameOver::update(sf::Time deltaTime)
{
	if (m_isRetryButtonSelected)
	{
		m_retryButton.setFillColor(sf::Color::Magenta);
		m_exitButton.setFillColor(::sf::Color::White);

	}
	else
	{
		m_exitButton.setFillColor(::sf::Color::Magenta);
		m_retryButton.setFillColor(sf::Color::White);

	}

	if (m_isRetryButtonPressed)
	{
		//TODO
		//Go to Play State
		m_bgm.stop();
		m_context->m_states->add(std::make_unique<GamePlay>(m_context), true);
	}
	else if (m_isExitButtonPressed)
	{
		m_context->m_window->close();
	}
}

void GameOver::draw()
{
	m_context->m_window->clear(sf::Color(14, 134, 212));
	m_context->m_window->draw(m_gameOverTitle);
	m_context->m_window->draw(m_retryButton);
	m_context->m_window->draw(m_exitButton);

	m_context->m_window->display();
}

void GameOver::start()
{
	m_bgm.play();
	m_deathSfx.play();
}
