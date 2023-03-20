#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

class PoweUp
{
private:
	sf::Sprite m_powerUpSprite;
	sf::Vector2f m_pos;
	bool m_powerUpTaken;
};

