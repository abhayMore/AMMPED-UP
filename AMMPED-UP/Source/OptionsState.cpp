#include "../Header Files/OptionsState.h"
#include "SFML/Window/Event.hpp"
#include "../Header Files/GamePlay.h"
#include "../Header Files/ExitState.h"
#include "../Header Files/MainMenu.h"

#include <memory>

OptionsState::OptionsState(std::shared_ptr<Context>& context) :
	m_context(context),
	m_isResetHighScoreButtonSelected(false),
	m_isResetHighScoreButtonPressed(false),
	m_isExitButtonSelected(true),
	m_isExitButtonPressed(false),
	gui(*m_context->m_window),
	m_isOverallMusicSliderMove(false),
	m_isInGameMusicSliderMove(false),
	m_isSFXSliderMove(false), 
	instance(MongoInstance::getInstance())
{
	theme.load("Resources/Black.txt");
	username = UserNameManager::getInstance();

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

OptionsState::~OptionsState()
{
}

void OptionsState::init()
{
	m_context->m_assets->addFont(MAIN_FONT, "Resources/fonts/BOMBERMAN.TTF");

	//MENU BACKGROUND 
	m_context->m_assets->addTextures(MENU_BACKGROUND, "Resources/assets/bombmap.png");
	m_menuBackground.setTexture(m_context->m_assets->getTexture(MENU_BACKGROUND));
	m_menuBackground.setPosition(m_context->m_window->getSize().x / 2, m_context->m_window->getSize().y / 2);
	m_menuBackground.setOrigin(sf::Vector2f(m_menuBackground.getTexture()->getSize().x / 2, m_menuBackground.getTexture()->getSize().y / 2));
	m_menuBackground.setScale({ 2,2 });

	//OPTIONS TITLE
	m_optionsTitle.setFont(m_context->m_assets->getFont(MAIN_FONT));
	m_optionsTitle.setString("Options");
	m_optionsTitle.setCharacterSize(50);
	m_optionsTitle.setOrigin(m_optionsTitle.getLocalBounds().width / 2, m_optionsTitle.getLocalBounds().height / 2);
	m_optionsTitle.setPosition(m_context->m_window->getSize().x / 2, m_context->m_window->getSize().y / 2 - 325.0f) ;
	m_optionsTitle.setOutlineThickness(1);

	for (int i = 0; i < 5; i++)
	{
		m_controlDirections[i].setFont(m_context->m_assets->getFont(MAIN_FONT));
		m_controlDirections[i].setCharacterSize(25);
		m_controlDirections[i].setOutlineThickness(1);
	}
	m_controlDirections[0].setString("W - Move UP");
	m_controlDirections[1].setString("A - Move RIGHT");
	m_controlDirections[2].setString("S - Move DOWN");
	m_controlDirections[3].setString("D - Move RIGHT");
	m_controlDirections[4].setString("SPACE - Plant BOMB");
	for (int i = 0; i < 5; i++)
	{
		m_controlDirections[i].setOrigin(m_controlDirections[i].getLocalBounds().width / 2, m_controlDirections[i].getLocalBounds().height / 2);
	}
	m_controlDirections[0].setPosition(m_context->m_window->getSize().x / 2, m_context->m_window->getSize().y / 2 - 100.0f);
	m_controlDirections[1].setPosition(m_context->m_window->getSize().x / 2, m_context->m_window->getSize().y / 2 - 50.0f);
	m_controlDirections[2].setPosition(m_context->m_window->getSize().x / 2, m_context->m_window->getSize().y / 2 - .0f);
	m_controlDirections[3].setPosition(m_context->m_window->getSize().x / 2, m_context->m_window->getSize().y / 2 + 50.0f);
	m_controlDirections[4].setPosition(m_context->m_window->getSize().x / 2, m_context->m_window->getSize().y / 2 + 100.0f);

	//RESET HIGHSCORE BUTTON
	m_resetHighScoreButton.setFont(m_context->m_assets->getFont(MAIN_FONT));
	m_resetHighScoreButton.setString("Reset Highscore?");
	m_resetHighScoreButton.setCharacterSize(35);
	m_resetHighScoreButton.setOrigin(m_resetHighScoreButton.getLocalBounds().width / 2, m_resetHighScoreButton.getLocalBounds().height / 2);
	m_resetHighScoreButton.setPosition(m_context->m_window->getSize().x / 2, m_context->m_window->getSize().y / 2 + 200.0f);
	m_resetHighScoreButton.setOutlineThickness(1);

	//EXIT BUTTON
	m_exitButton.setFont(m_context->m_assets->getFont(MAIN_FONT));
	m_exitButton.setString("Back");
	m_exitButton.setCharacterSize(35);
	m_exitButton.setOrigin(m_exitButton.getLocalBounds().width / 2, m_exitButton.getLocalBounds().height / 2);
	m_exitButton.setPosition(m_context->m_window->getSize().x / 2, m_context->m_window->getSize().y / 2 + 300.0f);
	m_exitButton.setOutlineThickness(1);

	for (int i = 0; i < 3; i++) {
		m_audioControls[i] = tgui::Slider::create();
		m_audioControls[i]->setRenderer(theme.getRenderer("Slider"));
		m_audioControls[i]->setSize(200, 20);
		m_audioControls[i]->setMinimum(0);
		m_audioControls[i]->setMaximum(100);
		m_audioControls[i]->setValue(50);
		gui.add(m_audioControls[i]);
	}
	m_audioControls[0]->setPosition(m_context->m_window->getSize().x / 2 - 100, m_context->m_window->getSize().y / 2 - 250.0f);
	m_audioControls[1]->setPosition(m_context->m_window->getSize().x / 2 - 210, m_context->m_window->getSize().y / 2 - 190.0f);
	m_audioControls[2]->setPosition(m_context->m_window->getSize().x / 2 + 10, m_context->m_window->getSize().y / 2 - 190.0f);

	auto audioTextHeightBuffer = 5;
	m_overallMusic.setFont(m_context->m_assets->getFont(MAIN_FONT));
	m_overallMusic.setString("Overall Music");
	m_overallMusic.setCharacterSize(20);
	m_overallMusic.setOrigin(m_overallMusic.getLocalBounds().width / 2, m_overallMusic.getLocalBounds().height / 2);
	m_overallMusic.setPosition(m_context->m_window->getSize().x / 2 + m_overallMusic.getLocalBounds().width / 2 - 100, m_context->m_window->getSize().y / 2 - 250.0f - m_overallMusic.getLocalBounds().height - audioTextHeightBuffer);
	m_overallMusic.setOutlineThickness(1);

	m_inGameMusic.setFont(m_context->m_assets->getFont(MAIN_FONT));
	m_inGameMusic.setString("in-Game Music");
	m_inGameMusic.setCharacterSize(20);
	m_inGameMusic.setOrigin(m_inGameMusic.getLocalBounds().width / 2, m_inGameMusic.getLocalBounds().height / 2);
	m_inGameMusic.setPosition(m_context->m_window->getSize().x / 2 + m_inGameMusic.getLocalBounds().width / 2 - 210, m_context->m_window->getSize().y / 2 - 190.0f - m_inGameMusic.getLocalBounds().height - audioTextHeightBuffer);
	m_inGameMusic.setOutlineThickness(1);

	m_sfx.setFont(m_context->m_assets->getFont(MAIN_FONT));
	m_sfx.setString("SFX");
	m_sfx.setCharacterSize(20);
	m_sfx.setOrigin(m_sfx.getLocalBounds().width / 2, m_sfx.getLocalBounds().height / 2);
	m_sfx.setPosition(m_context->m_window->getSize().x / 2 + m_sfx.getLocalBounds().width / 2 + 10, m_context->m_window->getSize().y / 2 - 190.0f - m_sfx.getLocalBounds().height - audioTextHeightBuffer);
	m_sfx.setOutlineThickness(1);

	m_audioControls[0]->setValue(m_bgm->getOverallVolume());
	m_audioControls[1]->setValue(m_bgm->getInGameVolume());
	m_audioControls[2]->setValue(m_bgm->getSFXVolume());
	//m_bgm->setVolume(m_audioControls[0]->getValue());

	//PROMPTS for exceptions at top left corner
	m_errorPrompt.setFont(m_context->m_assets->getFont(LOGIN_FONT));
	m_errorPrompt.setFillColor(sf::Color(255, 49, 49));
	m_errorPrompt.setOutlineThickness(0.5);
	m_errorPrompt.setOutlineColor(sf::Color::Black);
	m_errorPrompt.setString("");
	m_errorPrompt.setCharacterSize(20);
	m_errorPrompt.setOrigin(m_errorPrompt.getLocalBounds().width / 2, m_errorPrompt.getLocalBounds().height / 2);
	m_errorPrompt.setPosition(m_errorPrompt.getLocalBounds().width / 2 + 2, m_errorPrompt.getLocalBounds().height / 2 + 2);

}

void OptionsState::processInput()
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
				switch (event.mouseButton.button)
				{
				case sf::Mouse::Left:
				{
					if (m_audioControls[0]->isMouseOnWidget(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
					{
						m_isOverallMusicSliderMove = true;
					}
					if (m_audioControls[1]->isMouseOnWidget(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
					{
						m_isInGameMusicSliderMove = true;
					}
					if (m_audioControls[2]->isMouseOnWidget(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
					{
						m_isSFXSliderMove = true;
					}
					break;
				}
				default:
					break;
				}
				break;
			}
			case sf::Event::MouseButtonReleased:
			{
				switch (event.mouseButton.button)
				{
					case sf::Mouse::Left:
					{
						m_isOverallMusicSliderMove = false;
						m_isInGameMusicSliderMove = false;
						m_isSFXSliderMove = false;
						break;
					}
				}
				break;
			}
			case sf::Event::KeyPressed:
			{
				switch (event.key.code)
				{
					case sf::Keyboard::Up:
					{
						if (!m_isResetHighScoreButtonSelected)
						{
							m_isResetHighScoreButtonSelected = true;
							m_isExitButtonSelected = false;
						}
					break;
					}
					case sf::Keyboard::Down:
					{
						if (!m_isExitButtonSelected)
						{
							m_isExitButtonSelected = true;
							m_isResetHighScoreButtonSelected = false;
						}
					
					break;
					}
					case sf::Keyboard::Escape:
					{
					m_isExitButtonPressed = true;
					break;
					}
					case sf::Keyboard::Return:
					{
						m_isResetHighScoreButtonPressed = false;
						m_isExitButtonPressed = false;
						if (m_isExitButtonSelected)
							m_isExitButtonPressed = true;
						else if (m_isResetHighScoreButtonSelected)
							m_isResetHighScoreButtonPressed = true;
					break;
					}
					default:
					break;
				}
			}
		}
	}
}

void OptionsState::update(sf::Time deltaTime)
{
	m_elapsedTime += deltaTime;
	if (m_isOverallMusicSliderMove)
	{
		m_audioControls[0]->setValue(sf::Mouse::getPosition(*m_context->m_window).x / 2 - m_audioControls[0]->getPosition().x / 2);
	}
	if (m_isInGameMusicSliderMove)
	{
		m_audioControls[1]->setValue(sf::Mouse::getPosition(*m_context->m_window).x / 2 - m_audioControls[1]->getPosition().x / 2);
	}
	if (m_isSFXSliderMove)
	{
		m_audioControls[2]->setValue(sf::Mouse::getPosition(*m_context->m_window).x / 2 - m_audioControls[2]->getPosition().x / 2);
	}
	if (m_isExitButtonSelected)
	{
		m_exitButton.setFillColor(::sf::Color::Magenta);
	}
	else
	{
		m_exitButton.setFillColor(::sf::Color::White);
	}

	m_bgm->setOverallVolume(m_audioControls[0]->getValue());
	m_bgm->setInGameVolume(m_audioControls[1]->getValue());
	m_bgm->setSFXVolume(m_audioControls[2]->getValue());


	if (m_isResetHighScoreButtonSelected)
	{
		m_resetHighScoreButton.setFillColor(sf::Color::Magenta);
		m_exitButton.setFillColor(::sf::Color::White);
	}
	else if (m_isExitButtonSelected)
	{
		m_resetHighScoreButton.setFillColor(sf::Color::White);
		m_exitButton.setFillColor(::sf::Color::Magenta);
	}
	if (m_isResetHighScoreButtonPressed)
	{
		m.updateDocument("score", m.findScore(username->getUsername()), "score", 0);
		m_errorPrompt.setString("Highscore reset successful");

		m_isResetHighScoreButtonPressed = false;
	}
	if (m_isExitButtonPressed)
	{
		m_context->m_states->add(std::make_unique<MainMenu>(m_context, m_bgm->getOverallVolume(), m_bgm->getInGameVolume(), m_bgm->getSFXVolume()), true);
		m_isExitButtonPressed = false;
	}
	if (m_elapsedTime.asSeconds() > 3.0)
	{
		m_errorPrompt.setString("");
		m_elapsedTime = sf::Time::Zero;
	}
}

void OptionsState::draw()
{
	m_context->m_window->clear();
	m_context->m_window->draw(m_menuBackground);
	m_context->m_window->draw(m_optionsTitle);
	m_context->m_window->draw(m_resetHighScoreButton);
	m_context->m_window->draw(m_exitButton);
	m_context->m_window->draw(m_overallMusic);
	m_context->m_window->draw(m_inGameMusic);
	m_context->m_window->draw(m_sfx);
	m_context->m_window->draw(m_errorPrompt);
	for (int i = 0; i < 5; i++)
	{
		m_context->m_window->draw(m_controlDirections[i]);

	}
	gui.draw();
	m_context->m_window->display();
}

void OptionsState::start()
{
}

void OptionsState::pause()
{
}