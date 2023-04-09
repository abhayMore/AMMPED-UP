#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include "Animation.h"

class Bomb : public sf::Drawable
{
private:
	sf::Sprite m_bomb;
	Animation m_bombTickAnimation;
	int m_bombRadius;
	bool m_blasted;
	sf::Time m_bombTriggerTime;
	sf::Vector2f m_bombPosition;
public:
	Bomb();
	void init(const sf::Texture& texture);
	void update(const sf::Vector2f pos, sf::Time deltatime);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	bool isBlasted();
	void setIsBlasted(bool isBlasted);
	void setPosition(sf::Vector2f pos);
	sf::Vector2f getPosition();
};

