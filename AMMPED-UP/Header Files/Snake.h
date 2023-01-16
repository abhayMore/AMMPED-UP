#pragma once

#include <list>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include "../Header Files/Animation.h"

class Snake : public sf::Drawable
{
private:
	std::list<sf::Sprite> m_body;
	std::list<sf::Sprite>::iterator m_head;
	std::list<sf::Sprite>::iterator m_tail;
	sf::Sprite snakeSprite;

public:
	Snake();
	~Snake();

	void init(const sf::Texture& texture);
	void move(const sf::Vector2f& direction);
	bool isOn(const sf::Sprite& other) const;
	void grow(const sf::Vector2f& direction);
	bool isSelfIntersecting() ;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

