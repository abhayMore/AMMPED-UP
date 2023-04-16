#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include "Animation.h"
class Coin : public sf::Drawable
{
private:
	sf::Sprite m_coin;
	Animation m_coinAnimation;
	sf::Vector2f m_coinPosition;

public:
	Coin();
	void init(const sf::Texture& texture);
	void update(sf::Time deltatime);
	bool playerIsOnCoin(sf::Sprite& other);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void setPosition(sf::Vector2f pos);
	sf::Vector2f getPosition();
};