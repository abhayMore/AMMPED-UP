#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/System/Time.hpp>

enum PowerUPType
{
	HEART = 0,
	TIMER,
	SPEED,
	LIVES,
	EXPLOSION_RADIUS_INCREASE,
	EXPLOSION_RADIUS_DECREASE,
	APPLE,
	ICE_CREAM
};

class PowerUP : public sf::Drawable
{
private:
	sf::Sprite m_powerUPSprite;
	sf::Vector2f m_powerUPPosition;
	int m_type;
	
public:
	PowerUP();
	void init(const sf::Texture& texture, sf::Vector2f pos, PowerUPType type);
	void update(sf::Time deltatime);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void setPosition(sf::Vector2f pos);
	bool playerIsOnPowerUP(sf::Vector2f pos);
	PowerUPType getType();

	sf::Vector2f getPosition();
};