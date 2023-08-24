#include "../Header Files/Coin.h"
Coin::Coin() :m_coinAnimation(m_coin)
{
}

void Coin::init(const sf::Texture& texture)
{
	m_coin.setTexture(texture);
	m_coin.setTextureRect(sf::IntRect(0, 0, 16, 16));
	//m_coin.setScale({ 2,2 });
	m_coinAnimation.addFrame({ sf::IntRect(0,0,16,16), sf::Time(sf::seconds(0.1f)) });
	m_coinAnimation.addFrame({ sf::IntRect(16,0,16,16), sf::Time(sf::seconds(0.1f)) });
	m_coinAnimation.addFrame({ sf::IntRect(32,0,16,16), sf::Time(sf::seconds(0.1f)) });
	m_coinAnimation.addFrame({ sf::IntRect(48,0,16,16), sf::Time(sf::seconds(0.1f)) });
}
bool Coin::playerIsOnCoin(sf::Sprite& other)
{
	if (getPosition().x + 14 > other.getPosition().x + 3 &&
		getPosition().x + 1 <= other.getPosition().x + 14 &&
		getPosition().y + 14 > other.getPosition().y + 3 &&
		getPosition().y + 1 <= other.getPosition().y + 14)
	{
		return true;
	}
	return false;
}

void Coin::update(sf::Time deltatime)
{
	m_coinAnimation.update(deltatime);
}

void Coin::setPosition(sf::Vector2f pos)
{
	m_coinPosition = pos;
	m_coin.setPosition(m_coinPosition + sf::Vector2f(8,8));
}

sf::Vector2f Coin::getPosition()
{
	return m_coinPosition;
}

void Coin::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_coin);
}
