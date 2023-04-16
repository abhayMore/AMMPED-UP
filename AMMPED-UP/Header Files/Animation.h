#pragma once
#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/System/Time.hpp"
#include <vector>

struct Frame {
	sf::IntRect rect;
	sf::Time duration;
};

class Animation
{
private:
	std::vector<Frame> m_frames;
	sf::Time totalLength;
	sf::Time progress;
	sf::Sprite& m_target;

public:
	Animation(sf::Sprite& target);
	Animation(const Animation& other);
	virtual ~Animation();
	//bool operator!=(const Animation& other);

	//Animation& operator=(const Animation& other);

	void addFrame(Frame&& frame);
	void update(sf::Time elapsed);
	const sf::Time getLength() const;
};