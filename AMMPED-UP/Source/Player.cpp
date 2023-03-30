#include "../Header Files/Player.h"
#include <iostream>

Player::Player() :
	m_playerPosition({ 32,32 }),
	m_velocity(150),
	m_playerUpWalkAnimation(m_playerSprite),
	m_playerDownWalkAnimation(m_playerSprite),
	m_playerLeftWalkAnimation(m_playerSprite),
	m_playerRightWalkAnimation(m_playerSprite),
	m_isBombPlaced(false),
	m_health(100),
	m_playerColor(sf::Color(255,255,255,255)),
	m_previousPosition(m_playerPosition)
{
}

Player::~Player()
{
}

void Player::init(const sf::Texture& texture)
{
	m_playerSprite.setTexture(texture);
	m_playerSprite.setTextureRect(sf::IntRect(96, 0, 16, 16));
	m_playerSprite.setScale({ 2,2 });
	m_playerSprite.setColor(m_playerColor);
	m_playerUpWalkAnimation.addFrame({ sf::IntRect(0,0,16,16), sf::Time(sf::seconds(0.001)) });
	m_playerUpWalkAnimation.addFrame({ sf::IntRect(16,0,16,16), sf::Time(sf::seconds(0.001)) });
	m_playerUpWalkAnimation.addFrame({ sf::IntRect(32,0,16,16), sf::Time(sf::seconds(0.001)) });

	m_playerDownWalkAnimation.addFrame({ sf::IntRect(48,0,16,16), sf::Time(sf::seconds(0.001)) });
	m_playerDownWalkAnimation.addFrame({ sf::IntRect(64,0,16,16), sf::Time(sf::seconds(0.001) )});
	m_playerDownWalkAnimation.addFrame({ sf::IntRect(80,0,16,16), sf::Time(sf::seconds(0.001)) });

	m_playerRightWalkAnimation.addFrame({ sf::IntRect(96,0,16,16), sf::Time(sf::seconds(0.001)) });
	m_playerRightWalkAnimation.addFrame({ sf::IntRect(112,0,16,16), sf::Time(sf::seconds(0.001)) });
	m_playerRightWalkAnimation.addFrame({ sf::IntRect(128,0,16,16), sf::Time(sf::seconds(0.001)) });
	m_playerRightWalkAnimation.addFrame({ sf::IntRect(144,0,16,16), sf::Time(sf::seconds(0.001)) });

	m_playerLeftWalkAnimation.addFrame({ sf::IntRect(160,0,16,16), sf::Time(sf::seconds(0.001)) });
	m_playerLeftWalkAnimation.addFrame({ sf::IntRect(176,0,16,16), sf::Time(sf::seconds(0.001)) });
	m_playerLeftWalkAnimation.addFrame({ sf::IntRect(192,0,16,16), sf::Time(sf::seconds(0.001)) });
	m_playerLeftWalkAnimation.addFrame({ sf::IntRect(208,0,16,16), sf::Time(sf::seconds(0.001)) });

	m_playerSprite.setPosition(m_playerPosition);
	m_previousPosition = m_playerPosition;


}

void Player::update(const sf::Vector2f& direction, sf::Time deltaTime)
{
	if (direction == sf::Vector2f(0, -1))
	{
		m_playerUpWalkAnimation.update(deltaTime);
	}
	else if (direction == sf::Vector2f(0, 1))
	{
		m_playerDownWalkAnimation.update(deltaTime);
	}
	else if (direction == sf::Vector2f(1, 0))
	{
		m_playerRightWalkAnimation.update(deltaTime);
	}
	else if (direction == sf::Vector2f(-1, 0))
	{
		m_playerLeftWalkAnimation.update(deltaTime);
	}
	m_playerPosition +=(m_velocity * direction * deltaTime.asSeconds());
	m_playerSprite.setPosition(m_playerPosition);
}


sf::Vector2f Player::getPosition()
{
	return m_playerPosition;
}

int Player::getHealth()
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

sf::Vector2f Player::getPreviousPosition()
{
	return sf::Vector2f(m_previousPosition);
}

void Player::setPreviousPosition(sf::Vector2f prevpos)
{
	m_previousPosition = prevpos;
}

void Player::setPosition(sf::Vector2f pos)
{
	m_playerPosition = pos;
}

void Player::setVelocity(float vel)
{
	m_velocity = vel;
}

float Player::getVelocity()
{
	return m_velocity;
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
	// TODO: insert return statement here
	return m_playerSprite;
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
		
	target.draw(m_playerSprite);
}
