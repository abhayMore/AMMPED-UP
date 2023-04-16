#include "../Header Files/PowerUP.h"

PowerUP::PowerUP()
{
}

void PowerUP::init(const sf::Texture& texture, sf::Vector2f pos, PowerUPType type)
{
	m_powerUPSprite.setTexture(texture);
	m_powerUPSprite.setScale(32.0f / 48.0f, 32.0f / 48.0f);

	m_type = type;
	m_powerUPPosition = pos;
	m_powerUPSprite.setPosition(m_powerUPPosition);
	if (m_type == HEART) //SURVIVE ONE BLAST
	{
		m_powerUPSprite.setTextureRect({ 14 * 48,0,48,48 });
	}
	if (m_type == TIMER) //INCREASE TIMER BY 25 SECONDS
	{
		m_powerUPSprite.setTextureRect({ 18 * 48,0,48,48 });

	}
	if (m_type == SPEED) //INCREASE SPEED BY 10
	{
		m_powerUPSprite.setTextureRect({ 1 * 48,0,48,48 });

	}
	if (m_type == LIVES) //INCREASE ONE LIFE
	{
		m_powerUPSprite.setTextureRect({ 21 * 48,0,48,48 });

	}
	if (m_type == EXPLOSION_RADIUS_INCREASE) //INCREASE EXPLOSION RADIUS BY 2
	{
		m_powerUPSprite.setTextureRect({ 3 * 48,0,48,48 });

	}
	if (m_type == EXPLOSION_RADIUS_DECREASE) //DECREASE EXPLOSION RADIUS BY 2
	{
		m_powerUPSprite.setTextureRect({ 2 * 48,0,48,48 });
	}
	if (m_type == APPLE) //INCREASE SCORE BY 10
	{
		m_powerUPSprite.setTextureRect({ 10 * 48,0,48,48 });
	}
	if (m_type == ICE_CREAM) //INCREASE SCORE BY 25
	{
		m_powerUPSprite.setTextureRect({ 11 * 48,0,48,48 });
	}
}

void PowerUP::update(sf::Time deltatime)
{
}

void PowerUP::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_powerUPSprite);
}

void PowerUP::setPosition(sf::Vector2f pos)
{
	m_powerUPPosition = pos;
}

bool PowerUP::playerIsOnPowerUP(sf::Vector2f pos)
{
	if (getPosition().x + 14 > pos.x + 3 &&
		getPosition().x + 1 <= pos.x + 14 &&
		getPosition().y + 14 > pos.y + 3 &&
		getPosition().y + 1 <= pos.y + 14)
	{
		return true;
	}
	return false;
}

PowerUPType PowerUP::getType()
{
	return static_cast<PowerUPType>(m_type);
}

sf::Vector2f PowerUP::getPosition()
{
	return m_powerUPPosition;
}