#pragma once
#include "TGUI/TGUI.hpp"
#include "SFML/Graphics/Text.hpp"

class TextPrompt 
{
	tgui::Gui gui;
	tgui::Theme theme;
	tgui::Label::Ptr m_text;

public:
	TextPrompt() {}
	TextPrompt(sf::RenderWindow& window);
	void init(
		std::string str,
		tgui::Font textFont,
		unsigned int charSize,
		sf::Vector2f textPos,
		sf::Vector2f textOrigin,
		tgui::Color textColor,
		float textOutlineThicknes,
		tgui::Color textOutlineColor
	);
	
	sf::Vector2f getSize();
	int getLength();

	void setText(std::string str);
	void draw();
};

