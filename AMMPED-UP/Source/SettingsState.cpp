#include "../Header Files/SettingsState.h"
#include "SFML/Window/Event.hpp"
#include "../Header Files/GamePlay.h"
#include "../Header Files/ExitState.h"
#include "../Header Files/MainMenu.h"

#include <memory>

enum buttonValues
{
	RESET_HIGHSCORE,
	BACK
};

SettingsState::SettingsState(std::shared_ptr<Context>& context) :
	m_context(context),
	m_isResetHighScoreButtonPressed(false),
	m_isMainmenuButtonPressed(false),
	gui(*m_context->m_window),
	m_isOverallMusicSliderMove(false),
	m_isInGameMusicSliderMove(false),
	m_isSFXSliderMove(false),
	m_errorPrompt(*m_context->m_window)
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

SettingsState::~SettingsState()
{
}

void SettingsState::init()
{

	//MENU BACKGROUND 
	m_context->m_assets->addTextures(MENU_BACKGROUND, "Resources/assets/bombmap.png");
	m_menuBackground.setTexture(m_context->m_assets->getTexture(MENU_BACKGROUND));
	m_menuBackground.setPosition(static_cast<float>(m_context->m_window->getSize().x / 2), static_cast<float>(m_context->m_window->getSize().y / 2));
	m_menuBackground.setOrigin(sf::Vector2f(static_cast<float>(m_menuBackground.getTexture()->getSize().x / 2), static_cast<float>(m_menuBackground.getTexture()->getSize().y / 2)));
	m_menuBackground.setScale({ 2,2 });

	//SETTINGS TITLE
	m_settingsTitle.setFont(m_context->m_assets->getFont(MAIN_FONT));
	m_settingsTitle.setString("Settings");
	m_settingsTitle.setCharacterSize(50);
	m_settingsTitle.setOrigin(m_settingsTitle.getLocalBounds().width / 2, m_settingsTitle.getLocalBounds().height / 2);
	m_settingsTitle.setPosition(static_cast<float>(m_context->m_window->getSize().x / 2), static_cast<float>(m_context->m_window->getSize().y / 2)  - 325.0f);
	m_settingsTitle.setOutlineThickness(1);

	for (int i = 0; i < 5; i++)
	{
		m_controlDirections[i].setFont(m_context->m_assets->getFont(MAIN_FONT));
		m_controlDirections[i].setCharacterSize(25);
		m_controlDirections[i].setOutlineThickness(1);
	}
	m_controlDirections[0].setString("W / UP - Move UP");
	m_controlDirections[1].setString("A / LEFT - Move RIGHT");
	m_controlDirections[2].setString("S / DOWN - Move DOWN");
	m_controlDirections[3].setString("D / RIGHT - Move RIGHT");
	m_controlDirections[4].setString("SPACE - Plant BOMB");
	for (int i = 0; i < 5; i++)
	{
		m_controlDirections[i].setOrigin(m_controlDirections[i].getLocalBounds().width / 2, m_controlDirections[i].getLocalBounds().height / 2);
	}
	m_controlDirections[0].setPosition(static_cast<float>(m_context->m_window->getSize().x / 2), static_cast<float>(m_context->m_window->getSize().y / 2) - 100.0f);
	m_controlDirections[1].setPosition(static_cast<float>(m_context->m_window->getSize().x / 2), static_cast<float>(m_context->m_window->getSize().y / 2) - 50.0f);
	m_controlDirections[2].setPosition(static_cast<float>(m_context->m_window->getSize().x / 2), static_cast<float>(m_context->m_window->getSize().y / 2) - .0f);
	m_controlDirections[3].setPosition(static_cast<float>(m_context->m_window->getSize().x / 2), static_cast<float>(m_context->m_window->getSize().y / 2) + 50.0f);
	m_controlDirections[4].setPosition(static_cast<float>(m_context->m_window->getSize().x / 2), static_cast<float>(m_context->m_window->getSize().y / 2) + 100.0f);

	///////////////////////////////////////////////////
	//RESET HIGHSCORE AND MAINMENU BUTTON INIT
	m_context->m_assets->addGuiFont(MAIN_FONT, "Resources/fonts/BungeeSpice-Regular.TTF");

	for (int i = 0; i < 2; i++)
	{
		m_pageButtons[i] = tgui::Button::create();
		m_pageButtons[i]->getRenderer()->setBackgroundColor(tgui::Color::Transparent);
		m_pageButtons[i]->getRenderer()->setBorderColor(tgui::Color::Transparent);
		m_pageButtons[i]->getRenderer()->setTextColor(tgui::Color::White);
		m_pageButtons[i]->getRenderer()->setFont(tgui::Font(m_context->m_assets->getGuiFont(MAIN_FONT).getId()));
		m_pageButtons[i]->setTextSize(35);
		if (i == RESET_HIGHSCORE)
		{
			m_pageButtons[i]->setText("Reset Highscore?");
			m_pageButtons[i]->setPosition(m_context->m_window->getSize().x / 2 - m_pageButtons[i]->getSize().x / 2, m_context->m_window->getSize().y / 2 + 200.0f);
			m_pageButtons[i]->getRenderer()->setTextColorFocused(tgui::Color::Magenta);
			m_pageButtons[i]->getRenderer()->setBorderColorFocused(tgui::Color::Transparent);
		}
		else if (i == BACK)
		{
			m_pageButtons[i]->setText("Back");
			m_pageButtons[i]->setPosition(m_context->m_window->getSize().x / 2 - m_pageButtons[i]->getSize().x / 2, m_context->m_window->getSize().y / 2 + 300.0f);
			m_pageButtons[i]->setFocused(true);
			m_pageButtons[i]->getRenderer()->setTextColorFocused(tgui::Color::Magenta);
			m_pageButtons[i]->getRenderer()->setBorderColorFocused(tgui::Color::Transparent);
		}
		m_pageButtons[i]->getRenderer()->setTextOutlineThickness(1);
		gui.add(m_pageButtons[i]);
	}

	//AUDIO CONTROLS INIT
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

	m_context->m_assets->addGuiFont(LOGIN_FONT, "Resources/fonts/Arial.ttf");

	//PROMPTS for exceptions at top left corner
	m_errorPrompt.init(
		"",
		m_context->m_assets->getGuiFont(LOGIN_FONT),
		20,
		{2,2},
		{ m_errorPrompt.getSize().x / 2, m_errorPrompt.getSize().y / 2 },
		sf::Color(255, 49, 49),
		0.5,
		sf::Color::Black
	);
	
}

