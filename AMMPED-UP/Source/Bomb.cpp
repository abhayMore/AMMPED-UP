#include "../Header Files/Bomb.h"
#include <iostream>
Bomb::Bomb() :m_bombTickAnimation(m_bomb), m_bombRadius(1), m_blasted(false)
{
}

void Bomb::init(const sf::Texture& texture)
{
	m_bomb.setTexture(texture);
	m_bomb.setTextureRect(sf::IntRect(0,0,16,16));

	m_bombTickAnimation.addFrame({ sf::IntRect(0,0,16,16), sf::Time(sf::seconds(0.5))});
	m_bombTickAnimation.addFrame({ sf::IntRect(16,0,16,16), sf::Time(sf::seconds(0.5)) });
	m_bombTickAnimation.addFrame({ sf::IntRect(32,0,16,16), sf::Time(sf::seconds(0.5)) });
	m_bombTickAnimation.addFrame({ sf::IntRect(48,0,16,16), sf::Time(sf::seconds(0.5)) });
	m_bombTickAnimation.addFrame({ sf::IntRect(64,0,16,16), sf::Time(sf::seconds(0.5)) });
	m_bombTickAnimation.addFrame({ sf::IntRect(80,0,16,16), sf::Time(sf::seconds(0.5)) });
}

void Bomb::update(const sf::Vector2f pos, sf::Time deltatime)
{
	m_bombPosition = pos;
	m_bomb.setPosition(m_bombPosition);
	m_bombTickAnimation.update(deltatime);
	m_bombTriggerTime += deltatime;

	if (m_bombTriggerTime.asSeconds() > 3.0f)
	{
		m_blasted = true;
		m_bombTriggerTime = sf::Time::Zero;

	}
}

bool Bomb::isBlasted()
{
	return m_blasted;
}

void Bomb::setIsBlasted(bool isBlasted)
{
	m_blasted = isBlasted;

}

void Bomb::setPosition(sf::Vector2f pos)
{
	m_bombPosition = pos;
	m_bomb.setPosition(m_bombPosition);

}

sf::Vector2f Bomb::getPosition()
{
	return m_bombPosition;
}

void Bomb::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_bomb);
}
