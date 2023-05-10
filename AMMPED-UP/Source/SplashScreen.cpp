#include "../Header Files/SplashScreen.h"
#include "../Header Files/LoginState.h"
#include "../Header Files/MainMenu.h"
#include <SFML/System/Sleep.hpp>
#include "SFML/Window/Event.hpp"

SplashScreen::SplashScreen(std::shared_ptr<Context>& context, std::vector<int> assetID):
	m_context(context), m_assetID(assetID), m_currentSplashScreen(0), m_bgColor(sf::Color::White)
{
}

SplashScreen::~SplashScreen()
{
}

void SplashScreen::init()
{
	m_background.setTexture(m_context->m_assets->getTexture(m_assetID[m_currentSplashScreen]));
	m_background.setPosition(m_context->m_window->getSize().x / 2, m_context->m_window->getSize().y / 2);
	m_background.setOrigin(sf::Vector2f(m_background.getTexture()->getSize().x / 2,m_background.getTexture()->getSize().y / 2 ));

	for (auto id : m_assetID)
	{
		if (id == COLLEGE_SPLASH_SCREEN)
		{
			m_bgColor = sf::Color::White;
		}
		if (id == MY_SPLASH_SCREEN)
		{
			m_bgColor = sf::Color::Black;
		}

	}
}	

void SplashScreen::processInput()
{
	sf::Event event;
	while (m_context->m_window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			m_context->m_window->close();
	}
}

void SplashScreen::update(sf::Time deltaTime)
{
	m_elapsedTime += deltaTime;
	if (m_elapsedTime.asSeconds() > 3.0)
	{
		m_currentSplashScreen++;
		if (m_currentSplashScreen < m_assetID.size())
		{
			m_background.setTexture(m_context->m_assets->getTexture(m_assetID[m_currentSplashScreen]));
			m_elapsedTime = sf::Time::Zero;
			m_bgColor = sf::Color::Black;
		}
		else
		{
			m_context->m_states->add(std::make_unique<MainMenu>(m_context, " ", 0));
		}
	}
}

void SplashScreen::draw()
{
	m_context->m_window->clear(m_bgColor);
	m_context->m_window->draw(m_background);
	m_context->m_window->display();
}