void SettingsState::processInput()
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
			case sf::Event::MouseButtonPressed:
			{
				switch (event.mouseButton.button)
				{
				case sf::Mouse::Left:
				{
					if (m_audioControls[0]->isMouseOnWidget(sf::Vector2f(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y))))
					{
						m_isOverallMusicSliderMove = true;
					}
					if (m_audioControls[1]->isMouseOnWidget(sf::Vector2f(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y))))
					{
						m_isInGameMusicSliderMove = true;
					}
					if (m_audioControls[2]->isMouseOnWidget(sf::Vector2f(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y))))
					{
						m_isSFXSliderMove = true;
					}
					float mouseX = static_cast<float>(sf::Mouse::getPosition(*m_context->m_window).x);
					float mouseY = static_cast<float>(sf::Mouse::getPosition(*m_context->m_window).y);
					if (m_pageButtons[0]->isMouseOnWidget({ mouseX, mouseY })
						&& m_pageButtons[0]->isFocused())
					{
						
						m_isResetHighScoreButtonPressed = true;
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
				case sf::Keyboard::Return:
				{
					if (m_pageButtons[0]->isFocused())
					{
						m_isResetHighScoreButtonPressed = true;
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
		}
	}
}

void SettingsState::update(sf::Time deltaTime)
{
	
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
	

	m_bgm->setOverallVolume(m_audioControls[0]->getValue());
	m_bgm->setInGameVolume(m_audioControls[1]->getValue());
	m_bgm->setSFXVolume(m_audioControls[2]->getValue());


	if (m_isResetHighScoreButtonPressed)
	{
		m_elapsedTime += deltaTime;
		m.updateDocument(username->getUsername(), "score", 0);
		m_errorPrompt.setText("Highscore reset successful");

	}
	if (m_isMainmenuButtonPressed)
	{
		m_context->m_states->add(std::make_unique<MainMenu>(m_context, m_bgm->getOverallVolume(), m_bgm->getInGameVolume(), m_bgm->getSFXVolume()), true);
		m_isMainmenuButtonPressed = false;
	}
	if (m_elapsedTime.asSeconds() > 3.0)
	{
		m_errorPrompt.setText("");
		m_elapsedTime = sf::Time::Zero;
		m_isResetHighScoreButtonPressed = false;

	}
}

void SettingsState::draw()
{
	m_context->m_window->clear();
	m_context->m_window->draw(m_menuBackground);
	m_context->m_window->draw(m_settingsTitle);
	m_context->m_window->draw(m_overallMusic);
	m_context->m_window->draw(m_inGameMusic);
	m_context->m_window->draw(m_sfx);
	m_errorPrompt.draw();
	for (int i = 0; i < 5; i++)
	{
		m_context->m_window->draw(m_controlDirections[i]);

	}
	gui.draw();
	m_context->m_window->display();
}

void SettingsState::start()
{
}

void SettingsState::pause()
{
}