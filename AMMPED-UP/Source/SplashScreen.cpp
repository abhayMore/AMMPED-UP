#include "../Header Files/SplashScreen.h"
#include "../Header Files/LoginState.h"
#include "SFML/Window/Event.hpp"

SplashScreen::SplashScreen(std::shared_ptr<Context>& context):
	m_context(context)

{
}

SplashScreen::~SplashScreen()
{
}

void SplashScreen::init()
{
	m_context->m_assets->addTextures(SPLASH_SCREEN, "Resources/assets/F.jpg");
	m_background.setTexture(m_context->m_assets->getTexture(SPLASH_SCREEN));
	m_background.setPosition(m_context->m_window->getSize().x / 2, m_context->m_window->getSize().y / 2);
	m_background.setOrigin(sf::Vector2f(m_background.getTexture()->getSize().x / 2,m_background.getTexture()->getSize().y / 2 ));
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
		m_context->m_states->add(std::make_unique<LoginState>(m_context));
	}
}

void SplashScreen::draw()
{
	m_context->m_window->clear(sf::Color::White);
	m_context->m_window->draw(m_background);
	m_context->m_window->display();
}
