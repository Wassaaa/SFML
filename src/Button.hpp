#ifndef BUTTON_HPP
# define BUTTON_HPP
# include <SFML/Graphics.hpp>

class Button
{
public:
	Button();
	Button(std::string text, int charSize, sf::Vector2f size, sf::Color bgColor, sf::Color textColor);
	~Button();

	void setFont(sf::Font &font);
	void setBackColor(sf::Color color);
	void setTextColor(sf::Color color);
	void setPosition(sf::Vector2f pos);

	bool isMouseOver(sf::RenderWindow &window);

	void render(sf::RenderWindow &window);

private:
	sf::RectangleShape button;
	sf::Text text;
};

#endif
