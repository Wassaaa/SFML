#include "Button.hpp"

Button::Button()
{
}

Button::Button(std::string text, int charSize, sf::Vector2f size,
	sf::Color bgColor, sf::Color textColor)
{
	this->text.setString(text);
	this->text.setFillColor(textColor);
	this->text.setCharacterSize(charSize);
	this->button.setSize(size);
	this->button.setFillColor(bgColor);
}

Button::~Button()
{
}

void Button::setFont(sf::Font &font)
{
	this->text.setFont(font);
}

void Button::setBackColor(sf::Color color)
{
	this->button.setFillColor(color);
}

void Button::setTextColor(sf::Color color)
{
	this->text.setFillColor(color);
}

void Button::setPosition(sf::Vector2f pos)
{
	this->button.setPosition(pos);

	text.setOrigin(text.getGlobalBounds().getSize() / 2.f + text.getLocalBounds().getPosition());
	text.setPosition(this->button.getPosition() + (this->button.getSize() / 2.f));
}

bool Button::isMouseOver(sf::RenderWindow &window)
{
	sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
	if (button.getGlobalBounds().contains(mousePos))
		return true;
	return false;
}

void Button::render(sf::RenderWindow &window)
{
	window.draw(button);
	window.draw(text);
}
