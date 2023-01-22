#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"

class Button
{
public:
	Button() {}

	Button(std::string t, sf::Vector2f size, int charSize, sf::Color bgColor, sf::Color textColor)
	{
		text.setString(t);
		text.setFillColor(textColor);
		text.setCharacterSize(charSize);


		button.setSize(size);
		button.setFillColor(bgColor);
	}

	void setFont(const sf::Font& font)
	{
		text.setFont(font);

	}

	sf::Vector2f getButtonSize()
	{
		return button.getSize();
	}

	void setBackColor(sf::Color color)
	{
		button.setFillColor(color);

	}

	void setTextColor(sf::Color color)
	{
		text.setFillColor(color);

	}

	void setPosition(sf::Vector2f pos)
	{
		button.setPosition(pos);
		float xPos = (pos.x + button.getLocalBounds().width / 2) - (text.getLocalBounds().width / 2);
		float yPos = (pos.y + button.getLocalBounds().height / 2) - (text.getLocalBounds().height / 2);
		text.setPosition({ xPos, yPos });
	}

	void Draw(sf::RenderWindow& window)
	{
		window.draw(button);
		window.draw(text);
	}

	bool isMouseOver(sf::RenderWindow& window)
	{
		float mouseX = sf::Mouse::getPosition(window).x;
		float mouseY = sf::Mouse::getPosition(window).y;

		float btnPosX = button.getPosition().x;
		float btnPosY = button.getPosition().y;

		float btnXPosWidth = button.getPosition().x + button.getLocalBounds().width;
		float btnYPosHeight = button.getPosition().y + button.getLocalBounds().height;

		if (mouseX < btnXPosWidth && mouseX > btnPosX && mouseY < btnYPosHeight && mouseY > btnPosY)
		{
			return true;
		}
		return false;

	}

private:
	sf::RectangleShape button;
	sf::Text text;


};