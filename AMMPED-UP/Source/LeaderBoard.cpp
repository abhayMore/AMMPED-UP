#include "../Header Files/Leaderboard.h"
#include "SFML/Window/Event.hpp"
#include "../Header Files/MainMenu.h"
#include <iostream>>
Leaderboard::Leaderboard(std::shared_ptr<Context>& context) :
	m_context(context), 
	m_isExitButtonPressed(false)
{
	instance = MongoInstance::getInstance();

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

	m_TopTenScores = m.getTopScores(10);
}

Leaderboard::~Leaderboard()
{
}

void Leaderboard::init()
{
	m_context->m_assets->addFont(MAIN_FONT, "Resources/fonts/BOMBERMAN.TTF");

	//MENU BACKGROUND 
	m_context->m_assets->addTextures(MENU_BACKGROUND, "Resources/assets/bombmap.png");
	m_menuBackground.setTexture(m_context->m_assets->getTexture(MENU_BACKGROUND));
	m_menuBackground.setPosition(m_context->m_window->getSize().x / 2, m_context->m_window->getSize().y / 2);
	m_menuBackground.setOrigin(sf::Vector2f(m_menuBackground.getTexture()->getSize().x / 2, m_menuBackground.getTexture()->getSize().y / 2));
	m_menuBackground.setScale({ 2,2 });

	//GAME TITLE
	m_gameTitle.setFont(m_context->m_assets->getFont(MAIN_FONT));
	m_gameTitle.setString("LEADERBOARD");
	m_gameTitle.setCharacterSize(50);
	m_gameTitle.setOrigin(m_gameTitle.getLocalBounds().width / 2, m_gameTitle.getLocalBounds().height / 2);
	m_gameTitle.setPosition(m_context->m_window->getSize().x / 2, m_context->m_window->getSize().y / 2 - 340.0f) ;

	m_name.setFont(m_context->m_assets->getFont(MAIN_FONT));
	m_name.setString(username->getUsername());
	m_name.setCharacterSize(25);
	m_name.setOrigin(m_name.getLocalBounds().width / 2, m_name.getLocalBounds().height / 2);
	m_name.setPosition(m_context->m_window->getSize().x / 2 - 100, m_context->m_window->getSize().y / 2 - 275.0f);

	m_scoreText.setFont(m_context->m_assets->getFont(MAIN_FONT));
	m_scoreText.setCharacterSize(25);
	m_scoreText.setOrigin(m_scoreText.getLocalBounds().width / 2, m_scoreText.getLocalBounds().height / 2);
	m_scoreText.setPosition(m_context->m_window->getSize().x / 2 + 100, m_context->m_window->getSize().y / 2 - 275.0f);

	for (int i = 0; i < 10; i++)
	{
		m_TopTenPlayerNames[i].setFont(m_context->m_assets->getFont(LOGIN_FONT));
		m_TopTenPlayerNames[i].setCharacterSize(25);
		m_TopTenPlayerNames[i].setString(m_TopTenScores[i].first);
		m_TopTenPlayerNames[i].setOutlineThickness(1);
		m_TopTenPlayerNames[i].setOrigin(m_TopTenPlayerNames[i].getLocalBounds().width / 2, m_TopTenPlayerNames[i].getLocalBounds().height / 2);

		m_TopTenPlayerScores[i].setFont(m_context->m_assets->getFont(LOGIN_FONT));
		m_TopTenPlayerScores[i].setCharacterSize(25);
		m_TopTenPlayerScores[i].setString(std::to_string(m_TopTenScores[i].second));
		m_TopTenPlayerScores[i].setOutlineThickness(1);
		m_TopTenPlayerScores[i].setOrigin(m_TopTenPlayerScores[i].getLocalBounds().width / 2, m_TopTenPlayerScores[i].getLocalBounds().height / 2);
	}

	m_TopTenPlayerNames[0].setPosition(m_context->m_window->getSize().x / 2 - 100.0f , m_context->m_window->getSize().y / 2 - 225.0f);
	m_TopTenPlayerNames[1].setPosition(m_context->m_window->getSize().x / 2 - 100.0f , m_context->m_window->getSize().y / 2 - 175.0f);
	m_TopTenPlayerNames[2].setPosition(m_context->m_window->getSize().x / 2 - 100.0f , m_context->m_window->getSize().y / 2 - 125.0f);
	m_TopTenPlayerNames[3].setPosition(m_context->m_window->getSize().x / 2 - 100.0f , m_context->m_window->getSize().y / 2 - 75.0f);
	m_TopTenPlayerNames[4].setPosition(m_context->m_window->getSize().x / 2 - 100.0f , m_context->m_window->getSize().y / 2 - 25.0f);
	m_TopTenPlayerNames[5].setPosition(m_context->m_window->getSize().x / 2 - 100.0f , m_context->m_window->getSize().y / 2 + 25.0f);
	m_TopTenPlayerNames[6].setPosition(m_context->m_window->getSize().x / 2 - 100.0f , m_context->m_window->getSize().y / 2 + 75.0f);
	m_TopTenPlayerNames[7].setPosition(m_context->m_window->getSize().x / 2 - 100.0f , m_context->m_window->getSize().y / 2 + 125.0f);
	m_TopTenPlayerNames[8].setPosition(m_context->m_window->getSize().x / 2 - 100.0f , m_context->m_window->getSize().y / 2 + 175.0f);
	m_TopTenPlayerNames[9].setPosition(m_context->m_window->getSize().x / 2 - 100.0f , m_context->m_window->getSize().y / 2 + 225.0f);

	m_TopTenPlayerScores[0].setPosition(m_context->m_window->getSize().x / 2 + 100.0f , m_context->m_window->getSize().y / 2 - 225.0f);
	m_TopTenPlayerScores[1].setPosition(m_context->m_window->getSize().x / 2 + 100.0f , m_context->m_window->getSize().y / 2 - 175.0f);
	m_TopTenPlayerScores[2].setPosition(m_context->m_window->getSize().x / 2 + 100.0f , m_context->m_window->getSize().y / 2 - 125.0f);
	m_TopTenPlayerScores[3].setPosition(m_context->m_window->getSize().x / 2 + 100.0f , m_context->m_window->getSize().y / 2 - 75.0f);
	m_TopTenPlayerScores[4].setPosition(m_context->m_window->getSize().x / 2 + 100.0f , m_context->m_window->getSize().y / 2 - 25.0f);
	m_TopTenPlayerScores[5].setPosition(m_context->m_window->getSize().x / 2 + 100.0f , m_context->m_window->getSize().y / 2 + 25.0f);
	m_TopTenPlayerScores[6].setPosition(m_context->m_window->getSize().x / 2 + 100.0f , m_context->m_window->getSize().y / 2 + 75.0f);
	m_TopTenPlayerScores[7].setPosition(m_context->m_window->getSize().x / 2 + 100.0f , m_context->m_window->getSize().y / 2 + 125.0f);
	m_TopTenPlayerScores[8].setPosition(m_context->m_window->getSize().x / 2 + 100.0f , m_context->m_window->getSize().y / 2 + 175.0f);
	m_TopTenPlayerScores[9].setPosition(m_context->m_window->getSize().x / 2 + 100.0f , m_context->m_window->getSize().y / 2 + 225.0f);

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

