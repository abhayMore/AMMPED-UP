#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include "Animation.h"

class PlayerEntity : public sf::Drawable
{
protected:
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
	PlayerEntity();
	PlayerEntity(sf::Vector2f pos, float vel);
	~PlayerEntity();
	PlayerEntity(const PlayerEntity& other);
	PlayerEntity& operator=(const PlayerEntity& other);

	void init(const sf::Texture& texture);
	void update(const sf::Vector2f& direction, sf::Time deltaTime);

	sf::Vector2f getPosition();
	void setPosition(sf::Vector2f pos);

	sf::Vector2f getPreviousPosition();
	void setPreviousPosition(sf::Vector2f prevpos);

	sf::Vector2f getDirection();
	void setDirection(sf::Vector2f direction);

	void setVelocity(float vel);
	float getVelocity();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};