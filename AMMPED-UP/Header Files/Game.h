#pragma once
#include <memory>
#include "SFML/Graphics/RenderWindow.hpp"
#include "AssetManager.h"
#include "StateManager.h"

enum AssetID
{
	MAIN_FONT = 0,
	LOGIN_FONT,
	GRASS,
	WALL,
	VERTICAL_WALL_TEXTURE,
	HORIZONTAL_WALL_TEXTURE,
	INNER_COMPARTMENT_WALL_TEXTURE,
	COLUMN_WALL_TEXTURE,
	PLAYER,
	COLLEGE_SPLASH_SCREEN,
	MY_SPLASH_SCREEN,
	MAIN_SOUND_TRACK,
	COIN,
	COIN_SFX,
	DEATH_SFX,
	ENEMY_DEATH_SFX,
	IN_GAME_SOUND_TRACK,
	MENU_BACKGROUND,
	GAME_BACKGROUND,
	GAME_LOGO,
	BREAKABLE_WALL_TEXTURE,
	POWERUPS,
	BOMB_TRIGGER,
	EXPLOSION_SPRITE,
	ENEMY1,
	ENEMY2,
	ENEMY3,
	HEART_UI,
	DAMAGE_SFX,
	BLAST_SFX,
	TITLE_FONT
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
	sf::Image m_icon;
public:
	Game();
	~Game();

	void run();
};