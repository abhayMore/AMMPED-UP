#pragma once

#include <memory>
#include "SFML/Graphics/RenderWindow.hpp"
#include "AssetManager.h"
#include "StateManager.h"

enum AssetID
{
	MAIN_FONT = 0,
	GRASS,
	FOOD,
	WALL,
	OBJ,
	SPLASH_SCREEN,
	MAIN_SOUND_TRACK,
	FOOD_SFX,
	DEATH_SFX,
	IN_GAME_SOUND_TRACK,
	MENU_BACKGROUND,
	SNAKE_SPRITESHEET,
	GAME_LOGO
};
 
struct Context
{
	std::unique_ptr<am::AssetManager> m_assets;
	std::unique_ptr<am::StateManager> m_states;
	std::unique_ptr<sf::RenderWindow> m_window;

	Context()
	{
		m_assets = std::make_unique<am::AssetManager>();
		m_states = std::make_unique<am::StateManager>();
		m_window = std::make_unique<sf::RenderWindow>();
	}
};

class Game
{
private:
	std::shared_ptr<Context> m_context;
	const sf::Time TIME_PER_FRAME = sf::seconds(1.0f / 60.0f);

public:
	Game();
	~Game();

	void run();
};

