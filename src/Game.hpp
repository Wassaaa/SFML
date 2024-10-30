#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>

/*
	Class that acts as a game engine
	wrapper for the game loop
*/
class Game
{
public:
	//constructors and destructors
	Game();
	Game(const Game& other);
	Game& operator=(const Game& other);
	virtual ~Game();

	//member functions
	void update();
	void updateEnemies();
	void updateText();
	void render();
	void renderEnemies(sf::RenderTarget &target);
	void renderText(sf::RenderTarget &target);
	void pollEvents();
	void updateMousePositions();
	void spawnEnemy();

	//accessors
	const bool running() const;

private:
	sf::RenderWindow *window;
	sf::VideoMode videoMode;
	sf::Event ev;
	//private functions
	void initVariables();
	void initWindow();
	void initEnemies();
	void initFonts();
	void initText();

	//game logic
	unsigned points;
	int	health;
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	int maxEnemies;

	//resources
	sf::Font font;

	//text
	sf::Text uiText;


	//mouse positions
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;
	sf::Vector2f mouseClickPos;

	//game objects
	sf::RectangleShape enemy;
	std::vector<sf::RectangleShape> enemies;

};
