#include "../Header Files/Animation.h"

Animation::Animation(sf::Sprite& target) : m_target(target)
{
	progress = totalLength = sf::Time(sf::seconds(0));
}

Animation::Animation(const Animation& other) : m_target(other.m_target)
{
	progress = other.progress;
	totalLength = other.totalLength;
	m_frames = other.m_frames;
}

Animation::~Animation()
{
}

void Animation::addFrame(Frame&& frame)
{
	totalLength += frame.duration;
	m_frames.push_back(std::move(frame));
}

void Animation::update(sf::Time elapsed)
{
	progress += elapsed;
	sf::Time p = progress;
	
	for (size_t i = 0; i < m_frames.size(); i++)
	{
		p -= m_frames[i].duration;
		if (p > sf::Time(sf::microseconds(0.0000)) && &(m_frames[i]) == &m_frames.back())
		{
			i = 0;
			continue;
		}
		if (p <= sf::Time(sf::seconds(0)) || &(m_frames[i]) == &m_frames.back())
		{
			m_target.setTextureRect(m_frames[i].rect);
			break;
		}
	}
	
}

const sf::Time Animation::getLength() const
{
	return totalLength;
}