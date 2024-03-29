#include "../Header Files/Game.h"
#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Window/Event.hpp"
#include "SFML/System/Time.hpp"
#include "../Header Files/SplashScreen.h"
#include "../Header Files/MainMenu.h"
#include <iostream>
#include "SFML/System/Sleep.hpp"

Game::Game() : m_context(std::make_shared<Context>())
{
    //CREATE THE WINDOW
	m_context->m_window->create(sf::VideoMode(1280, 960), "AMMPED-UP", sf::Style::Close);
    //m_context->m_window->setFramerateLimit(60);
    //m_context->m_window->setKeyRepeatEnabled(true);
    m_context->m_window->setVerticalSyncEnabled(true);

    //LOAD ICON
    if (!m_icon.loadFromFile("Resources/assets/AppLogo.png"))
    {
        std::cout << "Game Logo Icon failed to load" << std::endl;
    }
    m_context->m_window->setIcon(m_icon.getSize().x, m_icon.getSize().y, m_icon.getPixelsPtr());
    //LOAD GAME RELATED SOUNDEFFECTS
    m_context->m_assets->addSoundEffects(COIN_SFX, "Resources/assets/music/assets_audio_Simple Coin 006.wav");
    m_context->m_assets->addSoundEffects(DEATH_SFX, "Resources/assets/music/assets_audio_Death 002.wav");
    m_context->m_assets->addSoundEffects(DAMAGE_SFX, "Resources/assets/music/ouch.wav");
    m_context->m_assets->addSoundEffects(BLAST_SFX, "Resources/assets/music/blast.wav");
    m_context->m_assets->addSoundEffects(ENEMY_DEATH_SFX, "Resources/assets/music/monster-4.wav");
    m_context->m_assets->addSoundTrack(MAIN_SOUND_TRACK, "Resources/assets/music/forest.wav", true);
    m_context->m_assets->addSoundTrack(IN_GAME_SOUND_TRACK, "Resources/assets/music/assets_audio_Spinning out.ogg", true);

    //ADDING TWO SPLASH_SCREEN TEXTURES
    m_context->m_assets->addTextures(COLLEGE_SPLASH_SCREEN, "Resources/assets/newLogo.png");
    m_context->m_assets->addTextures(MY_SPLASH_SCREEN, "Resources/assets/SplashScreenLogo.png");
	//Add First State(SPLASHSCREEN STATE) to m_states here
    m_context->m_states->add(std::make_unique<SplashScreen>(m_context, std::vector<std::pair<int, float> >{std::make_pair(COLLEGE_SPLASH_SCREEN, 3.0f), std::make_pair(MY_SPLASH_SCREEN, 3.0f)}));
    //m_context->m_states->add(std::make_unique<MainMenu>(m_context));
}

Game::~Game() 
{
}

void Game::run()
{
    sf::Clock clock;
    sf::Time timeSinceLastFrame = sf::Time::Zero;

    while (m_context->m_window->isOpen())
    {
        timeSinceLastFrame = clock.restart();
        m_context->m_states->processStateChange();
        m_context->m_states->getCurrent()->processInput();
        m_context->m_states->getCurrent()->update(timeSinceLastFrame);
        m_context->m_states->getCurrent()->draw();
    }
}