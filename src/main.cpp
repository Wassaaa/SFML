#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "GameEntity.hpp"
#include "EntityManager.hpp"

int main()
{
	auto window = sf::RenderWindow({400, 400u}, "CMake SFML Project");
	window.setFramerateLimit(60);
	sf::Clock clock;
	std::srand(std::time(nullptr));

	for (int i = 0; i < 100; i++)
	{
		EntityManager::instance().createEntity("ghost" + std::to_string(i), "/home/a/SFML/assets/skeleton_v2_1.png");
	}
	while (window.isOpen())
	{
		float currentTime = clock.restart().asSeconds();
		float fps = 1.f / currentTime;
		std::cout << "fps: " << fps << std::endl;
		for (auto event = sf::Event(); window.pollEvent(event);)
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		window.clear();
		EntityManager::instance().renderAll(window);
		window.display();
	}
}
