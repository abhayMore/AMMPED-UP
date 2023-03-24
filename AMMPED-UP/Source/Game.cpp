#include "../Header Files/Game.h"
#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Window/Event.hpp"
#include "../Header Files/SplashScreen.h"
#include "../Header Files/MainMenu.h"

Game::Game() : m_context(std::make_shared<Context>())
{
    //CREATE THE WINDOW
	m_context->m_window->create(sf::VideoMode(640, 480), "AMMPED-UP", sf::Style::Close);
    //m_context->m_window->setFramerateLimit(60);
    //m_context->m_window->setKeyRepeatEnabled(true);

    //LOAD GAME RELATED SOUNDEFFECTS
    m_context->m_assets->addSoundEffects(FOOD_SFX, "Resources/assets/music/assets_audio_Simple Coin 006.wav");
    m_context->m_assets->addSoundEffects(DEATH_SFX, "Resources/assets/music/assets_audio_Death 002.wav");
    m_context->m_assets->addSoundTrack(MAIN_SOUND_TRACK, "Resources/assets/music/forest.wav", true);
    m_context->m_assets->addSoundTrack(IN_GAME_SOUND_TRACK, "Resources/assets/music/assets_audio_Spinning out.ogg", true);

	//Add First State(SPLASHSCREEN STATE) to m_states here
    m_context->m_states->add(std::make_unique<MainMenu>(m_context));
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
        timeSinceLastFrame += clock.restart();   
        //timeSinceLastFrame = clock.restart();

        while (timeSinceLastFrame > TIME_PER_FRAME)
        {
            timeSinceLastFrame -= TIME_PER_FRAME;

            m_context->m_states->processStateChange();
            m_context->m_states->getCurrent()->processInput();
            //m_context->m_states->getCurrent()->update(timeSinceLastFrame);
            m_context->m_states->getCurrent()->update(TIME_PER_FRAME);
            m_context->m_states->getCurrent()->draw();

        }
    }
}
