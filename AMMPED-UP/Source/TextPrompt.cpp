#include "../Header Files/TextPrompt.h"

TextPrompt::TextPrompt(sf::RenderWindow& window) : gui(window)
{
	theme.load("Resources/Black.txt");
	m_text = tgui::Label::create();
	m_text->setRenderer(theme.getRenderer("Label"));
}

void TextPrompt::init(
	std::string str,
	tgui::Font textFont,
	unsigned int charSize,
	sf::Vector2f textPos,
	sf::Vector2f textOrigin,
	tgui::Color textColor,
	float textOutlineThicknes,
	tgui::Color textOutlineColor)
{
	m_text->getRenderer()->setFont(tgui::Font(textFont.getId()));
	m_text->setInheritedFont(textFont);
	m_text->setText(str);
	m_text->setPosition(textPos.x, textPos.y);
	m_text->setTextSize(charSize);
	//m_text->setOrigin(textOrigin.x, textOrigin.y);
	
	m_text->getRenderer()->setTextColor(textColor);
	m_text->getRenderer()->setTextOutlineColor(textOutlineColor);
	m_text->getRenderer()->setTextOutlineThickness(textOutlineThicknes);
	gui.add(m_text);
	
}

sf::Vector2f TextPrompt::getSize()
{
	return sf::Vector2f(m_text->getSize());
}

int TextPrompt::getLength()
{
	return m_text->getText().size();
}

void TextPrompt::setText(std::string str)
{
	m_text->setText(str);
}

void TextPrompt::draw()
{
	gui.draw();
}

