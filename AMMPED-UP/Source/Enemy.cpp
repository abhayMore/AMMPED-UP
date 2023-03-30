#include "../Header Files/Enemy.h"
#include <iostream>
Enemy::Enemy() :
	velocity(75),
	m_direction(1,0),
	m_playerUpWalkAnimation(m_playerSprite),
	m_playerDownWalkAnimation(m_playerSprite),
	m_playerLeftWalkAnimation(m_playerSprite),
	m_playerRightWalkAnimation(m_playerSprite)
{
}


Enemy::Enemy(sf::Vector2f pos) :
	m_playerPosition(pos),
	velocity(1),
	m_direction(1, 0),
	m_playerUpWalkAnimation(m_playerSprite),
	m_playerDownWalkAnimation(m_playerSprite),
	m_playerLeftWalkAnimation(m_playerSprite),
	m_playerRightWalkAnimation(m_playerSprite),
	m_prevPosition(m_playerPosition)
{
}

Enemy::~Enemy()
{

}

Enemy::Enemy(const Enemy& other) : 
	m_playerSprite(other.m_playerSprite),
	m_playerPosition(other.m_playerPosition),
	velocity(other.velocity),
	m_direction(other.m_direction),
	m_prevPosition(other.m_prevPosition),
	m_playerUpWalkAnimation(other.m_playerUpWalkAnimation),
	m_playerDownWalkAnimation(other.m_playerDownWalkAnimation),
	m_playerLeftWalkAnimation(other.m_playerLeftWalkAnimation),
	m_playerRightWalkAnimation(other.m_playerRightWalkAnimation)
{
	
}

Enemy& Enemy::operator=(const Enemy& other) 
{
	// TODO: insert return stat ement here

	if (this != &other)
	{
	
		*this = other;
	}
	return *this;
}

void Enemy::init(const sf::Texture& texture)
{
	m_playerSprite.setTexture(texture);
	m_playerSprite.setTextureRect(sf::IntRect(96, 0, 16, 16));
	m_playerSprite.setScale({ 2,2 });

	m_playerUpWalkAnimation.addFrame({ sf::IntRect(0,0,16,16), sf::Time(sf::seconds(0.1)) });
	m_playerUpWalkAnimation.addFrame({ sf::IntRect(16,0,16,16), sf::Time(sf::seconds(0.1)) });
	m_playerUpWalkAnimation.addFrame({ sf::IntRect(32,0,16,16), sf::Time(sf::seconds(0.1)) });

	m_playerDownWalkAnimation.addFrame({ sf::IntRect(48,0,16,16), sf::Time(sf::seconds(0.1)) });
	m_playerDownWalkAnimation.addFrame({ sf::IntRect(64,0,16,16), sf::Time(sf::seconds(0.1)) });
	m_playerDownWalkAnimation.addFrame({ sf::IntRect(80,0,16,16), sf::Time(sf::seconds(0.1)) });

	m_playerRightWalkAnimation.addFrame({ sf::IntRect(96,0,16,16), sf::Time(sf::seconds(0.1)) });
	m_playerRightWalkAnimation.addFrame({ sf::IntRect(112,0,16,16), sf::Time(sf::seconds(0.1)) });
	m_playerRightWalkAnimation.addFrame({ sf::IntRect(128,0,16,16), sf::Time(sf::seconds(0.1)) });
	m_playerRightWalkAnimation.addFrame({ sf::IntRect(144,0,16,16), sf::Time(sf::seconds(0.1)) });

	m_playerLeftWalkAnimation.addFrame({ sf::IntRect(160,0,16,16), sf::Time(sf::seconds(0.1)) });
	m_playerLeftWalkAnimation.addFrame({ sf::IntRect(176,0,16,16), sf::Time(sf::seconds(0.1)) });
	m_playerLeftWalkAnimation.addFrame({ sf::IntRect(192,0,16,16), sf::Time(sf::seconds(0.1)) });
	m_playerLeftWalkAnimation.addFrame({ sf::IntRect(208,0,16,16), sf::Time(sf::seconds(0.1)) });

	m_playerSprite.setPosition(m_playerPosition);
	//m_direction = sf::Vector2f(1, 0);

	m_prevPosition = m_playerPosition;

}

void Enemy::update(const sf::Vector2f& direction, sf::Time deltaTime)
{
	m_direction = direction;

	if (m_direction == sf::Vector2f(0, -1))
	{
		m_playerUpWalkAnimation.update(deltaTime);
	}
	else if (m_direction == sf::Vector2f(0, 1))
	{
		m_playerDownWalkAnimation.update(deltaTime);
	}
	else if (m_direction == sf::Vector2f(1, 0))
	{
		m_playerRightWalkAnimation.update(deltaTime);
	}
	else if (m_direction == sf::Vector2f(-1, 0))
	{
		m_playerLeftWalkAnimation.update(deltaTime);
	}
	//p = p + v * t;
	m_playerPosition += (velocity * m_direction * deltaTime.asSeconds());
	m_playerSprite.setPosition(m_playerPosition);
}

void Enemy::setPosition(sf::Vector2f pos)
{
	m_playerPosition = pos;
}

sf::Vector2f Enemy::getPosition()
{
	return sf::Vector2f(m_playerPosition);
}

void Enemy::setDirection(sf::Vector2f direction)
{
	m_direction = direction;
}

sf::Vector2f Enemy::getPreviousPosition()
{
	return sf::Vector2f(m_prevPosition);
}

void Enemy::setPreviousPosition(sf::Vector2f prevpos)
{
	m_prevPosition = prevpos;
}



void Enemy::draw(sf::RenderTarget& target, sf::RenderStates states) const 
{
	target.draw(m_playerSprite);
}

sf::Vector2f Enemy::getDirection()
{
	return m_direction;
}
