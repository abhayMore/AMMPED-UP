#include "../Header Files/Leaderboard.h"
#include "SFML/Window/Event.hpp"
#include "../Header Files/MainMenu.h"
#include <iostream>>
Leaderboard::Leaderboard(std::shared_ptr<Context>& context) :
	m_context(context), 
	m_isExitButtonPressed(false)
{
	username = UserNameManager::getInstance();

	inputFile = std::ifstream("score.json");
	isInputFileEmpty = (inputFile.peek() == std::ifstream::traits_type::eof());
	if (!isInputFileEmpty)
	{
		jsonFile = nlohmann::json::parse(inputFile);
		inputFile.close();

		for (auto& person : jsonFile)
		{
			if (person["username"].get<std::string>() == username->getUsername())
			{
				foundPlayerData = true;
				int score = person["score"].get<int>();
				m_scoreText.setString(std::to_string(score));
				break;
			}
		}
		writeToFile();
	}
	if(isInputFileEmpty || !foundPlayerData)
	{
		nlohmann::json playerInfo;
		playerInfo = {
			{"username",    username->getUsername()},
			{"score",       0}
		};
		jsonFile.push_back(playerInfo);
		m_scoreText.setString(std::to_string(0));
		writeToFile();
	}	

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
	m_gameTitle.setPosition(m_context->m_window->getSize().x / 2, m_context->m_window->getSize().y / 2 - 150.0f) ;

	m_name.setFont(m_context->m_assets->getFont(MAIN_FONT));
	m_name.setString(username->getUsername());
	m_name.setCharacterSize(25);
	m_name.setOrigin(m_name.getLocalBounds().width / 2, m_name.getLocalBounds().height / 2);
	m_name.setPosition(m_context->m_window->getSize().x / 2 - 150, m_context->m_window->getSize().y / 2 - 75.0f);

	m_scoreText.setFont(m_context->m_assets->getFont(MAIN_FONT));
	m_scoreText.setCharacterSize(25);
	m_scoreText.setOrigin(m_name.getLocalBounds().width / 2, m_name.getLocalBounds().height / 2);
	m_scoreText.setPosition(m_context->m_window->getSize().x / 2 + 150, m_context->m_window->getSize().y / 2 - 75.0f);
}

void Leaderboard::processInput()
{
	sf::Event event;
	while (m_context->m_window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_context->m_window->close();
			if (!isInputFileEmpty)
				writeToFile();
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

	m_context->m_window->display();
}

void Leaderboard::start()
{
}

void Leaderboard::pause()
{
}

void Leaderboard::writeToFile()
{
	outputFile = std::ofstream("score.json");
	outputFile << std::setw(4) << jsonFile << std::endl;
	outputFile.close();
}
