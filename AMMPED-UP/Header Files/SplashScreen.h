#pragma once
#include "SFML/System/Time.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Audio/Sound.hpp"

#include "State.h"
#include "Game.h"

class SplashScreen : public am::State
{
private:
	std::shared_ptr<Context> m_context;
	sf::Clock m_clock;
	sf::Sprite m_background;
	//sf::Music& m_bgm;


public:
	SplashScreen(std::shared_ptr<Context>& context);
	~SplashScreen();

	void init() override;
	void processInput() override;
	void update(sf::Time deltaTime) override;

	void draw() override;
};

