#ifndef TEXTBOX_HPP
# define TEXTBOX_HPP
# include <iostream>
# include <SFML/Graphics.hpp>
# include <sstream>

# define DELETE_KEY 8
# define ENTER_KEY 13
# define ESCAPE_KEY 27

class TextBox
{
public:
	TextBox();
	TextBox(int size, sf::Color color, bool sel);
	~TextBox();

	void setFont(sf::Font &font);
	void setPosition(sf::Vector2f pos);
	void setLimit(bool ToF);
	void setLimit(bool ToF, int limit);
	void setSelected(bool sel);

	std::string gettext();

	void typedOn(sf::Event &input)
	{
		if (this->isSelected)
		{
			int charTyped = input.text.unicode;
			if (charTyped < 128)
			{
				if (this->hasLimit)
				{
					if (this->text.tellp() <= limit)
						inputLogic(charTyped);
					if (this->text.tellp() > limit && charTyped == DELETE_KEY)
						this->deleteLastChar();
				}
				else
					inputLogic(charTyped);
			}
		}
	}

	void render(sf::RenderWindow &window);

private:
	sf::Text textbox;
	std::stringstream text;
	bool isSelected = false;
	bool hasLimit = false;
	int limit;

	void inputLogic(int charTyped);
	void deleteLastChar();
};

#endif
