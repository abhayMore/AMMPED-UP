#pragma once

#include <list>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include "../Header Files/Animation.h"
#include "../Header Files/Bomb.h"
#include <deque>

class Player : public sf::Drawable
{
private:
	sf::Sprite m_playerSprite;
	sf::Vector2f m_playerPosition;
	float m_velocity;
	sf::Vector2f m_previousPosition;
	Animation m_playerUpWalkAnimation;
	Animation m_playerDownWalkAnimation;
	Animation m_playerLeftWalkAnimation;
	Animation m_playerRightWalkAnimation;
	int m_health;
	sf::Color m_playerColor;

public:
	Player();
	~Player();

	bool m_isBombPlaced;
	Bomb m_bomb;
	sf::Vector2f m_bombPos;
	void init(const sf::Texture& texture);
	void update(const sf::Vector2f& direction, sf::Time deltatime);
	void setPosition(sf::Vector2f pos);
	void setVelocity(float vel);
	float getVelocity();

	void setIsBombPlaced(bool isPlaced);
	bool getIsBombPlaced();
	sf::Sprite& getSprite();

	sf::Vector2f getPosition();
	int getHealth();
	void setHealth(int health);
	bool playerBombCollision(sf::Vector2f bombPos);
	bool playerCollisionIsOn(sf::Sprite& bombSprite);
	void setPlayerColor(sf::Color color);
	sf::Color getColor();
	int getAlpha();

	sf::Vector2f getPreviousPosition();
	void setPreviousPosition(sf::Vector2f prevpos);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

