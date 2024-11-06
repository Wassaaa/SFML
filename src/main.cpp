#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "GameEntity.hpp"
#include "EntityManager.hpp"
#include "TextBox.hpp"
#include "Button.hpp"

int main()
{
	auto window = sf::RenderWindow({400, 400u}, "CMake SFML Project");
	window.setFramerateLimit(60);
	sf::Clock clock;
	std::srand(std::time(nullptr));

	sf::Font font;
	font.loadFromFile("/home/a/SFML/fonts/RubikWetPaint-Regular.ttf");
	TextBox textbox(15, sf::Color::White, false);
	textbox.setFont(font);
	textbox.setPosition({100, 100});

	Button btn("BUTTON", 10, {100, 20}, sf::Color::Green, sf::Color::Black);
	btn.setFont(font);
	btn.setPosition({150, 150});


	for (int i = 0; i < 100; i++)
	{
		EntityManager::instance().createEntity("ghost" + std::to_string(i), "/home/a/SFML/assets/skeleton_v2_1.png");
	}
	while (window.isOpen())
	{
		float deltaTime = clock.restart().asSeconds();
		float fps = 1.f / deltaTime;
		// std::cout << "fps: " << fps << std::endl;
		// std::cout << "on button: " << btn.isMouseOver(window) << std::endl;
		for (auto event = sf::Event(); window.pollEvent(event);)
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::TextEntered:
				textbox.typedOn(event);
				break;
			case sf::Event::KeyPressed:
				if (event.key.scancode == sf::Keyboard::Scan::Enter)
					textbox.setSelected(true);
				if (event.key.scancode == sf::Keyboard::Scan::Escape)
					textbox.setSelected(false);
				break;
			case sf::Event::MouseMoved:
				if (btn.isMouseOver(window))
					btn.setBackColor(sf::Color::White);
				else
					btn.setBackColor(sf::Color::Green);
				break;

			default:
				break;
			}
		}

		window.clear();
		EntityManager::instance().renderAll(window);
		textbox.render(window);
		btn.render(window);
		window.display();
	}
}
