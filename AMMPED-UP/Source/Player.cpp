#include "../Header Files/Player.h"
Player::Player() : PlayerEntity(sf::Vector2f(32,32), 150.0f), m_health(100), m_isBombPlaced(false)
	
{
}

Player::~Player()
{
}

unsigned int Player::getHealth()
{
	return m_health;
}

void Player::setHealth(int health)
{
	m_health = health;
}

bool Player::playerBombCollision(sf::Vector2f bombPos)
{
	if (bombPos.x - 32 == m_playerPosition.x && bombPos.y == m_playerPosition.y)
	{
		return true;
	}
	else if (bombPos.x == m_playerPosition.x && bombPos.y + 32 == m_playerPosition.y)
	{
		return true;
	}
	else if (bombPos.x + 32 == m_playerPosition.x && bombPos.y == m_playerPosition.y)
	{
		return true;

	}
	else if (bombPos.x == m_playerPosition.x && bombPos.y - 32 == m_playerPosition.y)
	{
		return true;
	}
	else if (bombPos == m_playerPosition)
	{
		return true;
	}
	return false;
}

bool Player::playerCollisionIsOn(sf::Sprite& bombSprite)
{
	return bombSprite.getGlobalBounds().intersects(m_playerSprite.getGlobalBounds());
}

void Player::setPlayerColor(sf::Color color)
{
	m_playerColor = color;
	m_playerSprite.setColor(color);
}

sf::Color Player::getColor()
{
	return sf::Color(m_playerColor);
}

int Player::getAlpha()
{
	return m_playerColor.a;
}

void Player::setIsBombPlaced(bool isPlaced)
{
	m_isBombPlaced = isPlaced;
}

bool Player::getIsBombPlaced()
{
	return m_isBombPlaced;
}

sf::Sprite& Player::getSprite()
{
	return m_playerSprite;
}