#include "../Header Files/Leaderboard.h"
#include "SFML/Window/Event.hpp"
#include "../Header Files/MainMenu.h"
#include <iostream>

Leaderboard::Leaderboard(std::shared_ptr<Context>& context) :
	m_context(context), 
	m_isExitButtonPressed(false)
{

	username = UserNameManager::getInstance();
	
	int score = m.findScore(username->getUsername());
	m_scoreText.setString(std::to_string(score));

	AudioManager& audioManager = AudioManager::getInstance(
		m_context->m_assets->getSoundTrack(MAIN_SOUND_TRACK),
		m_context->m_assets->getSoundTrack(IN_GAME_SOUND_TRACK),
		m_context->m_assets->getSoundEffect(DAMAGE_SFX),
		m_context->m_assets->getSoundEffect(BLAST_SFX),
		m_context->m_assets->getSoundEffect(COIN_SFX),
		m_context->m_assets->getSoundEffect(ENEMY_DEATH_SFX)
		);
	m_bgm = &audioManager;

	auto tempCount = m.getDocumentCount() > 10 ? 10 : m.getDocumentCount();
	m_TopTenScores = m.getTopScores(tempCount);
	//std::cout << "total number : " << m.getDocumentCount() << std::endl;

}

Leaderboard::~Leaderboard()
{
}

void Leaderboard::init()
{

	//MENU BACKGROUND 
	m_context->m_assets->addTextures(MENU_BACKGROUND, "Resources/assets/bombmap.png");
	m_menuBackground.setTexture(m_context->m_assets->getTexture(MENU_BACKGROUND));
	m_menuBackground.setPosition(static_cast<float>(m_context->m_window->getSize().x / 2), static_cast<float>(m_context->m_window->getSize().y / 2));
	m_menuBackground.setOrigin(sf::Vector2f(static_cast<float>(m_menuBackground.getTexture()->getSize().x / 2), static_cast<float>(m_menuBackground.getTexture()->getSize().y / 2)));
	m_menuBackground.setScale({ 2,2 });

	//LEADERBOARD TITLE
	m_gameTitle.setFont(m_context->m_assets->getFont(MAIN_FONT));
	m_gameTitle.setString("LEADERBOARD");
	m_gameTitle.setCharacterSize(50);
	m_gameTitle.setOrigin(m_gameTitle.getLocalBounds().width / 2, m_gameTitle.getLocalBounds().height / 2);
	m_gameTitle.setPosition(static_cast<float>(m_context->m_window->getSize().x / 2), static_cast<float>(m_context->m_window->getSize().y / 2) - 340.0f) ;
	m_gameTitle.setOutlineThickness(1);

	m_name.setFont(m_context->m_assets->getFont(MAIN_FONT));
	m_name.setString(username->getUsername());
	m_name.setCharacterSize(25);
	m_name.setOrigin(m_name.getLocalBounds().width / 2, m_name.getLocalBounds().height / 2);
	m_name.setPosition(static_cast<float>(m_context->m_window->getSize().x / 2) - 100, static_cast<float>(m_context->m_window->getSize().y / 2) - 275.0f);
	m_name.setOutlineThickness(1);

	m_scoreText.setFont(m_context->m_assets->getFont(MAIN_FONT));
	m_scoreText.setCharacterSize(25);
	m_scoreText.setOrigin(m_scoreText.getLocalBounds().width / 2, m_scoreText.getLocalBounds().height / 2);
	m_scoreText.setPosition(static_cast<float>(m_context->m_window->getSize().x / 2) + 100.0f, static_cast<float>(m_context->m_window->getSize().y / 2) - 275.0f);
	m_scoreText.setOutlineThickness(1);

	for (int i = 0; i < m_TopTenScores.size(); i++)
	{
		m_TopTenPlayerNames[i].setFont(m_context->m_assets->getFont(LOGIN_FONT));
		m_TopTenPlayerNames[i].setCharacterSize(25);
		m_TopTenPlayerNames[i].setString(m_TopTenScores[i].first);
		m_TopTenPlayerNames[i].setOutlineThickness(1);
		m_TopTenPlayerNames[i].setOrigin(m_TopTenPlayerNames[i].getLocalBounds().width / 2, m_TopTenPlayerNames[i].getLocalBounds().height / 2);
		m_TopTenPlayerNames[i].setPosition(static_cast<float>(m_context->m_window->getSize().x / 2) - 100.0f, static_cast<float>(m_context->m_window->getSize().y / 2) + static_cast<float>(i*50)- 225.0f);

		m_TopTenPlayerScores[i].setFont(m_context->m_assets->getFont(LOGIN_FONT));
		m_TopTenPlayerScores[i].setCharacterSize(25);
		m_TopTenPlayerScores[i].setString(std::to_string(m_TopTenScores[i].second));
		m_TopTenPlayerScores[i].setOutlineThickness(1);
		m_TopTenPlayerScores[i].setOrigin(m_TopTenPlayerScores[i].getLocalBounds().width / 2, m_TopTenPlayerScores[i].getLocalBounds().height / 2);
		m_TopTenPlayerScores[i].setPosition(static_cast<float>(m_context->m_window->getSize().x / 2) + 100.0f, static_cast<float>(m_context->m_window->getSize().y / 2) + static_cast<float>((i * 50)) - 225.0f);

	}

	
}

void Leaderboard::processInput()
{
	sf::Event event;
	while (m_context->m_window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_context->m_window->close();
			
		}
		else if (event.type == sf::Event::KeyPressed)
		{
			switch (event.key.code)
			{
			case sf::Keyboard::Up:
			{
				break;
			}
			case sf::Keyboard::Down:
			{
				break;
			}
			case sf::Keyboard::Escape:
			{
				m_isExitButtonPressed = true;
				break;
			}
			default:
				break;
			}
		}
	}
}

void Leaderboard::update(sf::Time deltaTime)
{
	if (m_isExitButtonPressed)
	{
		m_context->m_states->add(std::make_unique<MainMenu>(m_context, m_bgm->getOverallVolume(), m_bgm->getInGameVolume(), m_bgm->getSFXVolume()), true);
	}
}

void Leaderboard::draw()
{
	m_context->m_window->clear();
	m_context->m_window->draw(m_menuBackground);
	m_context->m_window->draw(m_gameTitle);
	m_context->m_window->draw(m_name);
	m_context->m_window->draw(m_scoreText);
	for (int i = 0; i < 10; i++)
	{
		m_context->m_window->draw(m_TopTenPlayerNames[i]);
		m_context->m_window->draw(m_TopTenPlayerScores[i]);

	}
	m_context->m_window->display();
}

void Leaderboard::start()
{
}

void Leaderboard::pause()
{
}

