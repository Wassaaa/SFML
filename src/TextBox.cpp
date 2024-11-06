#include "TextBox.hpp"

TextBox::TextBox()
{
}

TextBox::TextBox(int size, sf::Color color, bool sel)
{
	this->textbox.setCharacterSize(size);
	this->textbox.setFillColor(color);
	this->isSelected = sel;
	if (sel)
		textbox.setString("_");
	else
		textbox.setString("");
}

TextBox::~TextBox()
{
}

void TextBox::setFont(sf::Font &font)
{
	this->textbox.setFont(font);
}

void TextBox::setPosition(sf::Vector2f pos)
{
	this->textbox.setPosition(pos);
}

void TextBox::setLimit(bool ToF)
{
	this->hasLimit = ToF;
}

void TextBox::setLimit(bool ToF, int limit)
{
	this->hasLimit = ToF;
	this->limit = limit;
}

void TextBox::setSelected(bool sel)
{
	this->isSelected = sel;
	if (sel)
		textbox.setString(text.str() + "_");
	else
		textbox.setString(text.str());
}

std::string TextBox::gettext()
{
	return this->text.str();
}

void TextBox::render(sf::RenderWindow &window)
{
	window.draw(textbox);
}

void TextBox::inputLogic(int charTyped)
{
	if (charTyped != DELETE_KEY && charTyped != ENTER_KEY
		&& charTyped != ESCAPE_KEY)
		text << static_cast<char>(charTyped);
	else if (charTyped == DELETE_KEY)
		deleteLastChar();
	// textbox.setString(text.str() + "_");
	textbox.setString(text.str() + "_");
}

void TextBox::deleteLastChar()
{
	if (text.tellp() > 0)
	{
		text.seekp(-1, std::ios_base::end);
		text.str(text.str().substr(0, text.tellp()));
		text.seekp(0, std::ios_base::end);
	}
}
