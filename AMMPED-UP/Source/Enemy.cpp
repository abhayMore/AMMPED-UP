#include "../Header Files/Enemy.h"
Enemy::Enemy() :
	PlayerEntity()
{
}

Enemy::Enemy(sf::Vector2f pos, float vel) : PlayerEntity(pos, vel)
{
}

Enemy::~Enemy()
{
}

Enemy::Enemy(const Enemy& other) : PlayerEntity(other)
{
}

Enemy& Enemy::operator=(const Enemy& other) 
{
	// TODO: insert return stat ement here
	if (this != &other)
	{
		PlayerEntity::operator=(other);
	}
	return *this;
}