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
	//sf::Clock m_clock;
	std::vector<sf::Texture> m_textures;
	std::vector< std::pair<int, float> > m_assetID;

	sf::Sprite m_background;
	//sf::Music& m_bgm;
	int m_currentSplashScreen;
	sf::Time m_elapsedTime;
	sf::Color m_bgColor;

public:
	SplashScreen(std::shared_ptr<Context>& context, std::vector< std::pair<int, float> > assetID);
	~SplashScreen();

	void init() override;
	void processInput() override;
	void update(sf::Time deltaTime) override;

	void draw() override;
};