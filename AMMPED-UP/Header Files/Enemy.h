#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include "Animation.h"

class Enemy : public sf::Drawable
{
private:
	sf::Sprite m_playerSprite;
	sf::Vector2f m_playerPosition;
	float velocity;
	sf::Vector2f m_direction;
	sf::Vector2f m_prevPosition;
	Animation m_playerUpWalkAnimation;
	Animation m_playerDownWalkAnimation;
	Animation m_playerLeftWalkAnimation;
	Animation m_playerRightWalkAnimation;

public:
	Enemy();
	Enemy(sf::Vector2f pos);
	~Enemy();
	Enemy(const Enemy& other);
	Enemy& operator=(const Enemy& other);
	
	void init(const sf::Texture& texture);
	void update(const sf::Vector2f& direction, sf::Time deltaTime);
	
	sf::Vector2f getPosition();
	void setPosition(sf::Vector2f pos);
	
	sf::Vector2f getPreviousPosition();
	void setPreviousPosition(sf::Vector2f prevpos);
	
	sf::Vector2f getDirection();
	void setDirection(sf::Vector2f direction);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};


