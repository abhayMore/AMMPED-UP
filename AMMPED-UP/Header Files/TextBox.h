#pragma once
#include <iostream>>
#include "SFML/Graphics.hpp"
#include <sstream>

#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27

class Textbox {
public:
	Textbox() {

	}
	Textbox(sf::Vector2f size, int Charsize, sf::Color outlineColor, sf::Color bgColor, sf::Color textColor, bool sel) {
		textbox.setCharacterSize(Charsize);
		textbox.setFillColor(textColor);
		isSelected = sel;

		background.setSize(size);
		background.setFillColor(bgColor);
		background.setOutlineThickness(1);
		background.setOutlineColor(outlineColor);
		if (isSelected)
		{
			textbox.setString("_");
		}
		else
		{
			textbox.setString("");
		}
	}

	void setTextColor(sf::Color color)
	{
		textbox.setFillColor(color);
	}

	void setBackColor(sf::Color color)
	{
		background.setFillColor(color);
	}

	void setOutlineColor(sf::Color color)
	{
		background.setFillColor(color);
	}

	void setFont(const sf::Font& font)
	{
		textbox.setFont(font);
	}

	void setPosition(sf::Vector2f pos)
	{
		background.setPosition(pos);
		//float xPos = (pos.x + background.getLocalBounds().width / 2) - (textbox.getLocalBounds().width / 2);
		//float yPos = (pos.y + background.getLocalBounds().height / 2) - (textbox.getLocalBounds().height / 2);
		textbox.setPosition(pos);
	}

	void setLimit(bool ToF)
	{
		hasLimit = ToF;
	}

	void setLimit(bool ToF, int lim)
	{
		hasLimit = ToF;
		limit = lim - 1;
	}

	void setSelected(bool sel)
	{
		isSelected = sel;
		textbox.setString(textbox.getString() + "_");
		if (!sel)
		{
			std::string t = text.str();
			std::string newT = "";
			for (int i = 0; i < t.length(); i++)
			{
				newT += t[i];
			}
			textbox.setString(newT);
		}
	}

	bool getSelected()
	{
		return isSelected;
	}

	std::string getText()
	{
		return text.str();
	}

	void Draw(sf::RenderWindow& window)
	{
		window.draw(background);
		window.draw(textbox);
	}

	void typedOn(sf::Event input)
	{
		if (isSelected)
		{
			int charTyped = input.text.unicode;
			if (charTyped < 128) {
				if (hasLimit)
				{
					if (text.str().length() <= limit)
					{
						inputLogic(charTyped);
					}
					else if (text.str().length() > limit && charTyped == DELETE_KEY)
					{
						deleteLastChar();
					}
				}
				else
				{
					inputLogic(charTyped);
				}
			}
		}
	}
	bool isMouseOver(sf::RenderWindow& window)
	{
		float mouseX = sf::Mouse::getPosition(window).x;
		float mouseY = sf::Mouse::getPosition(window).y;

		float btnPosX = background.getPosition().x;
		float btnPosY = background.getPosition().y;

		float btnXPosWidth = background.getPosition().x + background.getLocalBounds().width;
		float btnYPosHeight = background.getPosition().y + background.getLocalBounds().height;

		if (mouseX < btnXPosWidth && mouseX > btnPosX && mouseY < btnYPosHeight && mouseY > btnPosY)
		{
			return true;
		}
		return false;
	}

private:
	sf::Text textbox;
	sf::RectangleShape background;
	std::ostringstream text;
	bool isSelected = false;
	bool hasLimit = false;
	int limit = 0;

	void inputLogic(int charTyped)
	{
		if (charTyped != DELETE_KEY && charTyped != ENTER_KEY && charTyped != ESCAPE_KEY)
		{
			text << static_cast<char>(charTyped);
		}
		else if (charTyped == DELETE_KEY)
		{
			if (text.str().length() > 0)
			{
				deleteLastChar();
			}
		}
		textbox.setString(text.str() + "_");
	}
	
	void deleteLastChar()
	{
		std::string t = text.str();
		std::string newT = "";

		for (int i = 0; i < t.length() - 1; i++)
		{
			newT += t[i];
		}
		text.str("");
		text << newT;
		textbox.setString(text.str() + "_");
	}
};