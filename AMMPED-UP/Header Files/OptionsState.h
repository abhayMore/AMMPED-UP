#pragma once
#include <memory>
#include "SFML/Graphics/Sprite.hpp"

#include "SFML/Graphics/Text.hpp"
#include "State.h"
#include "Game.h"

class OptionsState : public am::State
{
private:
	std::shared_ptr<Context> m_context;
	sf::Text m_optionsTitle;
	sf::Text m_playButton;
	sf::Text m_exitButton;
	sf::Sprite m_menuBackground;

	bool m_isPlayButtonSelected;
	bool m_isPlayButtonPressed;

	bool m_isExitButtonSelected;
	bool m_isExitButtonPressed;

	sf::Music& m_bgm;


public:
	OptionsState(std::shared_ptr<Context>& context);
	~OptionsState();

	void init() override;
	void processInput() override;
	void update(sf::Time deltaTime) override;

	void draw() override;
	void start();
	void pause();

};

