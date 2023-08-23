#include "../Header Files/SplashScreen.h"
#include "../Header Files/LoginState.h"
#include "../Header Files/MainMenu.h"
#include <SFML/System/Sleep.hpp>
#include "SFML/Window/Event.hpp"
#include <iostream>

SplashScreen::SplashScreen(std::shared_ptr<Context>& context, std::vector< std::pair<int, float> > assetID):
	m_context(context), m_assetID(assetID), m_currentSplashScreen(0), m_bgColor(sf::Color::White)
{
}

SplashScreen::~SplashScreen()
{
}

void SplashScreen::init()
{
	m_background.setTexture(m_context->m_assets->getTexture(m_assetID[m_currentSplashScreen].first));
	m_background.setPosition(m_context->m_window->getSize().x / 2, m_context->m_window->getSize().y / 2);
	m_background.setOrigin(sf::Vector2f(m_background.getTexture()->getSize().x / 2,m_background.getTexture()->getSize().y / 2 ));

	for (auto id : m_assetID)
	{
		if (id.first == COLLEGE_SPLASH_SCREEN)
		{
			m_bgColor = sf::Color::White;
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
	
		if (m_elapsedTime.asSeconds() > m_assetID[m_currentSplashScreen].second)
		{
			m_currentSplashScreen++;
			if (m_currentSplashScreen < m_assetID.size())
			{
				m_background.setTexture(m_context->m_assets->getTexture(m_assetID[m_currentSplashScreen].first));
				m_background.setPosition(m_context->m_window->getSize().x / 2, m_context->m_window->getSize().y / 2);
				m_background.setOrigin(sf::Vector2f(m_background.getTexture()->getSize().x / 2, m_background.getTexture()->getSize().y / 2));
				m_bgColor = sf::Color::Black;

				m_elapsedTime = sf::Time::Zero;
			}
			else
			{
				m_context->m_states->add(std::make_unique<LoginState>(m_context), true);
			}
		}
}

void SplashScreen::draw()
{

	m_context->m_window->clear(m_bgColor);
	m_context->m_window->draw(m_background);

	m_context->m_window->display();
	//sf::sleep(sf::seconds(5));

}