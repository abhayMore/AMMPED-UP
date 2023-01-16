#include "../Header Files/Snake.h"
#include <iostream>

Snake::Snake() : m_body(std::list<sf::Sprite>(1))
{
	m_head = --m_body.end();
	m_tail = m_body.begin();

	
}

Snake::~Snake()
{
}

void Snake::init(const sf::Texture& texture)
{
	float x = 16.0f;
	for (auto& piece : m_body)
	{
		piece.setTexture(texture);
		piece.setPosition({ x,16.0f });
		x += 16.0f;
	}
	//snakeAnimation.addFrame({ sf::IntRect(0,0,16,16), sf::Time(sf::seconds(0.1)) });
	//snakeAnimation.addFrame({ sf::IntRect(16,0,16,16), sf::Time(sf::seconds(0.1)) });

	//(*m_tail).setTexture(texture2);
}

void Snake::move(const sf::Vector2f& direction)
{
	m_tail->setPosition(m_head->getPosition() + direction);
	m_head = m_tail;
	++m_tail;

	if (m_tail == m_body.end())
	{
		m_tail = m_body.begin();
	}

}

bool Snake::isOn(const sf::Sprite& other) const
{
	return other.getGlobalBounds().intersects(m_head->getGlobalBounds());
}

void Snake::grow(const sf::Vector2f& direction)
{
	sf::Sprite newPiece;
	newPiece.setTexture(*(m_body.begin()->getTexture()));
	newPiece.setPosition(m_head->getPosition() + direction);

	m_head = m_body.insert(++m_head, newPiece);
}

bool Snake::isSelfIntersecting() 
{
	bool flag = false;
	auto newTail = m_body.end();
	for (auto piece = m_body.begin(); piece != m_body.end(); ++piece)
	{
		if (m_head != piece)
		{
			flag = isOn(*piece);
			if (flag)
			{
				newTail = ++piece;
				break;
			}
		}
	}

	if (newTail != m_body.end())
	{
		while (m_tail != newTail)
		{
			if (m_tail == m_body.end())
			{
				m_tail = m_body.begin();
			}
			auto toRemove = m_tail++;
			m_body.erase(toRemove);
		}
	}
	return flag;
}

void Snake::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (auto& piece : m_body)
	{		
		target.draw(piece);
	}
}
