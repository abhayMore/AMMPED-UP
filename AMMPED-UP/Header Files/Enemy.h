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
	Animation m_playerUpWalkAnimation;
	Animation m_playerDownWalkAnimation;
	Animation m_playerLeftWalkAnimation;
	Animation m_playerRightWalkAnimation;
	float velocity;
	sf::Vector2f m_direction;

public:
	Enemy();
	Enemy(sf::Vector2f pos);
	~Enemy();

	void init(const sf::Texture& texture);
	void update(const sf::Vector2f& direction, sf::Time deltaTime);
	bool isOn(const sf::Sprite& other) const;
	void grow(const sf::Vector2f& direction);
	bool isSelfIntersecting();
	void setPosition(sf::Vector2f pos);

	sf::Vector2f getPosition();
	void setDirection(sf::Vector2f direction);
	sf::Vector2f getDirection();

	bool playerCollisionIsOn(sf::Sprite& sprite);


	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

