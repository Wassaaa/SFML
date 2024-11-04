#ifndef GAME_HPP
# define GAME_HPP
# include "../pch.hpp"
# include "Player.hpp"
# include "TileMap.hpp"

class Game
{
public:
	Game();
	virtual ~Game();

	//Functions
	const sf::RenderWindow& getWindow() const;

	void updateInput();
	void update();
	void updatePlayer();
	void updateCollision();
	void updateTileMap();

	void render();
	void renderPlayer();
	void renderTileMap();

	float &dt() { return this->deltaTime; }


private:

	sf::Clock deltaClock;
	sf::RenderWindow window;
	sf::Event ev;
	sf::Texture tileSheet;

	std::shared_ptr<Player> player;
	std::shared_ptr<TileMap> tileMap;
	std::map<std::string, sf::Keyboard::Key> keyboardMappings;
	std::map<std::string, sf::Mouse::Button> mouseMappings;
	//variables
	float deltaTime;
	//tiles file
	float tileScale;
	int tileSize;
	int tilesWidth;
	int tilesHeight;

	void initWindow();
	void initInput();
	void initPlayer();
	void initTileSheet();
	void initTileMap();
};

#endif
