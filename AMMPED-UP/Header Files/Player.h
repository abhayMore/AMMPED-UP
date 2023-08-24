#pragma once
#include <list>
#include "../Header Files/PlayerEntity.h"
#include "../Header Files/Bomb.h"
#include <deque>

class Player : public PlayerEntity
{
private:
	int m_health;
	sf::Color m_playerColor;

public:
	Player();
	~Player();

	bool m_isBombPlaced;
	Bomb m_bomb;
	sf::Vector2f m_bombPos;

	void setIsBombPlaced(bool isPlaced);
	bool getIsBombPlaced();
	sf::Sprite& getSprite();

	unsigned int getHealth();
	void setHealth(int health);
	bool playerBombCollision(sf::Vector2f bombPos);
	bool playerCollisionIsOn(sf::Sprite& bombSprite);
	void setPlayerColor(sf::Color color);
	sf::Color getColor();
	int getAlpha();
};