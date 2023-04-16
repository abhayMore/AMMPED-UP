#pragma once
#include "../Header Files/PlayerEntity.h"
class Enemy : public PlayerEntity
{
private:
public:
	Enemy();
	Enemy(sf::Vector2f pos, float vel);
	~Enemy();
	Enemy(const Enemy& other);
	Enemy& operator=(const Enemy& other);
};